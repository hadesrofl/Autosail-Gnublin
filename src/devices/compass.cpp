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
  set_device_id (Device_ID::COMPASS);
}
Compass::Compass (int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C (slave_address));
  set_device_id (Device_ID::COMPASS);
}
unsigned char*
Compass::read_data ()
{
  unsigned char* data_ptr = NULL;
  return data_ptr;
}
Compass::~Compass ()
{
}

