#include "compass.h"

// Private Functions
int8_t
Compass::init ()
{
  uint8_t data[2] =
    { 0 };
  data[0] = COMPASS_CONFIG_A_REGISTER_ADDR;
  data[1] = COMPASS_CONFIG_A_REGISTER_VALUE;
  int8_t ret = Device::write (data, 2);
  if (ret < 0)
    {
      return -1;
    }
  data[0] = COMPASS_CONFIG_B_REGISTER_ADDR;
  data[1] = COMPASS_CONFIG_B_REGISTER_VALUE;
  ret = Device::write (data, 2);
  if (ret < 0)
    {
      return -1;
    }
  data[0] = COMPASS_MODE_REGISTER_ADDR ;
  data[1] = COMPASS_MODE_REGISTER_VALUE;
  ret = Device::write (data, 2);
  if (ret < 0)
    {
      return -1;
    }
  return ret;
}
// Public Functions
Compass::Compass (char* device_file, uint8_t slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (device_file, slave_address));
  set_device_id (Device_ID::COMPASS);
  init ();
}
Compass::Compass (uint8_t slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C (slave_address));
  set_device_id (Device_ID::COMPASS);
  init ();
}
uint8_t*
Compass::read_data ()
{
  uint8_t register_data[2] = {0};
  uint8_t* data = new unsigned char[6];
  for (int16_t i = 0; i < static_cast<int16_t> (Sensor_Param::COMPASS_DATA_LENGTH); i++)
    {
      data[i] = 0;
    }
  register_data[0] = COMPASS_X_MSB_REGISTER_ADDR;
  register_data[1] = static_cast<uint8_t>(Sensor_Param::COMPASS_DATA_LENGTH);
  Device::write (register_data, 2);
  Device::read (data, 6);
  int16_t x = (data[1] << 8) | data[0];
  int16_t z = (data[3] << 8) | data[2];
  int16_t y = (data[5] << 8) | data[4];
  int16_t x_gauss = x * COMPASS_SCALING_FACTOR;
  int16_t z_gauss = z * COMPASS_SCALING_FACTOR;
  int16_t y_gauss = y * COMPASS_SCALING_FACTOR;
  uint8_t msb_x = x_gauss >> 8;
  uint8_t lsb_x = x_gauss;
  uint8_t msb_z = z_gauss >> 8;
  uint8_t lsb_z = z_gauss;
  uint8_t msb_y = y_gauss >> 8;
  uint8_t lsb_y = y_gauss;
#ifdef _DEBUG
  int16_t check_x = (msb_x << 8) | lsb_x;
  int16_t check_z = (msb_z << 8) | lsb_z;
  int16_t check_y = (msb_y << 8) | lsb_y;
  float x_tesla = x_gauss / 10;
  float z_tesla = z_gauss / 10;
  float y_tesla = y_gauss / 10;
  std::cout << "X MSB: " << static_cast<int> (data[0]) << " " << std::endl;
  std::cout << "X LSB: " << static_cast<int> (data[1]) << " " << std::endl;
  std::cout << "Z MSB: " << static_cast<int> (data[2]) << " " << std::endl;
  std::cout << "Z LSB: " << static_cast<int> (data[3]) << " " << std::endl;
  std::cout << "Y MSB: " << static_cast<int> (data[4]) << " " << std::endl;
  std::cout << "Y LSB: " << static_cast<int> (data[5]) << " " << std::endl;
  std::cout << "X 16 bit: " << x << std::endl;
  std::cout << "Z 16 bit: " << z << std::endl;
  std::cout << "Y 16 bit: " << y << std::endl;
  std::cout << "Check X: " << check_x << std::endl;
  std::cout << "Check Z: " << check_z << std::endl;
  std::cout << "Check Y: " << check_y << std::endl;
  std::cout << "X mGauss: " << x_gauss << std::endl;
  std::cout << "Z mGauss: " << z_gauss << std::endl;
  std::cout << "Y mGauss: " << y_gauss << std::endl;
  std::cout << "X uTesla: " << x_tesla << std::endl;
  std::cout << "Z uTesla: " << z_tesla << std::endl;
  std::cout << "Y uTesla: " << y_tesla << std::endl;
#endif
  data[0] = msb_x;
  data[1] = lsb_x;
  data[2] = msb_z;
  data[3] = lsb_z;
  data[4] = msb_y;
  data[5] = lsb_y;
  return data;
}
Compass::~Compass ()
{
}

