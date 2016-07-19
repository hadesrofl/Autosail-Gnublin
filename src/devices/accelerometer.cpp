#include "accelerometer.h"
#ifdef _DEBUG
#include "../utils/int_converter.h"
#endif

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
  int16_t raw_z = (buf[5] << 8) | buf[4];
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
#ifdef _DEBUG
  // combine two unsigned chars into one int16_t
  int16_t tsb_x = (msb_x << 8) | lsb_x;
  int16_t tsb_y = (msb_y << 8) | lsb_y;
  int16_t tsb_z = (msb_z << 8) | lsb_z;
  // Calculate the speed of the axis with reference to G = 9.81 m / s^2
  float accel_meter_x = acc_x * MG_SPEED;
  float accel_meter_y = acc_y * MG_SPEED;
  float accel_meter_z = acc_z * MG_SPEED;
  uint8_t x0 = buf[0];
  uint8_t x1 = buf[1];
  uint8_t y0 = buf[2];
  uint8_t y1 = buf[3];
  uint8_t z0 = buf[4];
  uint8_t z1 = buf[5];
  std::cout << "X-Axis LSB: " << static_cast<int32_t>(x0) << " " << std::endl;
  std::cout << "X-Axis MSB: " << static_cast<int32_t>(x1) << " " << std::endl;
  std::cout << "Y-Axis LSB: " << static_cast<int32_t>(y0) << " " << std::endl;
  std::cout << "Y-Axis MSB: " << static_cast<int32_t>(y1) << " " << std::endl;
  std::cout << "Z-Axis LSB: " << static_cast<int32_t>(z0) << " " << std::endl;
  std::cout << "Z-Axis MSB: " << static_cast<int32_t>(z1) << " " << std::endl;
  std::cout << "X-Axis 16 Bit: " << raw_x << std::endl;
  std::cout << "Y-Axis 16 Bit: " << raw_y << std::endl;
  std::cout << "Z-Axis 16 Bit: " << raw_z << std::endl;
  std::cout << "X-Axis in G: " << acc_x << std::endl;
  std::cout << "Y-Axis in G: " << acc_y << std::endl;
  std::cout << "Z-Axis in G: " << acc_z << std::endl;
  std::cout << "X-Axis m/s^2: " << accel_meter_x << std::endl;
  std::cout << "Y-Axis m/s^2: " << accel_meter_y << std::endl;
  std::cout << "Z-Axis m/s^2: " << accel_meter_z << std::endl;
  std::cout << "Z-Axis in G (MSB): " << static_cast<int32_t> (msb_z)
  << std::endl;
  std::cout << "Z-Axis in G (LSB): " << static_cast<int32_t> (lsb_z)
  << std::endl;
  std::cout << "X-Axis together as int16: " << static_cast<int16_t> (tsb_x)
  << std::endl;
  std::cout << "Y-Axis together as int16: " << static_cast<int16_t> (tsb_y)
  << std::endl;
  std::cout << "Z-Axis together as int16: " << static_cast<int16_t> (tsb_z)
  << std::endl;
#endif
  data.push_back(msb_x);
  data.push_back(lsb_x);
  data.push_back(msb_y);
  data.push_back(lsb_y);
  data.push_back(msb_z);
  data.push_back(lsb_z);
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

Accelerometer::~Accelerometer ()
{
}

