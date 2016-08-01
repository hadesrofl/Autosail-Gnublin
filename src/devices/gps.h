#ifndef DEVICES_G_P_S_H
#define DEVICES_G_P_S_H

#include "../interfaces/serial.h"
#include "device.h"
#include "serial_parameter.h"
#include <stdlib.h>
#include <sstream>
#include <string>
#include <fstream>
#include <unistd.h>
#include "gps_data.h"
#include "../utils/int_converter.h"

/**
 * Size of a command to set via system command
 */
#define COMMAND_SIZE 50
/**
 * Shift value for latitude and longitude to get decimal value out of float
 */
#define DECIMAL_SHIFT_POSITION 100000
/**
 * Shift value for speed to get decimal value out of float
 */
#define DECIMAL_SHIFT_SPEED 100
/**
 * Program to get data from gps via gpsd
 */
#define SUB_PROGRAM "./gpsd-client"
/**
 * Temporary file to save data from SUB_PROGRAM and read from
 */
#define TMP_DATA_FILE "tmp/gps-data.txt"

/**
 * @file
 * @class GPS
 * @ingroup Devices
 * @brief Class for a GPS Module. Uses a Serial Port for communication but has some
 * functions to handle and transform received data.
 * @author Rene Kremer
 * @version 0.35
 */
class GPS : virtual public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the gps, setting the configuration for the device
   * @return 1 on success, otherwise -1
   */
  int8_t
  init ();
  /**
   * is this device activated?
   */
  bool m_active;
  /**
   * Last read data from GPS
   */
  gps_data_t* m_last_data;
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param interface_parameter are the parameters for the interface
   * @param descriptor is a pointer to the ComponentDescriptor of this device
   */
  GPS (SerialParameter *interface_parameter, ComponentDescriptor* descriptor);
  /**
   * Reads data via the SUB_PROGRAM and the TMP_DATA_FILE into an list of int8_t.
   * Index 0 is the fix mode of the gps. Index 1 to 4 are int8_t of the int32_t value for latitude,
   * 5 to 8 for longitude, 9 to 12 speed and 13 to 16 for timestamp.
   * @return a list of int8_t containing 4 int32_t byte splitted in int8_t
   */
  std::vector<int8_t>
  read_data ();
  /**
   * Gets the last read data from the gps
   * @return a struct of gps_data_t of the last read data
   */
  inline gps_data_t*
  get_last_data () const
  {
    return m_last_data;
  }
  /**
   * Returns a bool if the GPS is active or not
   * @return m_active determining if the GPS is active (true) or not (false)
   */
  inline bool
  is_active () const
  {
    return m_active;
  }
  /**
   * Destructor
   */
  ~GPS ();

};

#endif
