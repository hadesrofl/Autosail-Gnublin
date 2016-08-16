#ifdef _TEST
#ifndef TEST_GYROSCOPE_TEST_H_
#define TEST_GYROSCOPE_TEST_H_

#include <iostream>
#include <vector>
#include "../loader/loader.h"
#include <signal.h>
/**
 * @file
 * @class GyroscopeTest
 * @brief Class for testing purposes of the Gyroscope.
 * Reads Data from the Device and prints it to the stdio.
 * @author Rene Kremer
 * @version 0.2
 */
class GyroscopeTest
{
  /**
   * @public
   */
public:
  /**
   * Constructor
   */
  GyroscopeTest ();
  /**
   * Test for time needed to read device in firmware
   */
  void eval();
  /**
   * Test cases for the Gyroscope. Reads data from the Sensor and prints it to
   * stdio
   */
  bool test_cases();
  /**
   * Destructor
   */
  virtual
  ~GyroscopeTest ();
};

#endif /* TEST_GYROSCOPE_TEST_H_ */
#endif
