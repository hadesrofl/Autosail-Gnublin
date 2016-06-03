#include "hygrometer.h"

// Private Functions
int8_t
Hygrometer::init ()
{
  return -1;
}
// Public Functions
Hygrometer::Hygrometer (char* device_file, uint8_t slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (device_file, slave_address));
  set_device_id (Descriptor::HYGROMETER);
}
Hygrometer::Hygrometer (uint8_t slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C (slave_address));
  set_device_id (Descriptor::HYGROMETER);
}
uint8_t*
Hygrometer::read_data ()
{
  uint8_t* data_ptr = NULL;
  return data_ptr;
}
Hygrometer::~Hygrometer ()
{
}
