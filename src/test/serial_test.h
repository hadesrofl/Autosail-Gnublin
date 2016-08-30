/**
 * Copyright 2016 Rene Kremer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
 * @brief Class for testing purposes of the Serial Classes via XBEE Modules.
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
