#ifndef INTERFACES_GYROSCOPE_H_
#define INTERFACES_GYROSCOPE_H_

#include "i2c.h"

/**
 * @file
 * @class Gyroscope
 * @brief Class for a Gyroscope Module . Uses a I2C Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.2
 */
class Gyroscope
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
    * @param slave_address is the address of the Gyroscope Module
    */
   Gyroscope(char* device_file, int slave_address);
   /**
    * Constructor
    * @param slave_address is the address of the Gyroscope Module
    */
   Gyroscope(int slave_address);
   /**
    * Destructor
    */
   ~Gyroscope();
};



#endif /* INTERFACES_GYROSCOPE_H_ */
