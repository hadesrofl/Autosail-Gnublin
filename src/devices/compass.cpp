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
  switch (m_gain)
    {
    case DeviceConfig::COMPASS_GAIN_0_8_8_GA:
      data[1] = static_cast<uint8_t> (DeviceConfig::COMPASS_GAIN_0_8_8_GA);
      m_scale_factor = 0.73;
      break;
    case DeviceConfig::COMPASS_GAIN_1_3_GA:
      data[1] = static_cast<uint8_t> (DeviceConfig::COMPASS_GAIN_1_3_GA);
      m_scale_factor = 0.92;
      break;
    case DeviceConfig::COMPASS_GAIN_1_9_GA:
      data[1] = static_cast<uint8_t> (DeviceConfig::COMPASS_GAIN_1_9_GA);
      m_scale_factor = 1.22;
      break;
    case DeviceConfig::COMPASS_GAIN_2_5_GA:
      data[1] = static_cast<uint8_t> (DeviceConfig::COMPASS_GAIN_2_5_GA);
      m_scale_factor = 1.52;
      break;
    case DeviceConfig::COMPASS_GAIN_4_GA:
      data[1] = static_cast<uint8_t> (DeviceConfig::COMPASS_GAIN_4_GA);
      m_scale_factor = 2.27;
      break;
    case DeviceConfig::COMPASS_GAIN_4_7_GA:
      data[1] = static_cast<uint8_t> (DeviceConfig::COMPASS_GAIN_4_7_GA);
      m_scale_factor = 2.56;
      break;
    case DeviceConfig::COMPASS_GAIN_5_6_GA:
      data[1] = static_cast<uint8_t> (DeviceConfig::COMPASS_GAIN_5_6_GA);
      m_scale_factor = 3.03;
      break;
    case DeviceConfig::COMPASS_GAIN_8_1_GA:
      data[1] = static_cast<uint8_t> (DeviceConfig::COMPASS_GAIN_8_1_GA);
      m_scale_factor = 4.35;
      break;
    default:
      data[1] = static_cast<uint8_t> (DeviceConfig::COMPASS_GAIN_1_3_GA);
      m_scale_factor = 0.92;
    }
  data[0] = COMPASS_CONFIG_B_REGISTER_ADDR;
  ret = Device::write (data, 2);
  if (ret < 0)
    {
      return -1;
    }
  data[0] = COMPASS_MODE_REGISTER_ADDR;
  data[1] = COMPASS_MODE_REGISTER_VALUE;
  ret = Device::write (data, 2);
  if (ret < 0)
    {
      return -1;
    }
  return ret;
}
// Public Functions
Compass::Compass (I2CParameter *interface_parameter, DeviceConfig gain,
		  ComponentDescriptor* descriptor)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (interface_parameter->get_device_file (),
	       interface_parameter->get_address ()));
  set_component_descriptor (descriptor);
  m_gain = gain;
  m_device_parameter = std::unique_ptr<I2CParameter> (interface_parameter);
  init ();
}
uint8_t*
Compass::read_data ()
{
  uint8_t register_data[2] =
    { 0 };
  uint8_t* data = new unsigned char[6];
  for (int16_t i = 0;
      i < static_cast<int16_t> (DeviceConfig::COMPASS_DATA_LENGTH); i++)
    {
      data[i] = 0;
    }
  register_data[0] = COMPASS_X_MSB_REGISTER_ADDR;
  register_data[1] = static_cast<uint8_t> (DeviceConfig::COMPASS_DATA_LENGTH);
  Device::write (register_data, 2);
  Device::read (data, 6);
  int16_t x = (data[1] << 8) | data[0];
  int16_t z = (data[3] << 8) | data[2];
  int16_t y = (data[5] << 8) | data[4];
  int16_t x_gauss = x * m_scale_factor;
  int16_t z_gauss = z * m_scale_factor;
  int16_t y_gauss = y * m_scale_factor;
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

