#include "accelerometer.h"

Accelerometer::Accelerometer (char* device_file, int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C(device_file, slave_address));
}
Accelerometer::Accelerometer (int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C(slave_address));
}
int Accelerometer::read(unsigned char* buf, int length){
  return -1;
}
int Accelerometer::write(unsigned char* buf, int length){
  return -1;
}
Accelerometer::~Accelerometer ()
{
}



