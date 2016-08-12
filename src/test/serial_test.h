#ifdef _TEST
#ifndef TEST_SERIAL_TEST_H_
#define TEST_SERIAL_TEST_H_

#include <vector>
#include "asserter.h"
#include <iostream>
#include "../interfaces/serial.h"
#include "../devices/serial_parameter.h"
#include "../devices/device_config.h"

/**
 * @file
 * @class SerialTest
 * @brief Class for testing purposes the Serial Classes via XBEE Modules.
 * @author Rene Kremer
 * @version 0.2
 */
class SerialTest
  {
    /**
     * @private
     */
  private:
    /**
     * Test for the Serial interface with XBEE Modules.
     * A check via log of XCTU Serial Console is needed.
     * @return true on success, otherwise false
     */
    bool xbee_test();
    /**
     * @public
     */
  public:
    /**
     * Constructor
     */
    SerialTest();
    /**
     * Tests all cases and returns a boolean if they passed or not
     * @return true if all cases passed, otherwise false
     */
    bool test_cases();
    /**
     * Destructor
     */
    ~SerialTest();
  };

#endif /* TEST_SERIAL_TEST_H_ */
#endif
