#include "hygrometer.h"

Hygrometer::Hygrometer (char* device_file, int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (device_file, slave_address));
}
Hygrometer::Hygrometer (int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C (slave_address));
}
int Hygrometer::read(unsigned char* buf, int length){
  return -1;
}
int Hygrometer::write(unsigned char* buf, int length){
  return -1;
}
Hygrometer::~Hygrometer ()
{
}
