#include "accelerometer.h"

Accelerometer::Accelerometer (char* device_file, int slave_address)
{
  m_i2c_port = std::unique_ptr<I2C> (new I2C (device_file, slave_address));
}
Accelerometer::Accelerometer (int slave_address)
{
  m_i2c_port = std::unique_ptr<I2C> (new I2C(slave_address));
}
Accelerometer::~Accelerometer ()
{
}



