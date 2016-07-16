#include "gyroscope.h"
#ifdef _DEBUG
#include "../utils/int_converter.h"
#endif

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
Gyroscope::Gyroscope (I2CParameter *interface_parameter,
		      ComponentDescriptor* descriptor)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (interface_parameter->get_device_file (),
	       interface_parameter->get_address ()));
  set_component_descriptor (descriptor);
  m_device_parameter = std::unique_ptr<I2CParameter> (interface_parameter);
  init ();
}
int8_t*
Gyroscope::read_data ()
{
  uint8_t register_address = GYRO_X_MSB_REGISTER;
  uint8_t* buf = new uint8_t[DeviceConfig::GYROSCOPE_DATA_LENGTH];
  int8_t* data = new int8_t[DeviceConfig::GYROSCOPE_DATA_LENGTH];
  for (int16_t i = 0;
      i < static_cast<int16_t> (DeviceConfig::GYROSCOPE_DATA_LENGTH); i++)
    {
      buf[i] = 0;
    }
  Device::write (&register_address, 1);
  Device::read (buf, static_cast<int8_t> (DeviceConfig::GYROSCOPE_DATA_LENGTH));
  int16_t x = (buf[0] << 8) | buf[1];
  int16_t y = (buf[2] << 8) | buf[3];
  int16_t z = (buf[4] << 8) | buf[5];
  int16_t x_degree = static_cast<float> (x)
      / static_cast<float> (GYRO_SCALING_FACTOR);
  int16_t y_degree = static_cast<float> (y)
      / static_cast<float> (GYRO_SCALING_FACTOR);
  int16_t z_degree = static_cast<float> (z)
      / static_cast<float> (GYRO_SCALING_FACTOR);
  int8_t msb_x = (uint16_t) x_degree >> 8;
  int8_t lsb_x = x_degree;
  int8_t msb_y = (uint16_t) y_degree >> 8;
  int8_t lsb_y = y_degree;
  int8_t msb_z = (uint16_t) z_degree >> 8;
  int8_t lsb_z = z_degree;
#ifdef _DEBUG
  int16_t tsb_x = (msb_x << 8) | lsb_x;
  int16_t tsb_y = (msb_y << 8) | lsb_y;
  int16_t tsb_z = (msb_z << 8) | lsb_z;
  std::cout << "X MSB: " << static_cast<int> (buf[0]) << " " << std::endl;
  std::cout << "X LSB: " << static_cast<int> (buf[1]) << " " << std::endl;
  std::cout << "Y MSB: " << static_cast<int> (buf[2]) << " " << std::endl;
  std::cout << "Y LSB: " << static_cast<int> (buf[3]) << " " << std::endl;
  std::cout << "Z MSB: " << static_cast<int> (buf[4]) << " " << std::endl;
  std::cout << "Z LSB: " << static_cast<int> (buf[5]) << " " << std::endl;
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
#ifdef _DEBUG
  int8_t* tmp = new int8_t[2];
  tmp[0] = msb_x;
  tmp[1] = lsb_x;
  int16_t test_x = IntConverter::int8_to_int16(tmp);
  tmp[0] = msb_y;
  tmp[1] = lsb_y;
  int16_t test_y = IntConverter::int8_to_int16(tmp);
  tmp[0] = msb_z;
  tmp[1] = lsb_z;
  int16_t test_z = IntConverter::int8_to_int16(tmp);
  delete[] tmp;
  std::cout << "Returned:" <<std::endl;
  std::cout << "X-Axis LSB: " << static_cast<int32_t>(data[1]) << " " << std::endl;
  std::cout << "X-Axis MSB: " << static_cast<int32_t>(data[0]) << " " << std::endl;
  std::cout << "Y-Axis LSB: " << static_cast<int32_t>(data[3]) << " " << std::endl;
  std::cout << "Y-Axis MSB: " << static_cast<int32_t>(data[2]) << " " << std::endl;
  std::cout << "Z-Axis LSB: " << static_cast<int32_t>(data[5]) << " " << std::endl;
  std::cout << "Z-Axis MSB: " << static_cast<int32_t>(data[4]) << " " << std::endl;
  std::cout << "Test X: " << test_x << " " << std::endl;
  std::cout << "Test Y: " << test_y << " " << std::endl;
  std::cout << "Test Z: " << test_z << " " << std::endl;
#endif
  delete[] buf;
  return data;
}
Gyroscope::~Gyroscope ()
{
}

