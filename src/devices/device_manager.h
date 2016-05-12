#ifndef DEVICES_DEVICE_MANAGER_H_
#define DEVICES_DEVICE_MANAGER_H_
#include <map>
#include "../interfaces/interface.h"
#include "../tlve/tlve_protocol.h"
#include "device.h"
#include "accelerometer.h"
#include "compass.h"
#include "gps.h"
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
    ACCELEROMETER,
    COMPASS,
    GPS,
    GYROSCOPE,
    HYGROMETER,
    WIND_SENSOR,
#ifdef _TEST
    TEENSY_I2C,
#endif
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
  enum class Sensor_Params
  {
#ifdef _TEST
    TEENSY_ADDR = 0x55, 	// Teensy Slave Address for I2C
#endif
    COMPASS_ADDR = 0x1E,	// Address of Digital Compass HMC5883L
    ACC_ADDR = 0x53,		// Address of Accelerometer ADXL345
    GYRO_ADDR = 0x68,		// Address of Gyroscope ITG-3200
    GPS_BAUD = 38400,		// Baudrate of GPS
    //HYGRO_ADDR = 0x00,		// FILLER VALUE Address of Hygrometer
    //WIND_SENSOR_ADDR = 0x00	// FILLER VALUE Address of Wind Sensor
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

#endif /* DEVICES_DEVICE_MANAGER_H_ */
