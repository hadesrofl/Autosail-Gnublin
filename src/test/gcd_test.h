#ifdef _TEST
#ifndef TEST_GCD_TEST_H_
#define TEST_GCD_TEST_H_

#include "../utils/gcd.h"
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
     * Greatest Common Divisor Class to calculate the gcd
     */
    GCD m_gcd;
    /**
     * Asserter to assert the values
     */
    Asserter asserter;
    /**
     * result value of gcd
     */
    uint32_t m_result;
    /**
     * expected value for gcd
     */
    uint32_t m_expected;
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
     * Test for the vector size of 6
     * @return true if the test passed, otherwise false
     */
    bool test_length_6();
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
