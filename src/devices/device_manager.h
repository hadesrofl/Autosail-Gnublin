#ifndef DEVICES_DEVICE_MANAGER_H_
#define DEVICES_DEVICE_MANAGER_H_
#include <map>
#include <vector>
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
  Device* get_sensor(Device_ID s);
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
   * Map of Sensor Data
   */
  std::map<char*, unsigned char*> m_data_map;
  /**
   * Map of Sensors
   */
  std::map<Device_ID, std::unique_ptr<Device>> m_devices;
  /**
   * Pointer to the TLVE Protocol
   */
  std::unique_ptr<TLVEProtocol> m_protocol;
  /**
   * Allocates memory for a new pointer to the copied data and deletes the old pointer.
   * @param src is the old pointer and source to the data
   * @param length is the length of the data
   * @return a new pointer pointing to the copied data.
   */
  unsigned char* copy_data(unsigned char* src, int length);

};

#endif /* DEVICES_DEVICE_MANAGER_H_ */
