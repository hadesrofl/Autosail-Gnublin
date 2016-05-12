#include "compass.h"

Compass::Compass (char* device_file, int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C (device_file, slave_address));
}
Compass::Compass (int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C(slave_address));
}
int Compass::read(unsigned char* buf, int length){
  return -1;
}
int Compass::write(unsigned char* buf, int length){
  return -1;
}
Compass::~Compass ()
{
}

