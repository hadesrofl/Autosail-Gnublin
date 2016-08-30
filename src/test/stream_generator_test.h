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
#ifndef TEST_STREAM_GENERATOR_TEST_H_
#define TEST_STREAM_GENERATOR_TEST_H_

#include <iostream>
#include <vector>
#include "asserter.h"
#include "../loader/loader.h"
#include "../devices/device_manager.h"

/**
 * @file
 * @class StreamGeneratorTest
 * @brief Class for testing purposes of the StreamGenerator.
 * @author Rene Kremer
 * @version 0.2
 */
class StreamGeneratorTest
{
  /**
   * @private
   */
private:
  /**
   * Tests the StreamGenerator via example Streams of the Accelerometer,
   * Gyroscope and Compass
   * @return true only, as there is no test of this function by the firmware itself
   */
  bool
  stream_test ();
  /**
   * @public
   */
public:
  /**
   * Constructor
   */
  StreamGeneratorTest ();
  /**
   * Evaluates the StreamGenerator. Therefore needs some measurement code in
   * the StreamGenerator to get a begin and end time
   */
  void
  eval ();
  /**
   * Starts the test cases and returns true, as the firmware doesn't test itself.
   * Needs someone to have a look at the logs
   * @return true only, as the firmware doesn't test itself
   */
  bool
  test_cases ();
  /**
   * Destructor
   */
  ~StreamGeneratorTest ();
};

#endif /* TEST_STREAM_GENERATOR_TEST_H_ */
#endif
