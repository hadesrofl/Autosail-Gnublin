#ifndef DEVICES_COMPASS_H_
#define DEVICES_COMPASS_H_

#include "../interfaces/i2c.h"
#include "device.h"
/**
 * @file
 * @class Compass
 * @brief Class for a Compass Module . Uses a I2C Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.2
 */
class Compass : public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the compass, setting the configuration for the device
   */
  int init();
/**
 * @public
 */
public:
   /**
    * Constructor
    * @param device_file is the name of the file for the I2C Interface
    * @param slave_address is the address of the Compass Module
    */
   Compass(char* device_file, int slave_address);
   /**
    * Constructor
    * @param slave_address is the address of the Compass Module
    */
   Compass(int slave_address);
   /**
    * TODO: Comment with compass specific register
    * Reads the Data X, Y and Z Register of the Accelerometer and returns them as a
    * pointer with allocated memory.
    */
   unsigned char* read_data();
   /**
    * Destructor
    */
   ~Compass();
};



#endif /* DEVICES_COMPASS_H_ */
