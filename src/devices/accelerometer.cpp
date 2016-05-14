#include "accelerometer.h"

// Private Functions
int
Accelerometer::init ()
{
  // Address Power CTL Register to set Link Bit, Measure Bit, and Wake Up to 8Hz
  unsigned char register_address = 0x2D;
  unsigned char register_value = 0x38;
  int ret;
  ret = write (&register_address, 1);
  if (ret < 0)
    {
      return -1;
    }
  ret = write (&register_value, 1);
  if (ret < 0)
    {
      return -1;
    }
  return ret;
}
// Public Functions
Accelerometer::Accelerometer (char* device_file, int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (device_file, slave_address));
  set_device_id (static_cast<int> (Device_ID::ACCELEROMETER));
  init();
}
Accelerometer::Accelerometer (int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C (slave_address));
  set_device_id (static_cast<int> (Device_ID::ACCELEROMETER));
  init();
}
int
Accelerometer::read (unsigned char* buf, int length)
{
  if (buf == 0 || length < 1)
    {
      return -1;
    }
  int ret = m_interface_port->receive (buf, length);
  if (ret > 0)
    {
      return ret;
    }
  return -1;
}
int
Accelerometer::write (unsigned char* buf, int length)
{
  if (buf == 0 || length < 1)
    {
      return -1;
    }
  int ret = m_interface_port->send (buf, length);
  if (ret > 0)
    {
      return ret;
    }
  return -1;
}
Accelerometer::~Accelerometer ()
{
}

