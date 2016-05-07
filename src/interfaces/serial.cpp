#include "serial.h"

//
// Public Functions
//

Serial::Serial (char* device_file, int baudrate)
{
  Interface::set_device_file (device_file);
  set_baudrate (baudrate);
  m_serial_port = std::unique_ptr<gnublin_serial> (new gnublin_serial(device_file, baudrate));
  //m_serial_port = new gnublin_serial (device_file, baudrate);
}

int
Serial::receive (unsigned char* buf, int length)
{
  if (buf == 0)
    {
      return -1;
    }

  if (length < 1)
    {
      return -1;
    }

  int fd = open (Interface::get_device_file (),
		 O_RDWR | O_NOCTTY | O_SYNC | O_NONBLOCK);
  if (read (fd, buf, length) != length)
    {
      return -1;
    }

  return length;
}

int
Serial::send (unsigned char* buf, int length)
{
  int result = 0;
  if (buf == 0)
    return -1;
  if (length < 1)
    return -1;
  result = m_serial_port->send (buf, length);
  if (result < 0)
    {
      //cout << "Sending failed" << endl;
      return -1;
    }
  else
    {
      /*cout << "Sending: ";
       for (int k = 0; k < length; k++)
       {
       cout << buf[k];
       }
       cout << endl;*/
      return length;
    }
}

Serial::~Serial ()
{
}

//
// Private Functions
//

void
Serial::set_baudrate (int baudrate)
{
  m_baudrate = baudrate;
}

