#include "hygrometer.h"

// Private Functions
int
Hygrometer::init ()
{
  return -1;
}
// Public Functions
Hygrometer::Hygrometer (char* device_file, int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (device_file, slave_address));
  set_device_id (Device_ID::HYGROMETER);
}
Hygrometer::Hygrometer (int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C (slave_address));
  set_device_id (Device_ID::HYGROMETER);
}
unsigned char*
Hygrometer::read_data ()
{
  unsigned char* data_ptr = NULL;
  return data_ptr;
}
Hygrometer::~Hygrometer ()
{
}
