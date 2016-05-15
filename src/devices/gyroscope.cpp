#include "gyroscope.h"

// Private Functions
int Gyroscope::init(){
  return -1;
}
// Public Functions
Gyroscope::Gyroscope (char* device_file, int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (device_file, slave_address));
  set_device_id (Device_ID::GYROSCOPE);
}
Gyroscope::Gyroscope (int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C (slave_address));
  set_device_id (Device_ID::GYROSCOPE);
}
int Gyroscope::read(unsigned char* buf, int length){
  return -1;
}
int Gyroscope::write(unsigned char* buf, int length){
  return -1;
}
Gyroscope::~Gyroscope ()
{
}

