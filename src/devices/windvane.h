#ifndef DEVICES_WINDVANE_H_
#define DEVICES_WINDVANE_H_

#include "../interfaces/i2c.h"
#include "device.h"
#include "i2c_parameter.h"

/**
 * @file
 * @class WindVane
 * @brief Class for a WindVane module. Uses a I2C Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.2
 */
class WindVane : virtual public Device
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
   * @param interface_parameter are the parameters for the I2C Interface
   */
  WindVane (I2CParameter *interface_parameter);
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
