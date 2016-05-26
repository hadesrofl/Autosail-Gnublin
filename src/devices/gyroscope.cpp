#include "gyroscope.h"

// Private Functions
int8_t
Gyroscope::init ()
{
  return -1;
}
// Public Functions
Gyroscope::Gyroscope (char* device_file, uint8_t slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (device_file, slave_address));
  set_device_id (Device_ID::GYROSCOPE);
}
Gyroscope::Gyroscope (uint8_t slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C (slave_address));
  set_device_id (Device_ID::GYROSCOPE);
}
uint8_t*
Gyroscope::read_data ()
{
  uint8_t* data_ptr = NULL;
  return data_ptr;
}
Gyroscope::~Gyroscope ()
{
}

