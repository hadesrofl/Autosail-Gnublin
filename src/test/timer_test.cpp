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
  passed.push_back (timer_test ());
  return asserter.check_asserts (passed, 1);
}

TimerTest::~TimerTest ()
{

}

// private functions
void
TimerTest::timer_handler (int32_t signo)
{
  timeval start;
  gettimeofday(&start,0);
  std::cout << start.tv_sec << ";" << start.tv_usec/1000 << ";" << std::endl;
  m_interrupt_counter++;
}

bool
TimerTest::timer_test ()
{
  std::cout << "---------------------------------" << std::endl;
  std::cout << "Starting Timer Test" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  std::cout << "\nPeriod in ms;Seconds;Milliseconds;" << std::endl;
  uint32_t ms, counter, difference;
  ms = 50;
  counter = 250;
  std::cout << "Timer set to: " << ms << " ms for " << counter << " times"
      << std::endl;
  Timer* timer = new Timer (ms, timer_handler);
  timeval start, end;
  gettimeofday (&start, 0);
  while (m_interrupt_counter < counter)
    {
      std::cout << ms << ";";
      sleep (1);
    }
  gettimeofday (&end, 0);
  difference = (end.tv_sec - start.tv_sec) * 1000
      + (end.tv_usec - start.tv_usec) / 1000;
  std::cout << "Begin: " << start.tv_sec << ":" << start.tv_usec << std::endl;
  std::cout << "End: " << end.tv_sec << ":" << end.tv_usec << std::endl;
  std::cout << "Expected Difference: " << ms * counter << std::endl;
  std::cout << "Difference: " << difference << std::endl;
  std::cout << "Expected Interrupt Counter: " << counter << std::endl;
  std::cout << "Interrupt Counter: " << m_interrupt_counter << std::endl;
  delete timer;
  if (difference / 1000 < ms * counter && m_interrupt_counter == counter)
    {
      return true;
    }
  return false;
}
#endif
