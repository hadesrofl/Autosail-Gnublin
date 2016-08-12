#ifdef _TEST
#ifndef TEST_COMPASS_TEST_H_
#define TEST_COMPASS_TEST_H_

#include <iostream>
#include <vector>
#include "../loader/loader.h"

/**
 * @file
 * @class CompassTest
 * @brief Class for testing purposes of the Compass.
 * Reads Data from the Device and prints it to the stdio.
 * @author Rene Kremer
 * @version 0.2
 */
class CompassTest
{
  /**
   * @public
   */
public:
  /**
   * Constructor
   */
  CompassTest ();
  /**
   * Test cases for the Compass. Reads data and prints it to stdio
   */
  bool test_cases();
  /**
   * Destructor
   */
  virtual
  ~CompassTest ();
};

#endif /* TEST_COMPASS_TEST_H_ */
#endif
