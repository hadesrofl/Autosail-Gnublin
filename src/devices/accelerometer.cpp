#include "accelerometer.h"

// Private Functions
int8_t
Accelerometer::init ()
{
  // Address Power CTL Register to set Link Bit, Measure Bit, and Wake Up to 8Hz
  uint8_t data[2];
  uint8_t register_address = 0x2D;
  uint8_t register_value = 0x38;
  data[0] = register_address;
  data[1] = register_value;
  int ret;
  ret = Device::write (data, 2);
  if (ret < 0)
    {
      return -1;
    }
 /*
  // Set Latent for Tap Event
  register_address = 0x22;
  register_value = 0x15;
  data[0] = register_address;
  data[1] = register_value;
  ret = write (data, 2);
  if (ret < 0)
    {
      return -1;
    }
  // Set Window between Tap Events
  register_address = 0x23;
  register_value = 0x12;
  ret = write (data, 2);
  if (ret < 0)
    {
      return -1;
    }
  // Set Thresh Active
  register_address = 0x24;
  register_value = 0x04;
  data[0] = register_address;
  data[1] = register_value;
  ret = write (data, 2);
  if (ret < 0)
    {
      return -1;
    }
  // Set Thresh Inactive
  register_address = 0x25;
  register_value = 0x02;
  data[0] = register_address;
  data[1] = register_value;
  ret = write (data, 2);
  if (ret < 0)
    {
      return -1;
    }
  // ACT INACT Control
  register_address = 0x27;
  register_value = 0xFF;
  data[0] = register_address;
  data[1] = register_value;
  ret = write (data, 2);
  if (ret < 0)
    {
      return -1;
    }
  // Set Thresh Free Fall
  register_address = 0x28;
  register_value = 0x07;
  data[0] = register_address;
  data[1] = register_value;
  ret = write (data, 2);
  if (ret < 0)
    {
      return -1;
    }
  // Set Time Free Fall
  register_address = 0x29;
  register_value = 0x25;
  data[0] = register_address;
  data[1] = register_value;
  ret = write (data, 2);
  if (ret < 0)
    {
      return -1;
    }
    */
  /**
  // Set Fifo Mode
  register_address = 0x38;
  register_value = 0x40;
  data[0] = register_address;
  data[1] = register_value;
  ret = write (data, 2);
  if (ret < 0)
    {
      return -1;
    }
    */
  // Set Data Format
  register_address = 0x31;
  switch (m_range)
    {
    case Sensor_Param::ACC_RANGE_2G:
      register_value = 0x00;
      m_scale_factor = 3.9;
      break;
    case Sensor_Param::ACC_RANGE_4G:
      register_value = 0x01;
      m_scale_factor = 7.8;
      break;
    case Sensor_Param::ACC_RANGE_8G:
      register_value = 0x02;
      m_scale_factor = 15.6;
      break;
    case Sensor_Param::ACC_RANGE_16G:
      register_value = 0x03;
      m_scale_factor = 31.2;
      break;
    default:
      register_value = 0x00;
      m_scale_factor = 3.9;
    }
  data[0] = register_address;
  data[1] = register_value;
  ret = Device::write (data, 2);
  if (ret < 0)
    {
      return -1;
    }
  return ret;
}
// Public Functions
Accelerometer::Accelerometer (char* device_file, uint8_t slave_address,
			      Sensor_Param range)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (device_file, slave_address));
  set_device_id (Device_ID::ACCELEROMETER);
  m_range = range;
  init ();
}
Accelerometer::Accelerometer (uint8_t slave_address, Sensor_Param range)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C (slave_address));
  set_device_id (Device_ID::ACCELEROMETER);
  m_range = range;
  init ();
}

uint8_t*
Accelerometer::read_data ()
{
  //Set Register Pointer to first Data Register
  uint8_t register_address = 0x32;
  Device::write (&register_address, 1);
  uint8_t* data = new uint8_t[Sensor_Param::ACC_DATA_LENGTH];
  Device::read (data, static_cast<int16_t> (Sensor_Param::ACC_DATA_LENGTH));
  // Get Axis Value therefore shift MSB and OR MSB with LSB
  int16_t raw_x = (data[1] << 8) | data[0];
  int16_t raw_y = (data[3] << 8) | data[2];
  int16_t raw_z = (data[5] << 8) | data[4];
  // Calculate G Value with scale factor as described in the data sheet
  int16_t acc_x = raw_x * m_scale_factor;
  int16_t acc_y = raw_y * m_scale_factor;
  int16_t acc_z = raw_z * m_scale_factor;
  // Split int16_t into unsigned char
  uint8_t msb_x = acc_x >> 8;
  uint8_t lsb_x = acc_x;
  uint8_t msb_y = acc_y >> 8;
  uint8_t lsb_y = acc_y;
  uint8_t msb_z = acc_z >> 8;
  uint8_t lsb_z = acc_z;
#ifdef _DEBUG
  // combine two unsigned chars into one int16_t
  int16_t tsb_x = (msb_x << 8) | lsb_x;
  int16_t tsb_y = (msb_y << 8) | lsb_y;
  int16_t tsb_z = (msb_z << 8) | lsb_z;
  // Calculate the speed of the axis with reference to G = 9.81 m / s^2
  float accel_meter_x = acc_x * MG_SPEED;
  float accel_meter_y = acc_y * MG_SPEED;
  float accel_meter_z = acc_z * MG_SPEED;
  uint8_t x0 = data[0];
  uint8_t x1 = data[1];
  uint8_t y0 = data[2];
  uint8_t y1 = data[3];
  uint8_t z0 = data[4];
  uint8_t z1 = data[5];
  std::cout << "X-Axis LSB: " << x0 << " " << std::endl;
  std::cout << "X-Axis MSB: " << x1 << " " << std::endl;
  std::cout << "Y-Axis LSB: " << y0 << " " << std::endl;
  std::cout << "Y-Axis MSB: " << y1 << " " << std::endl;
  std::cout << "Z-Axis LSB: " << z0 << " " << std::endl;
  std::cout << "Z-Axis MSB: " << z1 << " " << std::endl;
  std::cout << "X-Axis 16 Bit: " << raw_x << std::endl;
  std::cout << "Y-Axis 16 Bit: " << raw_y << std::endl;
  std::cout << "Z-Axis 16 Bit: " << raw_z << std::endl;
  std::cout << "X-Axis in G: " << acc_x << std::endl;
  std::cout << "Y-Axis in G: " << acc_y << std::endl;
  std::cout << "Z-Axis in G: " << acc_z << std::endl;
  std::cout << "X-Axis m/s^2: " << accel_meter_x << std::endl;
  std::cout << "Y-Axis m/s^2: " << accel_meter_y << std::endl;
  std::cout << "Z-Axis m/s^2: " << accel_meter_z << std::endl;
  std::cout << "Z-Axis in G (MSB): " << static_cast<int32_t> (msb_z) << std::endl;
  std::cout << "Z-Axis in G (LSB): " << static_cast<int32_t> (lsb_z) << std::endl;
  std::cout << "X-Axis together as int16: " << static_cast<int16_t> (tsb_x)
      << std::endl;
  std::cout << "Y-Axis together as int16: " << static_cast<int16_t> (tsb_y)
      << std::endl;
  std::cout << "Z-Axis together as int16: " << static_cast<int16_t> (tsb_z)
      << std::endl;
#endif
  data[0] = msb_x;
  data[1] = lsb_x;
  data[2] = msb_y;
  data[3] = lsb_y;
  data[4] = msb_z;
  data[5] = lsb_z;
  return data;
}

Accelerometer::~Accelerometer ()
{
}

