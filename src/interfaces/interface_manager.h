#ifndef INTERFACES_INTERFACE_MANAGER_H_
#define INTERFACES_INTERFACE_MANAGER_H_
#include <map>
#include "interface.h"
#include "../tlve/tlve_protocol.h"

class InterfaceManager
{
private:
  enum class Device
  {
    SERIAL, I2C
  };
  enum class Sensor_Addr
  {
    TEENSY_I2C = 0x55, 		// Teensy Slave Address for I2C
    COMPASS_I2C = 0x1e,		// Address of Digital Compass HMC5883L
    ACC_I2C = 0x53,		// Address of Accelerometer ADXL345
    GYRO_I2C = 0x68		// Address of Gyroscope ITG-3200
  };
  std::map<char*, unsigned char*> m_data_map;
  std::map<char*, Interface*> m_interfaces;
  std::unique_ptr<TLVEProtocol> m_protocol;
  char*
  enum_to_string (Device e);
public:
  InterfaceManager ();
  int
  init_sensors ();
  int
  get_data ();
  int
  read_spi ();
  ~InterfaceManager ();
};

#endif /* INTERFACES_INTERFACE_MANAGER_H_ */
