#ifndef DEVICES_G_P_S_H
#define DEVICES_G_P_S_H

#include "../interfaces/serial.h"
#include "device.h"
/**
 * @file
 * @class GPS
 * @brief Class for a GPS Module. Uses a Serial Port for communication but has some
 * functions to handle and transform received data.
 * @author Rene Kremer
 * @version 0.2
 */
class GPS : public Device
{
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param device_file is the name of the device
   * @param baudrate is the baudrate for communication
   */
  GPS (char* device_file, int baudrate);
  /**
   * Constructor
   * @param baudrate is the baudrate for communication
   */
  GPS (int baudrate);
  /**
   * Reads data from the gps for a given length
   * @param buf is the buffer to save the data into
   * @param length is the length of byte to read
   * @return length on success, otherwise -1 on an Error
   */
  int read (unsigned char* buf, int length);
  /**
   * Writes data from the gps for a given length
   * @param buf is the buffer with the data to write
   * @param length is the length of the written bytes
   * @return length on success, otherwise -1 on an Error
   */
  int write (unsigned char* buf, int length);
  /**
   * Destructor
   */
  ~GPS ();

};

#endif
