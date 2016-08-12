#ifdef _TEST
#ifndef TEST_ACC_TEST_H_
#define TEST_ACC_TEST_H_

#include <iostream>
#include <vector>
#include "../loader/loader.h"

/**
 * Speed of milli g. 1G = 9.81 m / s^2
 */
#define MG_SPEED 0.00981

/**
 * @file
 * @class AccTest
 * @brief Class for testing purposes of the Accelerometer.
 * Reads Data from the Device and prints it to the stdio.
 * @author Rene Kremer
 * @version 0.2
 */
class AccTest
{
  /**
   * @public
   */
public:
  /**
   * Constructor
   */
  AccTest ();
  /**
   * Test cases for the Accelerometer. Reads data from the Sensor and prints it to
   * stdio
   */
  bool
  test_cases ();
  /**
   * Destructor
   */
  virtual
  ~AccTest ();
};

#endif /* TEST_ACC_TEST_H_ */
#endif
