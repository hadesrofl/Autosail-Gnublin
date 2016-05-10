#ifndef INTERFACES_G_P_S_H
#define INTERFACES_G_P_S_H

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
   * Destructor
   */
  ~GPS ();

};

#endif
