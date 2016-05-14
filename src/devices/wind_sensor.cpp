#include "wind_sensor.h"

// Private Functions
int WindSensor::init(){
  return -1;
}
// Public Functions
WindSensor::WindSensor (char* device_file, int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (device_file, slave_address));
  set_device_id(static_cast<int>(Device_ID::WIND_SENSOR));
}
WindSensor::WindSensor (int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C (slave_address));
  set_device_id(static_cast<int>(Device_ID::WIND_SENSOR));
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

