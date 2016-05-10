#ifndef DEVICES_DEVICE_MANAGER_H_
#define DEVICES_DEVICE_MANAGER_H_
#include <map>
#include "../interfaces/interface.h"
#include "../tlve/tlve_protocol.h"
#include "device.h"
#include "gps.h"
#include "accelerometer.h"
#include "gyroscope.h"
#include "hygrometer.h"
#include "wind_sensor.h"

/**
 * @file
 * @class DeviceManager
 * @brief Class for the Device Manager. Administrates all devices and reads data or
 * returns devices for special usage.
 * @author Rene Kremer
 * @version 0.2
 */
class DeviceManager
{
  /**
   * @public
   */
public:
  /**
   * Enums of the Sensors
   */
  enum class Sensor
  {
    GPS,
    ACCELEROMETER,
    COMPASS,
    GYROSCOPE,
    HYGROMETER,
    WIND_SENSOR,
    TEENSY_I2C,
    NUM_DEVICES
  };
  /**
   * Constructor
   */
  DeviceManager ();
  /**
   * Inits the Sensors
   */
  int
  init_sensors ();
  /**
   * Gets all data from the sensors
   */
  int
  get_data ();
  /**
   * Gets a single sensor
   * @param s is the sensor to get
   * @return a pointer to the sensor
   */
  Device* get_sensor(Sensor s);
  /**
   * Read Data from the SPI
   * @return read bytes
   */
  int
  read_spi ();
  /**
   * Destructor
   */
  ~DeviceManager ();
  /**
   * @private
   */
private:
  /**
   * Addresses of the Sensors
   */
  enum class Sensor_Addr
  {
    TEENSY_I2C = 0x55, 		// Teensy Slave Address for I2C
    COMPASS_I2C = 0x1e,		// Address of Digital Compass HMC5883L
    ACC_I2C = 0x53,		// Address of Accelerometer ADXL345
    GYRO_I2C = 0x68		// Address of Gyroscope ITG-3200
  };
  /**
   * Map of Sensor Data
   */
  std::map<char*, unsigned char*> m_data_map;
  /**
   * Map of Sensors
   */
  std::map<Sensor, std::unique_ptr<Device>> m_devices;
  /**
   * Pointer to the TLVE Protocol
   */
  std::unique_ptr<TLVEProtocol> m_protocol;

};

#endif /* INTERFACES_INTERFACE_MANAGER_H_ */
