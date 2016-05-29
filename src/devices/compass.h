#ifndef DEVICES_COMPASS_H_
#define DEVICES_COMPASS_H_

#include "../interfaces/i2c.h"
#include "device.h"

/**
 * Address of Config A Register
 */
#define COMPASS_CONFIG_A_REGISTER_ADDR 0x00
/**
 * Set Configuration Register A (1 samples average, 15hz, normal measurement)
 */
#define COMPASS_CONFIG_A_REGISTER_VALUE 0x10
/**
 * Address of Config B Register
 */
#define COMPASS_CONFIG_B_REGISTER_ADDR 0x01
/**
 * Set Configuration Register B (Gain = 2, Range: +- 1.3 Ga (Scale Factor: 0.92))
 */
#define COMPASS_CONFIG_B_REGISTER_VALUE 0x40
/**
 * Address of the Mode Register
 */
#define COMPASS_MODE_REGISTER_ADDR 0x02
/**
 * Set Mode Register to Continous Measurement Mode
 */
#define COMPASS_MODE_REGISTER_VALUE 0x00
#define COMPASS_X_MSB_REGISTER_ADDR 0x03
/**
 * Scaling Factor to calculate LSB to mg
 */
#define COMPASS_SCALING_FACTOR 0.92


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
  int8_t init();
/**
 * @public
 */
public:
   /**
    * Constructor
    * @param device_file is the name of the file for the I2C Interface
    * @param slave_address is the address of the Compass Module
    */
   Compass(char* device_file, uint8_t slave_address);
   /**
    * Constructor
    * @param slave_address is the address of the Compass Module
    */
   Compass(uint8_t slave_address);
   /**
    * TODO: Comment with compass specific register
    * Reads the Data X, Y and Z Register of the Accelerometer and returns them as a
    * pointer with allocated memory.
    */
   uint8_t* read_data();
   /**
    * Destructor
    */
   ~Compass();
};



#endif /* DEVICES_COMPASS_H_ */
