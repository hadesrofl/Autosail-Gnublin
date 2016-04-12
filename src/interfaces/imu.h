#ifndef KLASSENDIAGRAMM_INTERFACES_I_M_U_H
#define KLASSENDIAGRAMM_INTERFACES_I_M_U_H

#include "i2c.h"
/**
 * @file
 * @class IMU
 * @brief Class for an IMU Module. Uses an I2C Interface for communication and has
 * some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.2
 */
class IMU
{
  /**
   * @private
   */
private:
  /**
   * I2C Interface
   */
  I2C* m_i2c_port;
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param device_file is the name of the file for the device
   * @param slave_address is the address of a slave
   */
  IMU (char* device_file, int slave_address);
  /**
   * Destructor
   */
  ~IMU ();

};

#endif
