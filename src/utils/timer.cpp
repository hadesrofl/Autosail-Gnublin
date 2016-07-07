#include "timer.h"

// Init statics
int32_t Timer::m_last_signal_id = 0;
uint8_t Timer::m_last_timer_id = 0;
// private functions
timer_t
Timer::create_timer (int32_t sig_id)
{
  timer_t timer_id;
  struct sigevent se;
  se.sigev_notify = SIGEV_SIGNAL;
  se.sigev_signo = sig_id;
  if (timer_create (CLOCK_REALTIME, &se, &timer_id) == -1)
    {
#ifdef _DEBUG
      std::cerr << "Failed to create timer" << std::endl;
#endif
      return NULL;
    }
  return timer_id;
}
void
Timer::install_sighandler (int32_t signo, void
(*handler) (int32_t))
{
  sigset_t set;
  struct sigaction act;

  /* Setup the handler */
  act.sa_handler = handler;
  act.sa_flags = SA_RESTART;
  sigaction (signo, &act, 0);

  /* Unblock the signal */
  sigemptyset (&set);
  sigaddset (&set, signo);
  sigprocmask (SIG_UNBLOCK, &set, NULL);

  return;
}
//public functions

Timer::Timer (uint32_t milliseconds, void
(*handler) (int32_t))
{
  m_last_signal_id++;
  m_last_timer_id++;
  m_timer_id = m_last_timer_id;
  m_signal_id = m_last_signal_id;
  m_timer = create_timer (m_signal_id);
  if (set_timer (milliseconds) > 0)
    {
      install_sighandler (m_signal_id, handler);
    }
  else
    {
      // disarm timer
      set_timer (0);
    }
}
uint32_t
Timer::set_timer (uint32_t milliseconds)
{
  uint32_t seconds = 0;
  if (milliseconds > 1000)
    {
      uint16_t divider = milliseconds / 1000;
#ifdef _DEBUG
      std::cout << "Divider: " << divider << std::endl;
#endif
      for(int16_t i = 0; i < divider;i++){
	  seconds++;
	  milliseconds -= 1000;
      }
    }
  struct itimerspec timervals;
  timervals.it_value.tv_sec = seconds;
  timervals.it_value.tv_nsec = milliseconds * 1000000;
  timervals.it_interval.tv_sec = seconds;
  timervals.it_interval.tv_nsec = milliseconds * 1000000;

  if (timer_settime (m_timer, 0, &timervals, NULL) == -1)
    {
#ifdef _DEBUG
      std::cerr << "Failed to start timer" << std::endl;
#endif
      return -1;
    }
  return seconds*1000 + milliseconds;
}
