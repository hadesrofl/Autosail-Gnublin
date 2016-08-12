#ifdef _TEST
#ifndef TEST_GPS_TEST_H_
#define TEST_GPS_TEST_H_

#include <iostream>
#include <vector>
#include "../loader/loader.h"
/**
 * @file
 * @class GPSTest
 * @brief Class for testing purposes of the GPS.
 * Reads Data from the Device and prints it to the stdio.
 * @author Rene Kremer
 * @version 0.2
 */
class GPSTest
{
  /**
   * @public
   */
public:
  /**
   * Constructor
   */
  GPSTest ();
  /**
   * Test cases for the GPS. Reads data from the Sensor and prints it to
   * stdio
   */
  bool
  test_cases ();
  /**
   * Destructor
   */
  virtual
  ~GPSTest ();
};

#endif /* TEST_GPS_TEST_H_ */
#endif
