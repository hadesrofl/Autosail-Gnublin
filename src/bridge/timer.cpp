#include "timer.h"

// Init statics
uint8_t Timer::m_last_signal_id = 0;
uint8_t Timer::m_last_timer_id = 0;
// private functions
timer_t
Timer::create_timer (int signo)
{
  timer_t timerid;
  struct sigevent se;
  se.sigev_notify = SIGEV_SIGNAL;
  se.sigev_signo = signo;
  if (timer_create (CLOCK_REALTIME, &se, &timerid) == -1)
    {
      std::cerr << "Failed to create timer" << std::endl;
      return NULL;
    }
  return timerid;
}
void
Timer::install_sighandler (int signo, void
(*handler) (int))
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

Timer::Timer (int seconds, int milliseconds, void
(*handler) (int))
{
  m_last_signal_id++;
  m_last_timer_id++;
  m_timer_id = m_last_timer_id;
  m_signal_id = m_last_signal_id;
  m_timer = create_timer (m_signal_id);
  if (set_timer (seconds, milliseconds) > 0)
    {
      install_sighandler (m_signal_id, handler);
    }
  else
    {
      // disarm timer
      set_timer (0, 0);
    }
}
int
Timer::set_timer (int seconds, int milliseconds)
{
  struct itimerspec timervals;
  timervals.it_value.tv_sec = seconds;
  timervals.it_value.tv_nsec = milliseconds * 1000000;
  timervals.it_interval.tv_sec = seconds;
  timervals.it_interval.tv_nsec = milliseconds * 1000000;

  if (timer_settime (m_timer, 0, &timervals, NULL) == -1)
    {
      std::cerr << "Failed to start timer" << std::endl;
      return -1;
    }
  return timervals.it_interval.tv_sec;
}
