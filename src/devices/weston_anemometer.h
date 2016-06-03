#ifndef DEVICES_WESTON_ANEMOMETER_H_
#define DEVICES_WESTON_ANEMOMETER_H_

#include "../interfaces/i2c.h"
#include "device.h"

/**
 * @file
 * @class WestonAnemometer
 * @brief Class for a WestonAnemometer module. Uses a I2C Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.2
 */
class WestonAnemometer : public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the weston anemometer, setting the configuration for the device
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
   * @param slave_address is the address of the WestonAnemometer module
   */
  WestonAnemometer (char* device_file, uint8_t slave_address);
  /**
   * Constructor
   * @param slave_address is the address of the WestonAnemometer module
   */
  WestonAnemometer (uint8_t slave_address);
  /**
   * TODO: Comment with WestonAnemometer specific register
   * Reads the Data X, Y and Z Register of the WestonAnemometer and returns them as a
   * pointer with allocated memory.
   */
  uint8_t* read_data();
  /**
   * Destructor
   */
  ~WestonAnemometer ();

};



#endif /* DEVICES_WESTON_ANEMOMETER_H_ */
