#ifdef _TEST
#ifndef TEST_I2C_TEST_H_
#define TEST_I2C_TEST_H_

#include <vector>
#include "asserter.h"
#include <iostream>
#include "../interfaces/i2c.h"
#include "../devices/i2c_parameter.h"

/**
 * Slave Address of Teensy for I2C
 */
#define TEENSY_I2C_ 0x55

/**
 * @file
 * @class I2CTest
 * @brief Class for testing purposes of the I2C Class via a TeensyDuino.
 * Implements some functions to assert that the I2C Interface is working.
 * @author Rene Kremer
 * @version 0.2
 */
class I2CTest
  {
    /**
     * @private
     */
  private:
    /**
     * Test for the i2c interface with a Teensyduino. Sends two byte to the teensy,
     * which is configured as echo client and checks if the same bytes are received.
     * If all cases pass the return value is true for success,
     * otherwise false for failure.
     * @return true on success, otherwise false
     */
    bool i2c_teensy_test();
    /**
     * @public
     */
  public:
    /**
     * Constructor
     */
    I2CTest();
    /**
     * Tests all cases and returns a boolean if they passed or not
     * @return true if all cases passed, otherwise false
     */
    bool test_cases();
    /**
     * Destructor
     */
    ~I2CTest();
  };

#endif /* TEST_I2C_TEST_H_ */
#endif
