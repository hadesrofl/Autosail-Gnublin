#ifdef _TEST
#ifndef TEST_WIND_VANE_TEST_H_
#define TEST_WIND_VANE_TEST_H_

#include <iostream>
#include <vector>
#include "../loader/loader.h"
#include <signal.h>
/**
 * @file
 * @class WindVaneTest
 * @brief Class for testing purposes of the WindVane.
 * Reads Data from the Device and prints it to the stdio.
 * @author Rene Kremer
 * @version 0.2
 */
class WindVaneTest
{
public:
  /**
   * Constructor
   */
  WindVaneTest ();
  /**
   * Test to eval the read speed in the firmware
   */
  void eval();
  /**
   * Test cases for the WindVane. Reads data from the Sensor and prints it to
   * stdio
   */
  bool test_cases();
  /**
   * Destructor
   */
  virtual
  ~WindVaneTest ();
};

#endif /* TEST_WIND_VANE_TEST_H_ */
#endif
