#ifndef INTERFACES_ACCELEROMETER_H_
#define INTERFACES_ACCELEROMETER_H_

#include "i2c.h"
/**
 * @file
 * @class Accelerometer
 * @brief Class for a Accelerometer Module . Uses a I2C Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.2
 */
class Accelerometer
{
private:
  /**
   * I2C Interface
   */
  std::unique_ptr<I2C> m_i2c_port;
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
    * Destructor
    */
   ~Accelerometer();
};





#endif /* INTERFACES_ACCELEROMETER_H_ */
