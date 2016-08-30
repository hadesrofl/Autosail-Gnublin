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
#ifndef TEST_GCD_TEST_H_
#define TEST_GCD_TEST_H_

#include "../utils/calculation.h"
#include <memory>
#include "asserter.h"
#include <iostream>
/**
 * @file
 * @class GCDTest
 * @brief Class for testing purposes of the GCD.
 * Implements some test cases to assert the GCD.
 * @author Rene Kremer
 * @version 0.2
 */
class GCDTest
  {
    /**
     * @private
     */
  private:
    /**
     * Asserter to assert the values
     */
    Asserter asserter;
    /**
     * result value of gcd
     */
    uint16_t m_result;
    /**
     * expected value for gcd
     */
    uint16_t m_expected;
    /**
     * Test for the gcd of two values
     * @return true if the test passed, otherwise false
     */
    bool test_gcd();
    /**
     * Test for the vector size of 1
     * @return true if the test passed, otherwise false
     */
    bool test_length_1();
    /**
     * Test for the vector size of 2
     * @return true if the test passed, otherwise false
     */
    bool test_length_2();
    /**
     * Test for the vector size of 3
     * @return true if the test passed, otherwise false
     */
    bool test_length_3();
    /**
     * Test for the vector size of 4
     * @return true if the test passed, otherwise false
     */
    bool test_length_4();
    /**
     * Test for the vector size of 5
     * @return true if the test passed, otherwise false
     */
    bool test_length_5();
    /**
     * Test for the vector size of 8
     * @return true if the test passed, otherwise false
     */
    bool test_length_8();
    /**
     * @public
     */
  public:
    /**
     * Constructor
     */
    GCDTest();
    /**
     * Tests all cases and returns true if all passed, otherwise false
     * @return true if all tests pass, otherwise false
     */
    bool test_cases();
    /**
     * Destructor
     */
    ~GCDTest();

  };

#endif /* TEST_GCD_TEST_H_ */
#endif
