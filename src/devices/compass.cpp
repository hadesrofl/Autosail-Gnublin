#include "compass.h"

// Private Functions
int
Compass::init ()
{
  // Set Configuration Register A (8 samples average, 15hz, normal measurement)
  unsigned char register_address = 0x00;
  unsigned char register_value = 0x70;
  int ret = Device::write(&register_address, 1);
  ret = Device::write(&register_value, 1);
  if(ret < 0){
      return -1;
  }
  // Set Configuration Register B (Gain = 5)
  register_address = 0x01;
  //register_value = 0xA0;
  register_value = 0x00;
  ret = Device::write(&register_address, 1);
  ret = Device::write(&register_value, 1);
  if(ret < 0){
      return -1;
  }
  // Set Mode Register to Continous Measurement Mode
  register_address = 0x02;
  register_value = 0x00;
  ret = Device::write(&register_address, 1);
  ret = Device::write(&register_value, 1);
  if(ret < 0){
      return -1;
  }
  return ret;
}
// Public Functions
Compass::Compass (char* device_file, int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (device_file, slave_address));
  set_device_id (Device_ID::COMPASS);
  init();
}
Compass::Compass (int slave_address)
{
  m_interface_port = std::unique_ptr<I2C> (new I2C (slave_address));
  set_device_id (Device_ID::COMPASS);
  init();
}
unsigned char*
Compass::read_data ()
{
  unsigned char register_address = 0x03;
  unsigned char register_value;
  unsigned char* data = new unsigned char[Sensor_Param::COMPASS_DATA_LENGTH];
  // Set Pointer to MSB Output Register for X-Axis
  Device::write (&register_address, 1);
  /*for(int i = 0; i < static_cast<int>(Sensor_Param::COMPASS_DATA_LENGTH);i++){
      Device::read(&data[i], 1);
  }*/
  Device::read (data, static_cast<int> (Sensor_Param::COMPASS_DATA_LENGTH));
  register_address = 0x09;
  Device::write(&register_address, 1);
  Device::read(&register_value, 1);
  int16_t x = (data[0] << 8) | data[1];
  int16_t z = (data[2] << 8) | data[3];
  int16_t y = (data[4] << 8) | data[5];
  std::cout << "X MSB: " << static_cast<int> (data[0]) << " " << std::endl;
  std::cout << "X LSB: " << static_cast<int> (data[1]) << " " << std::endl;
  std::cout << "Z MSB: " << static_cast<int> (data[2]) << " " << std::endl;
  std::cout << "Z LSB: " << static_cast<int> (data[3]) << " " << std::endl;
  std::cout << "Y MSB: " << static_cast<int> (data[4]) << " " << std::endl;
  std::cout << "Y LSB: " << static_cast<int> (data[5]) << " " << std::endl;
  std::cout << "X Int: " << x << " " << std::endl;
  std::cout << "Z Int: " << z << " " << std::endl;
  std::cout << "Y Int: " << y << " " << std::endl;
  std::cout << "Mode Register Value: " << static_cast<int> (register_value)
      << std::endl;
  return data;
}
Compass::~Compass ()
{
}

