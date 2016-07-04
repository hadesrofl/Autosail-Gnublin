#ifndef UTILS_CONF_READER_H_
#define UTILS_CONF_READER_H_

#include <vector>
#include <fstream>
#include <iostream>
#include <stdint.h>

/**
 * Size of an entry of a component in the config file
 */
#define DATA_ENTRIES_PER_COMPONENT 6

/**
 * Shift for integer numbers ( 48 in ASCII = 0 )
 */
#define ASCII_SHIFT 48
/**
 * Shift for Decimal System Numbers to read one after another
 */
#define DECIMAL_SHIFT 10

/**
 * Name of default config file for devices
 */
#define DEVICE_CONFIG "config/devices.conf"

/**
 * @file
 * @class ConfReader
 * @brief Class for a ConfReader. Reads the config file for the devices.
 * A Conf File starts in the first line and then has a name of a device followed
 * by 6 data lines. It ends with a new line. If some data is not specified it has to
 * be coded with '0x00'. Single Digits and Hex are allowed,
 * no double digits supported. Syntax examples:
 * <br/>
 * <br/>
 * Device = [Name]
 * <br/>
 * Component Class = 0x[First Number][Second Number]
 * <br/>
 * Component Attribute = 0x[First Number][Second Number]
 * <br/>
 * Component Number = 0x[First Number][Second Number]
 * <br/>
 * Communication Number = 0x[First Number][Second Number]
 * <br/>
 * Config = [Number specified in Device_Config]
 * <br/>
 * [new line (needed!)]
 * <br/>
 *
 * Example Code:
 *  <pre>
 *   <code>
 * Device = Accelerometer
 * Component Class = 0x55
 * Component Attribute = 0x07
 * Component Number = 1
 * Communication Number = 1
 * Config = 2
 *
 * Device = Compass
 * Component Class = 0x55
 * Component Attribute = 0x06
 * Component Number = 1
 * Communication Number = 2
 * Config = 0
 *
 * Device = Gyroscope
 * Component Class = 0x55
 * Component Attribute = 0x05
 * Component Number = 1
 * Communication Number = 3
 * Config = 0
 *   </code>
 *  </pre>
 * @author Rene Kremer
 * @version 0.2
 */
class ConfReader
{
  /**
   * @private
   */
private:
  /**
   * Map to store the config values to a certain key
   */
  std::vector<uint8_t*> m_config_values;
  /**
   * File to read
   */
  const char* m_file;
  /**
   * Stores a line of the config file into the map of values
   * @param key is the key of this key-value pair
   * @param value is the value of this key-value pair
   * @return 1 on success otherwise -1
   */
  int8_t
  store_line (uint8_t* value, uint16_t value_length);
  /**
   * Reads a line of the raw config values called m_config_values and adds them to
   * the vector called values
   * @param values is a pointer of a vector containing the parsed values
   * @param index is the current index of m_config_values
   */
  void
  read_line (std::vector<uint8_t> *values, uint32_t index);
  /**
   * Reads a given config file. The Id of a Device has to be the same number as given in Sensor_Params.h
   * With the following Syntax:
   *
   * Device = Accelerometer
   * ID = 0
   *
   * @return on success 1, otherwise -1
   */
  int8_t
  read_config ();
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
  /**
   * @protected
   */
protected:
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param file is the file to read
   */
  ConfReader (const char* file);
  /**
   * Gets a vector with all descriptors listed in the config file
   * @return a vector with all descriptors of the config file in
   * 5 byte representation (component class, component attribute, component number,
   * communication number, config of device)
   * Communication Number and Config are 0 if these are not needed
   * (like for non communicating components or devices without configuration)
   */
  std::vector<uint8_t>
  get_descriptors ();
  /**
   * Destructor
   */
  ~ConfReader ();
};

#endif /* UTILS_CONF_READER_H_ */
