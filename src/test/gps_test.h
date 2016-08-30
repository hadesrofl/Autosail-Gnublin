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
   * Test function for gps latency
   */
  void
  eval ();
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
