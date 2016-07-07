#ifdef _TEST
#include "timer_test.h"

// Intialize static member
uint32_t TimerTest::m_interrupt_counter = 0;

// public functions
TimerTest::TimerTest ()
  {

  }
bool
TimerTest::test_cases ()
  {
    std::vector<bool> passed;
    Asserter asserter;
    passed.push_back(timer_test());
    return asserter.check_asserts(passed, 1);
  }

TimerTest::~TimerTest ()
  {

  }

// private functions
void
TimerTest::timer_handler (int32_t signo)
  {
    m_interrupt_counter++;
  }

bool
TimerTest::timer_test ()
  {
  std::cout << "---------------------------------" << std::endl;
  std::cout << "Starting Timer Test" << std::endl;
  std::cout << "---------------------------------" << std::endl;
    uint32_t ms, counter, seconds, nanoseconds;
    ms = 250;
    counter = 5;
    Timer* timer = new Timer (ms, timer_handler);
    timeval start, end;
    gettimeofday (&start, 0);
    while (m_interrupt_counter < counter)
      {
	sleep(1);
      }
    gettimeofday (&end, 0);
    std::cout << "Begin: " << start.tv_sec << ":" << start.tv_usec << std::endl;
    std::cout << "End: " << end.tv_sec << ":" << end.tv_usec << std::endl;
    std::cout << "Difference: " << (end.tv_sec - start.tv_sec) << ":"
    << (end.tv_usec - start.tv_usec) << std::endl;
    seconds = end.tv_sec - start.tv_sec;
    nanoseconds = end.tv_usec - start.tv_usec;
    // counter + 1 because the timer is not 100 percent accurate so 5*250
    // might be something around 1250 to 1500 at least between 1250 and 2000
    if(seconds*1000 + nanoseconds/1000 < ms*(counter + 1))
      {
	return true;
      }
    return false;
  }
#endif
