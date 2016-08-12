#include "accelerometer.h"

// Private Functions
int8_t
Accelerometer::init ()
{
  // Address Power CTL Register to set Link Bit, Measure Bit, and Wake Up to 8Hz
  uint8_t data[2] =
    { 0 };
  data[0] = ACC_POWER_CTL_REGISTER_ADDR;
  data[1] = ACC_POWER_CTL_REGISTER_VALUE;
  int ret;
  ret = Device::write (data, 2);
  if (ret < 0)
    {
      return -1;
    }
  // Set Data Format
  uint8_t register_value;
  switch (m_range)
    {
    case DeviceConfig::ACC_RANGE_2G:
      register_value = static_cast<uint8_t> (DeviceConfig::ACC_RANGE_2G);
      m_scale_factor = 3.9;
      break;
    case DeviceConfig::ACC_RANGE_4G:
      register_value = static_cast<uint8_t> (DeviceConfig::ACC_RANGE_4G);
      m_scale_factor = 7.8;
      break;
    case DeviceConfig::ACC_RANGE_8G:
      register_value = static_cast<uint8_t> (DeviceConfig::ACC_RANGE_8G);
      m_scale_factor = 15.6;
      break;
    case DeviceConfig::ACC_RANGE_16G:
      register_value = static_cast<uint8_t> (DeviceConfig::ACC_RANGE_16G);
      m_scale_factor = 31.2;
      break;
    default:
      register_value = static_cast<uint8_t> (DeviceConfig::ACC_RANGE_2G);
      m_scale_factor = 3.9;
    }
  data[0] = ACC_DATA_FORMAT_REGISTER_ADDR;
  data[1] = register_value;
  ret = Device::write (data, 2);
  if (ret < 0)
    {
      return -1;
    }
  return ret;
}
// Public Functions
Accelerometer::Accelerometer (I2CParameter *interface_parameter,
			      DeviceConfig range,
			      ComponentDescriptor* descriptor)
{

  m_interface_port = std::unique_ptr<I2C> (
      new I2C (interface_parameter->get_device_file (),
	       interface_parameter->get_address ()));
  m_device_parameter = std::unique_ptr<I2CParameter> (interface_parameter);
  set_component_descriptor (descriptor);
  m_range = range;
  m_datastructure_id = DataStructureIdentifier::INT16;
  init ();
}

std::vector<int8_t>
Accelerometer::read_data ()
{
  //Set Register Pointer to first Data Register
  uint8_t register_address = ACC_X_LSB_REGISTER_ADDR;
  Device::write (&register_address, 1);
  uint8_t* buf = new uint8_t[DeviceConfig::ACC_DATA_LENGTH];
  std::vector<int8_t> data;
  Device::read (buf, static_cast<int16_t> (DeviceConfig::ACC_DATA_LENGTH));
  // Get Axis Value therefore shift MSB and OR MSB with LSB
  int16_t raw_x = (buf[1] << 8) | buf[0];
  int16_t raw_y = (buf[3] << 8) | buf[2];
  int16_t raw_z = (buf[5] << 8) | buf[3];
  // Calculate G Value with scale factor as described in the data sheet
  int16_t acc_x = raw_x * m_scale_factor;
  int16_t acc_y = raw_y * m_scale_factor;
  int16_t acc_z = raw_z * m_scale_factor;
  // Split int16_t into unsigned char
  int8_t msb_x = (uint16_t) acc_x >> 8;
  int8_t lsb_x = acc_x;
  int8_t msb_y = (uint16_t) acc_y >> 8;
  int8_t lsb_y = acc_y;
  int8_t msb_z = (uint16_t) acc_z >> 8;
  int8_t lsb_z = acc_z;
  data.push_back(msb_x);
  data.push_back(lsb_x);
  data.push_back(msb_y);
  data.push_back(lsb_y);
  data.push_back(msb_z);
  data.push_back(lsb_z);
  delete[] buf;
  return data;
}

Accelerometer::~Accelerometer ()
{
}

