#include "gyroscope.h"

Gyroscope::Gyroscope (char* device_file, int slave_address)
{
  m_i2c_port = std::unique_ptr<I2C> (new I2C (device_file, slave_address));
}
Gyroscope::Gyroscope (int slave_address)
{
  m_i2c_port = std::unique_ptr<I2C> (new I2C(slave_address));
}
Gyroscope::~Gyroscope ()
{
}




