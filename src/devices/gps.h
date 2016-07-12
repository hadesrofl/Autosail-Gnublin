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

#define COMMAND_SIZE 50
#define SUB_PROGRAM "/home/apps/gpsd_client"
#define TMP_DATA_FILE "/home/apps/gps_data.txt"

/**
 * @file
 * @class GPS
 * @brief Class for a GPS Module. Uses a Serial Port for communication but has some
 * functions to handle and transform received data.
 * @author Rene Kremer
 * @version 0.3
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
   * Reads data from the gps for a given length
   * @param buf is the buffer to save the data into
   * @param length is the length of byte to read
   * @return length on success, otherwise -1 on an Error
   */
  int8_t
  read (uint8_t* buf, int16_t length);
  /**
   * TODO: Comment with gps specific register
   * Reads the Data X, Y and Z Register of the Accelerometer and returns them as a
   * pointer with allocated memory.
   */
  uint8_t*
  read_data ();
  /**
   * TODO: Comment with gps specific register
   * Reads the Data X, Y and Z Register of the Accelerometer and returns them as a
   * pointer with allocated memory.
   */
  int8_t
  read_data (gps_data_t *data);
  /**
   * Writes data from the gps for a given length
   * @param buf is the buffer with the data to write
   * @param length is the length of the written bytes
   * @return length on success, otherwise -1 on an Error
   */
  int8_t
  write (uint8_t* buf, int16_t length);
  /**
   * Destructor
   */
  ~GPS ();

};

#endif
