#ifndef DEVICES_GYROSCOPE_H_
#define DEVICES_GYROSCOPE_H_

#include "../interfaces/i2c.h"
#include "device.h"

/**
 * @file
 * @class Gyroscope
 * @brief Class for a Gyroscope Module . Uses a I2C Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.2
 */
class Gyroscope : public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the gyroscope, setting the configuration for the device
   */
  int init();
/**
 * @public
 */
public:
   /**
    * Constructor
    * @param device_file is the name of the file for the I2C Interface
    * @param slave_address is the address of the Gyroscope Module
    */
   Gyroscope(char* device_file, int slave_address);
   /**
    * Constructor
    * @param slave_address is the address of the Gyroscope Module
    */
   Gyroscope(int slave_address);
   /**
    * TODO: Comment with gyroscope specific register
    * Reads the Data X, Y and Z Register of the Accelerometer and returns them as a
    * pointer with allocated memory.
    */
   unsigned char* read_data();
   /**
    * Destructor
    */
   ~Gyroscope();
};



#endif /* DEVICES_GYROSCOPE_H_ */
