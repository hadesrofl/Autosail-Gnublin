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
    * Reads data from the compass for a given length
    * @param buf is the buffer to save the data into
    * @param length is the length of byte to read
    * @return length on success, otherwise -1 on an Error
    */
   int
   read (unsigned char* buf, int length);
   /**
    * Writes data from the compass for a given length
    * @param buf is the buffer with the data to write
    * @param length is the length of the written bytes
    * @return length on success, otherwise -1 on an Error
    */
   int
   write (unsigned char* buf, int length);
   /**
    * Destructor
    */
   ~Compass();
};



#endif /* DEVICES_COMPASS_H_ */
