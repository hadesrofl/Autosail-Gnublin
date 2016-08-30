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
#ifndef TEST_COMMUNICATION_TABLE_TEST_H_
#define TEST_COMMUNICATION_TABLE_TEST_H_

#include <iostream>
#include <vector>
#include "asserter.h"
#include "../loader/loader.h"
#include "../devices/device_manager.h"
#include "../communication/protocol_engine.h"
/**
 * @file
 * @class CommunicationTableTest
 * @brief Class for testing purposes of the communication tables.
 * Implements some functions to assert that the forward and backward communication
 * table is working correctly.
 * @author Rene Kremer
 * @version 0.2
 */
class CommunicationTableTest
  {
    /**
     * @private
     */
  private:
    /**
     * Tests three devices if they are reachable via ComponentDescriptorEnum
     * and DeviceManager. After that checks if they are correctly given a communication
     * number in the forward communication table of the ProtocolEngine. In the end
     * checks if the devices are reachable via the communication number and the
     * backward communication table of the ProtocolEngine
     * @return true if everything is fine, otherwise false
     */
    bool communication_table_standard_test();
    /**
     * @public
     */
  public:
    /**
     * Constructor
     */
    CommunicationTableTest();
    /**
     * Tests all cases and returns a boolean if they passed or not
     * @return true if all cases passed, otherwise false
     */
    bool test_cases();
    /**
     * Destructor
     */
    ~CommunicationTableTest();
  };

#endif /* TEST_COMMUNICATION_TABLE_TEST_H_ */
#endif
