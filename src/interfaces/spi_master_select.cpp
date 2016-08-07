#include "spi_master_select.h"
#include <stdio.h>

#include "spi_thread_param_t.h"

// private functions

int8_t
SPIMasterSelect::set_trigger_type (uint8_t pin_no, char* trigger)
{
  gnublin_gpio gpio;
  gpio.pinMode (static_cast<int> (pin_no), INPUT);
  char dir[28];
  sprintf (dir, "%s%d%s", PIN_MS_PRE_TRIGGER_FILE, pin_no,
  PIN_MS_SUFF_TRIGGER_FILE);
  ofstream file (dir);
  if (file < 0)
    {
      return -1;
      cout << "cannot open file: " << dir << endl;
    }
  file << trigger;
  file.close ();
  return 1;
}

// public functions
SPIMasterSelect::SPIMasterSelect (char* device_file, uint16_t spi_speed,
				  uint8_t pin_no)
{
  m_device_file = Interface::set_device_file (device_file);
  m_spi_port = std::unique_ptr<gnublin_spi> (new gnublin_spi ());
  // SPI Mode 1
  m_spi_port->setMode (1);
  // MSB
  m_spi_port->setLSB (0);

  if (pin_no > 0)
    {

      m_pin_ms = pin_no;
      m_trigger_action = (char*) TRIGGER_RISING;
      set_trigger_type (m_pin_ms, m_trigger_action);
#ifdef _DEBUG
      //XXX For Test Purposes set Pin to output for switch on breadboard
      std::cout << "Pin: " << static_cast<int>(m_pin_ms) << std::endl;
      char command[COMMAND_OUTPUT_PIN_LENGTH];
      snprintf (command, COMMAND_OUTPUT_PIN_LENGTH, "gnublin-gpio -o 1 -p %d",
	  m_pin_ms);
      system (command);
#endif
    }
  else
    {
      m_pin_ms = 0;
      m_trigger_action = (char*) "";
    }
}

int16_t
SPIMasterSelect::receive (uint8_t* buf, int16_t length)
{
  int16_t result = m_spi_port->receive ((char*) buf, length);
#ifdef _DEBUG
  bool error = m_spi_port->fail ();
  std::cout << error << std::endl;
#endif
  return result;
}

int16_t
SPIMasterSelect::send (uint8_t* buf, int16_t length)
{
  int16_t result = m_spi_port->send (buf, length);
#ifdef _DEBUG
  bool error = m_spi_port->fail ();
  std::cout << error << std::endl;
#endif
  return result;
}
int8_t
SPIMasterSelect::transfer (uint8_t* write, int16_t write_length, uint8_t* read,
			   int16_t read_length)
{
  return m_spi_port->message (write, write_length, read, read_length);
}

void *
SPIMasterSelect::pin_change_interrupt (void* params)
{
  struct spi_thread_param_t* spi = (struct spi_thread_param_t*) params;
  spi->frame_count = 0;
  struct pollfd *poll_fd;
  char buf[2];
  char dir[28];
  sprintf (dir, "%s%d%s", PIN_MS_PRE_VALUE_FILE, spi->spi_ptr->get_pin_ms (),
  PIN_MS_SUFF_VALUE_FILE);
  poll_fd = (pollfd*) malloc (sizeof(*poll_fd));
  poll_fd->fd = open (dir, O_RDWR);
  poll_fd->events = POLLPRI;
  poll_fd->revents = 0;
  int32_t ret = 0;
  while (true)
    {
      read (poll_fd->fd, buf, 1);

      ret = poll (poll_fd, 1, -1);
      if (ret > 0)
	{
	  spi->frame_count++;
	  pthread_cond_signal (&spi->wakeup_cond);
	}
    }
  pthread_exit (0);
  close (poll_fd->fd);
  return NULL;
}

SPIMasterSelect::~SPIMasterSelect ()
{
  gnublin_gpio gpio;
  if (m_pin_ms > 0)
    {
      gpio.unexport (m_pin_ms);
    }
}

