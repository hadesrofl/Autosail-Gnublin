#include "spi_master_select.h"

#include "spi_thread_param.h"

pthread_mutex_t SPIMasterSelect::m_region_mutex = PTHREAD_MUTEX_INITIALIZER;
bool SPIMasterSelect::m_trigger_type_set = false;
uint8_t SPIMasterSelect::m_use_count = 0;

// private functions

int8_t
SPIMasterSelect::set_trigger_type (uint8_t pin_no, char* trigger)
{
  // TODO: Dynamic Read from Trigger File
  gnublin_gpio gpio;
  gpio.pinMode (static_cast<int> (pin_no), INPUT);
  char* dir = (char*) PIN_MS_TRIGGER_FILE;
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
SPIMasterSelect::SPIMasterSelect (char* device_file, uint16_t spi_speed, bool interrupt_check)
{
  // TODO: Dynamic Pin Number for PIN MS
  m_device_file = Interface::set_device_file (device_file);
  m_spi_port = std::unique_ptr<gnublin_spi> (new gnublin_spi ());
  // SPI Mode 1
  m_spi_port->setMode (1);
  // MSB
  m_spi_port->setLSB (0);
  if (m_trigger_type_set == false && interrupt_check == true)
    {
      m_pin_ms = PIN_MS
      ;
      m_trigger_action = (char*) TRIGGER_FALLING;
      set_trigger_type (m_pin_ms, m_trigger_action);
      m_trigger_type_set = true;
    }
  else
    {
      m_pin_ms = 0;
      m_trigger_action = (char*) "";
    }
  m_interrupted = false;
  SPIMasterSelect::m_use_count++;
}

int16_t
SPIMasterSelect::receive (uint8_t* buf, int16_t length)
{
  int result = m_spi_port->receive ((char*) buf, length);
#ifdef _DEBUG
  bool error = m_spi_port->fail ();
  std::cout << error << std::endl;
#endif
  return result;
}

int16_t
SPIMasterSelect::send (uint8_t* buf, int16_t length)
{
  int result = m_spi_port->send (buf, length);
#ifdef _DEBUG
  bool error = m_spi_port->fail ();
  std::cout << error << std::endl;
#endif
  return result;
}

void *
SPIMasterSelect::pin_change_interrupt (void* params)
{
  // TODO: Dynamic Read from Value File
  struct SPIThreadParam* spi = (struct SPIThreadParam*) params;
  spi->spi_ptr->m_interrupted = false;
  struct pollfd *poll_fd;
  char buf[2] =
    { 0 };
  const char* gpio_11 = PIN_MS_VALUE_FILE;
  poll_fd = (pollfd*) malloc (sizeof(*poll_fd));
  poll_fd->fd = open (gpio_11, O_RDWR);
  poll_fd->events = POLLPRI;
  poll_fd->revents = 0;
  read (poll_fd->fd, buf, 1);
  int interrupt_counter = 0;
  int ret = 0;
  ret = poll (poll_fd, 1, -1);
  if (ret > 0)
    {
      std::cout << "Pin Change Interrupt occured! " << std::endl;
      pthread_mutex_lock (&SPIMasterSelect::m_region_mutex);
      //SPIMasterSelect::m_interrupted = true;
      spi->spi_ptr->m_interrupted = true;
      interrupt_counter++;
      pthread_mutex_unlock (&SPIMasterSelect::m_region_mutex);
    }
  else
    {
      std::cout << "No interrupt" << std::endl;
    }
  std::cout << "Interrupt Counter: " << interrupt_counter << std::endl;
  pthread_exit (0);
  close (poll_fd->fd);
  return NULL;
}

SPIMasterSelect::~SPIMasterSelect ()
{
  SPIMasterSelect::m_use_count--;
  std::cout << "Use Count: " << static_cast<int> (SPIMasterSelect::m_use_count)
      << std::endl;
  if (SPIMasterSelect::m_use_count == 0)
    {
      gnublin_gpio gpio;
      uint8_t pin_ms = PIN_MS
      ;
      gpio.unexport (pin_ms);
      std::cout << "Deleted GPIO!" << std::endl;
    }
}

