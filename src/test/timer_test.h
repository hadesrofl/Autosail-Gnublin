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
#ifndef TEST_TIMER_TEST_H_
#define TEST_TIMER_TEST_H_

#include <iostream>
#include <vector>
#include "../utils/timer.h"
#include "asserter.h"
/**
 * @file
 * @class TimerTest
 * @brief Class for testing purposes of the timer interrupts.
 * Implements some functions to assert that the timer interrupt works as intended.
 * @author Rene Kremer
 * @version 0.2
 */
class TimerTest
  {
    /**
     * @private
     */
  private:
    /**
     * Counter of interrupts
     */
    static uint32_t m_interrupt_counter;
    /**
     * Handler function for the timer interrupt
     * @param signo is the signal number
     */
    static void
    timer_handler (int32_t signo);
    /**
     * Test for one timer object
     * @return true if the given time for an interrupt and the difference between
     * start and end time of this test is the same or nearly the same.
     * Otherwise it's false.
     */
    bool
    timer_test ();
    /**
     * @public
     */
  public:
    /**
     * Constructor
     */
    TimerTest ();
    /**
     * Tests all cases and returns a boolean if they passed or not
     * @return true if all cases passed, otherwise false
     */
    bool
    test_cases ();
    /**
     * Destructor
     */
    ~TimerTest ();
  };

#endif /* TEST_TIMER_TEST_H_ */
#endif
