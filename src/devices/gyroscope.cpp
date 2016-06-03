#include "gyroscope.h"

// Private Functions
int8_t
Gyroscope::init ()
{
// Set DLPF Full Scale Register to Range = +- 2000 deg/s , 42Hz Low Pass Filter, 1kHz Internal Sample Rate
  uint8_t register_address = 0x16;
  uint8_t register_data;
  uint8_t* data = new uint8_t[2];
  data[0] = register_address;
  data[1] = register_data;
  Device::write (data, 1);
  Device::read (&register_data, 1);
  if (register_data != GYRO_DLPF_FS_REGISTER_VALUE)
    {
      data[1] = GYRO_DLPF_FS_REGISTER_VALUE;
      Device::write (data, 2);
    }
  delete[] data;
  return 1;
}
// Public Functions
Gyroscope::Gyroscope (I2CParameter *interface_parameter)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (interface_parameter->get_device_file(), interface_parameter->get_address()));
  set_device_id (Descriptor::GYROSCOPE);
  m_device_parameter = std::unique_ptr<I2CParameter> (interface_parameter);
  init ();
}
uint8_t*
Gyroscope::read_data ()
{
  uint8_t register_address = GYRO_X_MSB_REGISTER;
  uint8_t* data =
      new unsigned char[static_cast<int8_t> (Device_Config::GYROSCOPE_DATA_LENGTH)];
  for (int16_t i = 0;
      i < static_cast<int16_t> (Device_Config::GYROSCOPE_DATA_LENGTH); i++)
    {
      data[i] = 0;
    }
  Device::write (&register_address, 1);
  Device::read (data,
		static_cast<int8_t> (Device_Config::GYROSCOPE_DATA_LENGTH));
  int16_t x = (data[1] << 8) | data[0];
  int16_t y = (data[3] << 8) | data[2];
  int16_t z = (data[5] << 8) | data[4];
  int16_t x_degree = static_cast<float> (x)
      / static_cast<float> (GYRO_SCALING_FACTOR);
  int16_t y_degree = static_cast<float> (y)
      / static_cast<float> (GYRO_SCALING_FACTOR);
  int16_t z_degree = static_cast<float> (z)
      / static_cast<float> (GYRO_SCALING_FACTOR);
  uint8_t msb_x = x_degree >> 8;
  uint8_t lsb_x = x_degree;
  uint8_t msb_y = y_degree >> 8;
  uint8_t lsb_y = y_degree;
  uint8_t msb_z = z_degree >> 8;
  uint8_t lsb_z = z_degree;
#ifdef _DEBUG
  int16_t tsb_x = (msb_x << 8) | lsb_x;
  int16_t tsb_y = (msb_y << 8) | lsb_y;
  int16_t tsb_z = (msb_z << 8) | lsb_z;

  std::cout << "X MSB: " << static_cast<int> (data[0]) << " " << std::endl;
  std::cout << "X LSB: " << static_cast<int> (data[1]) << " " << std::endl;
  std::cout << "Y MSB: " << static_cast<int> (data[2]) << " " << std::endl;
  std::cout << "Y LSB: " << static_cast<int> (data[3]) << " " << std::endl;
  std::cout << "Z MSB: " << static_cast<int> (data[4]) << " " << std::endl;
  std::cout << "Z LSB: " << static_cast<int> (data[5]) << " " << std::endl;
  std::cout << "X 16 bit: " << x << std::endl;
  std::cout << "Y 16 bit: " << y << std::endl;
  std::cout << "Z 16 bit: " << z << std::endl;
  std::cout << "X Degrees per Second: " << x_degree << std::endl;
  std::cout << "Y Degrees per Second: " << y_degree << std::endl;
  std::cout << "Z Degrees per Second: " << z_degree << std::endl;
  std::cout << "X together again: " << static_cast<int> (tsb_x) << std::endl;
  std::cout << "Y together again: " << static_cast<int> (tsb_y) << std::endl;
  std::cout << "Z together again: " << static_cast<int> (tsb_z) << std::endl;
#endif
  data[0] = msb_x;
  data[1] = lsb_x;
  data[2] = msb_y;
  data[3] = lsb_y;
  data[4] = msb_z;
  data[5] = lsb_z;
  return data;
}
Gyroscope::~Gyroscope ()
{
}

