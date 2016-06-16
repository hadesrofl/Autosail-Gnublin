#ifndef UTILS_TIMER_H_
#define UTILS_TIMER_H_

#include <signal.h>
#include <time.h>
#include <iostream>

/**
 * @file
 * @class Timer
 * @brief Class for a Timer. A Timer uses the system clock of linux to arm a timer
 * and fire signals as software interrupts.
 *
 * Signal Handler is a function like: void signal_handler(int32_t signo)
 *
 * It needs to be a function with void as return value and an integer value
 * for the signo. This function will be called if the interrupt is fired.
 * @author Rene Kremer
 * @version 0.2
 * @note Base Idea from http://stackoverflow.com/questions/4883411/multiple-timer-to-one-process-without-linking-to-rt
 */
class Timer
{
  /**
   * @private
   */
private:
  /**
   * Timer Object from Linux API
   */
  timer_t m_timer;
  /**
   * Counter for the total and last of the timer ids
   */
  static uint8_t m_last_timer_id;
  /**
   * Counter for the total and last of the signal ids
   */
  static int32_t m_last_signal_id;
  /**
   * Id of this timer
   */
  uint8_t m_timer_id;
  /**
   * Id of the signal for this timer
   */
  int32_t m_signal_id;
  /**
   * Creates a timer_t object according to linux api
   * @param sig_id is the id of the signal
   */
  timer_t
  create_timer (int32_t sig_id);
  /**
   * Sets up a signal handler which will be called if the signal occurs
   * @param sig_id is the id of the signal
   * @param handler is the handler for the function to be called
   */
  void
  install_sighandler (int32_t sig_id, void
  (*handler) (int32_t));
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param seconds are the seconds for the time interval. If this time expires an interrupt (signal) will be fired
   * @param milliseconds are the milliseconds for the time interval
   * @param handler is the function to be called if an interrupt is fired
   */
  Timer (uint32_t seconds, uint32_t milliseconds, void
  (*handler) (int32_t));
  /**
   * Sets the timer to seconds and milliseconds. Initially called in constructor, but can be used to change the intervals on runtime
   * @param seconds for the seconds of the time interval
   * @param milliseconds for the milliseconds of the time interval
   * @return on success the sum of seconds and milliseconds in milliseconds of the time interval, otherwise on failure -1
   */
  uint32_t
  set_timer (uint32_t seconds, uint32_t milliseconds);
  /**
   * Gets the signal id of this timer
   * @return signal_id
   */
  inline int32_t
  get_signal_id () const
  {
    return m_signal_id;
  }
  /**
   * Gets the timer id of this timer
   * @return timer_id
   */
  inline uint8_t
  get_timer_id () const
  {
    return m_timer_id;
  }
  /**
   * Default Destructor
   */
  ~Timer ()
  {
  }
};

#endif /* UTILS_TIMER_H_ */
