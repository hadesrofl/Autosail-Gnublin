#ifndef DEVICES_DEVICE_MANAGER_H_
#define DEVICES_DEVICE_MANAGER_H_
#include <map>
#include <vector>
#include "../interfaces/interface.h"
#include "device.h"
#include "accelerometer.h"
#include "compass.h"
#include "gps.h"
#include "gyroscope.h"
#include "hygrometer.h"
#include <iostream>
#include <fstream>
#include "../utils/conf_reader.h"

/**
 * Name of default config file for devices
 */
#define DEVICE_CONFIG "config/devices.conf"

/**
 * @file
 * @class DeviceManager
 * @brief Class for the Device Manager. Administrates all devices and returns devices for special usage.
 * @author Rene Kremer
 * @version 0.3
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
   * Gets a single sensor
   * @param id is the sensor to get
   * @return a pointer to the sensor
   */
  Device*
  get_sensor (Descriptor id);
  /**
   * Destructor
   */
  ~DeviceManager ();
  /**
   * @private
   */
private:
  /**
   * Map of Sensors
   */
  std::map<Descriptor, std::unique_ptr<Device>> m_devices;
  /**
   * Inits the Sensors
   * @param devices is a vector of Descriptors
   * @return on succes 1, otherwise -1
   */
  int8_t
  init_sensors (std::vector<Descriptor> devices);
};

#endif /* DEVICES_DEVICE_MANAGER_H_ */
