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
