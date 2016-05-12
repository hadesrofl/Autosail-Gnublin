#ifndef DEVICES_ACCELEROMETER_H_
#define DEVICES_ACCELEROMETER_H_

#include "../interfaces/i2c.h"
#include "device.h"
/**
 * @file
 * @class Accelerometer
 * @brief Class for a Accelerometer Module . Uses a I2C Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.2
 */
class Accelerometer : public Device
{
/**
 * @public
 */
public:
   /**
    * Constructor
    * @param device_file is the name of the file for the I2C Interface
    * @param slave_address is the address of the Accelerometer Module
    */
   Accelerometer(char* device_file, int slave_address);
   /**
    * Constructor
    * @param slave_address is the address of the Accelerometer Module
    */
   Accelerometer(int slave_address);
   /**
    * Reads data from the accelerometer for a given length
    * @param buf is the buffer to save the data into
    * @param length is the length of byte to read
    * @return length on success, otherwise -1 on an Error
    */
   int read (unsigned char* buf, int length);
   /**
    * Writes data from the accelerometer for a given length
    * @param buf is the buffer with the data to write
    * @param length is the length of the written bytes
    * @return length on success, otherwise -1 on an Error
    */
   int write (unsigned char* buf, int length);
   /**
    * Destructor
    */
   ~Accelerometer();
};





#endif /* DEVICES_ACCELEROMETER_H_ */
