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
#define DECIMAL_SHIFT_SPEED 1000
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
   */
  int8_t
  init ();
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
   * Index 0 to 3 are int8_t of the int32_t value for latitude, 4 to 7 for longitude,
   * 8 to 11 speed and 12 to 15 for timestamp.
   * @return a list of int8_t containing 4 int32_t byte splitted in int8_t
   */
  std::vector<int8_t>
  read_data ();
  /**
   * Destructor
   */
  ~GPS ();

};

#endif
