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

/**
 * Name of default config file for devices
 */
#define DEVICE_CONFIG "config/devices.conf"
/**
 * Shift for integer numbers ( 48 in ASCII = 0 )
 */
#define ASCII_SHIFT 48
/**
 * Shift for Decimal System Numbers to read one after another
 */
#define DECIMAL_SHIFT 10

/**
 * @file
 * @class DeviceManager
 * @brief Class for the Device Manager. Administrates all devices and returns devices for special usage.
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
   * Map to store the config values to a certain key
   */
  std::vector<uint8_t*> m_config_values;
  /**
   * Stores a line of the config file into the map of values
   * @param key is the key of this key-value pair
   * @param value is the value of this key-value pair
   * @return 1 on success otherwise -1
   */
  int8_t
  store_line (uint8_t* value,
	      uint16_t value_length);
  /**
   * Reads a given config file. The Id of a Device has to be the same number as given in Sensor_Params.h
   * With the following Syntax:
   *
   * Device = Accelerometer
   * ID = 0
   *
   * @param fd is the config file to read
   * @param devices is an array containing all ids of the connected devices
   * @return on success 1, otherwise -1
   */
  int8_t
  read_config (const char* file, Descriptor devices[]);

  /**
   * Inits the Sensors
   * @param devices is an array of device ids
   * @return on succes 1, otherwise -1
   */
  int8_t
  init_sensors (Descriptor devices[]);
  /**
   * Clears the content of an array for a given length. Writes 0 into the index of the given array
   * @param array is the array to be cleared
   * @param length is the length to clear
   * @return the length of cleared byte
   */
  uint16_t
  clear_array (uint8_t array[], uint16_t length);
  /**
   * Checks if an array is empty. An array is empty if there is no other character than 0 stored in every index.
   * @param array is the array to check
   * @param length is the length of the array
   * @return true if it is empty, otherwise false
   */
  bool
  array_is_empty (uint8_t array[], uint16_t length);

};

#endif /* DEVICES_DEVICE_MANAGER_H_ */
