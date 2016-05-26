#include "wind_sensor.h"

// Private Functions
int8_t
WindSensor::init ()
{
  return -1;
}
// Public Functions
WindSensor::WindSensor (char* device_file, uint8_t slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (device_file, slave_address));
  set_device_id (Device_ID::WIND_SENSOR);
}
WindSensor::WindSensor (uint8_t slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C (slave_address));
  set_device_id (Device_ID::WIND_SENSOR);
}
uint8_t*
WindSensor::read_data ()
{
  uint8_t* data_ptr = NULL;
  return data_ptr;
}
WindSensor::~WindSensor ()
{
}

