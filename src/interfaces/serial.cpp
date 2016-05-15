#include "serial.h"

//
// Public Functions
//

Serial::Serial (char* device_file, int baudrate)
{
  Interface::set_device_file (device_file);
  set_baudrate (baudrate);
  m_serial_port = std::unique_ptr<gnublin_serial> (
      new gnublin_serial (device_file, baudrate));
}
Serial::Serial(int baudrate){
  Interface::set_device_file(SERIAL_DEFAULT_FILE);
  set_baudrate(baudrate);
  m_serial_port = std::unique_ptr<gnublin_serial> (new gnublin_serial(get_device_file(),baudrate));
}

int
Serial::receive (unsigned char* buf, int length)
{
  if (buf == 0)
    {
#ifdef _DEBUG
      std::cout << "ERROR: Buffer is empty!" << std::endl;
#endif
      return -1;
    }

  if (length < 1)
    {
#ifdef _DEBUG
      std::cout << "ERROR: Length is less or equal to 0!" << std::endl;
#endif
      return -1;
    }

  int fd = open (Interface::get_device_file (),
  O_RDWR | O_NOCTTY | O_SYNC | O_NONBLOCK);
  if (read (fd, buf, length) != length)
    {
#ifdef _DEBUG
      std::cout << "ERROR: Not as many bytes read as given by length!"
	  << std::endl;
#endif
      return -1;
    }

  return length;
}

int
Serial::send (unsigned char* buf, int length)
{
  int result = 0;
  if (buf == 0)
    {
#ifdef _DEBUG
      std::cout << "ERROR: Buffer is empty!" << std::endl;
#endif
      return -1;
    }

  if (length < 1)
    {
#ifdef _DEBUG
      std::cout << "ERROR: Length is less or equal to 0!" << std::endl;
#endif
      return -1;
    }
  result = m_serial_port->send (buf, length);
  if (result < 0)
    {
#ifdef _DEBUG
      std::cout << "Sending failed" << std::endl;
#endif
      return -1;
    }
#ifdef _DEBUG
  else
    {
      cout << "Sending: ";
      for (int k = 0; k < length; k++)
	{
	  cout << buf[k];
	}
      cout << endl;
    }
#endif
  return length;
}

Serial::~Serial ()
{
}


