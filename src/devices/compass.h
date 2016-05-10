#ifndef INTERFACES_COMPASS_H_
#define INTERFACES_COMPASS_H_

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
    * Destructor
    */
   ~Compass();
};



#endif /* INTERFACES_COMPASS_H_ */
