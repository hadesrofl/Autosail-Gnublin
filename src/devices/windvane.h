#ifndef DEVICES_WINDVANE_H_
#define DEVICES_WINDVANE_H_

#include "../interfaces/i2c.h"
#include "device.h"

/**
 * @file
 * @class WindVane
 * @brief Class for a WindVane module. Uses a I2C Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.2
 */
class WindVane : public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the wind vane, setting the configuration for the device
   */
  int8_t
  init ();
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param device_file is the name of the I2C Interface this devices listens to
   * @param slave_address is the address of the WindVane module
   */
  WindVane (char* device_file, uint8_t slave_address);
  /**
   * Constructor
   * @param slave_address is the address of the WindVane module
   */
  WindVane (uint8_t slave_address);
  /**
   * TODO: Comment with WindVane specific register
   * Reads the Data X, Y and Z Register of the WindVane and returns them as a
   * pointer with allocated memory.
   */
  uint8_t* read_data();
  /**
   * Destructor
   */
  ~WindVane ();

};



#endif /* DEVICES_WINDVANE_H_ */
