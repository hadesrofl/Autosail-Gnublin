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
Gyroscope::Gyroscope (I2CParameter *interface_parameter,
		      ComponentDescriptor* descriptor)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (interface_parameter->get_device_file (),
	       interface_parameter->get_address ()));
  set_component_descriptor (descriptor);
  m_device_parameter = std::unique_ptr<I2CParameter> (interface_parameter);
  m_datastructure_id = DataStructureIdentifier::INT16;
  init ();
}
std::vector<int8_t>
Gyroscope::read_data ()
{
  uint8_t register_address = GYRO_X_MSB_REGISTER;
  uint8_t* buf = new uint8_t[DeviceConfig::GYROSCOPE_DATA_LENGTH];
  std::vector<int8_t> data;
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
  data.push_back(msb_x);
  data.push_back(lsb_x);
  data.push_back(msb_y);
  data.push_back(lsb_y);
  data.push_back(msb_z);
  data.push_back(lsb_z);
  delete[] buf;
  return data;
}
Gyroscope::~Gyroscope ()
{
}

