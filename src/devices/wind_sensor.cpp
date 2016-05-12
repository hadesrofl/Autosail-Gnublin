#include "wind_sensor.h"

WindSensor::WindSensor (char* device_file, int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (device_file, slave_address));
}
WindSensor::WindSensor (int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C (slave_address));
}
int WindSensor::read(unsigned char* buf, int length){
  return -1;
}
int WindSensor::write(unsigned char* buf, int length){
  return -1;
}
WindSensor::~WindSensor ()
{
}

