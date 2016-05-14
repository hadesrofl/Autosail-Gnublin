#include "compass.h"

// Private Functions
int
Compass::init ()
{
  return -1;
}
// Public Functions
Compass::Compass (char* device_file, int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (device_file, slave_address));
  set_device_id (static_cast<int> (Device_ID::COMPASS));
}
Compass::Compass (int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C (slave_address));
  set_device_id (static_cast<int> (Device_ID::COMPASS));
}
int
Compass::read (unsigned char* buf, int length)
{
  if (buf == NULL || length == 0)
    {
      return -1;
    }
  return m_interface_port->receive (buf, length);
}
int
Compass::write (unsigned char* buf, int length)
{
  if (buf == NULL || length == 0)
    {
      return -1;
    }
  return m_interface_port->send (buf, length);
}
Compass::~Compass ()
{
}

