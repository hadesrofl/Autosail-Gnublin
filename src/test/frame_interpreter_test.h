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
   * @param begin is the begin time
   * @param end is the end time
   */
  void
  print_time (timeval begin, timeval end);
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
