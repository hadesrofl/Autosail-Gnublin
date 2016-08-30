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
#ifndef TEST_FRAME_INTERPRETER_TEST_H_
#define TEST_FRAME_INTERPRETER_TEST_H_

#include <signal.h>
#include <iostream>
#include "../loader/loader.h"
#include "../interfaces/spi_thread_param_t.h"
/**
 * @file
 * @class FrameInterpreterTest
 * @brief Class for testing purposes of the FrameInterpreter. Uses a TeensyDuino and
 * the Pin Change Interrupt on Pin 11 on the Gnublin and Pin 6 on the Duino
 * @author Rene Kremer
 * @version 0.2
 */
class FrameInterpreterTest
{
  /**
   * @private
   */
private:
  /**
   * Tests the FrameInterpreter via a teensyduino echo client, which sends the frames
   * back to the gnublin to read and interpret them via I2C
   */
  static void*
  test_teensy (void* params);
  /**
   * @public
   */
public:
  /**
   * Boa Constructor
   */
  FrameInterpreterTest ();
  /**
   * Prints the time and difference in time for the eval function
   * @param command is the commando of the Frame
   * @param begin is the begin time
   * @param end is the end time
   */
  void
  print_time (const char* command, timeval begin, timeval end);
  /**
   * Evals the speed to interpret frames
   */
  void
  eval ();
  /**
   * Starts the Pin Change Interrupt and test_teensy
   */
  void run_test();
  /**
   * Destructor
   */
  virtual
  ~FrameInterpreterTest ();
};

#endif /* TEST_FRAME_INTERPRETER_TEST_H_ */
#endif
