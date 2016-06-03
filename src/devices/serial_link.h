#ifndef DEVICES_SERIAL_LINK_H_
#define DEVICES_SERIAL_LINK_H_

#include "../interfaces/spi_master_select.h"
#include "device.h"

/**
 * @file
 * @class SerialLink
 * @brief Class for a SerialLink module. Uses a SPIMasterSelect Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.2
 */
class SerialLink : public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the SerialLink, setting the configuration for the device
   */
  int8_t
  init ();
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param device_file is the name of the SPIMasterSelect Interface this devices listens to
   * @param speed is the speed of the used SPI Bus
   */
  SerialLink (char* device_file, uint16_t speed);
  /**
   * Constructor
   * @param speed is the speed of the used SPI Bus
   */
  SerialLink (uint16_t speed);
  /**
   * TODO: Comment with SerialLink specific register
   * Reads the Data X, Y and Z Register of the SerialLink and returns them as a
   * pointer with allocated memory.
   */
  uint8_t* read_data();
  /**
   * Destructor
   */
  ~SerialLink ();

};



#endif /* DEVICES_SERIAL_LINK_H_ */
