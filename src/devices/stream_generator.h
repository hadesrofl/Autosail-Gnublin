#ifndef DEVICES_STREAM_GENERATOR_H_
#define DEVICES_STREAM_GENERATOR_H_

#include "../utils/timer.h"
#include <stdint.h>
#include <memory>
#include "../communication/protocol_engine.h"

/*
 * Forward Declaration because of recursive include of header files
 */
class ProtocolEngine;
/**
 * @file
 * @class StreamGenerator
 * @brief Class for a StreamGenerator.
 * A StreamGenerator creates data streams using a Timer
 * that interrupts at a specific period. After that interrupt an
 * integer will increase.
 *
 * The different Streams controlled by the StreamGenerator will be called
 * if a given amount of time passed.
 *
 * Shall be used as Singleton as C++ needs a so called pointer-to-function
 * for the interrupt_handler. This is accomplished by a function on top-level or
 * a static class function. Therefore m_interrupt_counter is also static as it
 * will be increased in the handler function. More than one StreamGenerator would
 * end up in overriding the interrupt counter.
 *
 * @note Info on pointer-to-function and pointer-to-member-function: http://stackoverflow.com/questions/15841338/c-unresolved-overloaded-function-type
 * @author Rene Kremer
 * @version 0.2
 */
class StreamGenerator
{
  /**
   * @private
   */
private:
  std::shared_ptr<ProtocolEngine> m_protocol_engine;
  /**
   * Counts how many interrupts happened
   */
  static uint32_t m_interrupt_counter;
  /**
   * Timer that causes the software interrupt in Linux
   */
  std::unique_ptr<Timer> m_timer;
  /**
   * Shortest period for a stream to be generated
   */
  uint16_t m_period;
  /**
   * Handler for the Timer Interrupt. Will be called if the Timer interrupts
   * @param signo is the signal number for a software interrupt in Linux
   */
  static void
  timer_handler (int signo);
  /**
   * @public
   */
public:
  /**
   * Constructor for the StreamGenerator
   */
  StreamGenerator ();
  /**
   * Sets a new period for the timer but only if the new period is
   * shorter than the previous one.
   * @param period is the time for the timer to be called
   */
  inline void
  set_period (uint16_t period)
  {
    if (m_period == 0 || m_period > period)
      {
	m_period = period;
      }
  }
  /**
   * Destructor
   */
  ~StreamGenerator ();
};

#endif /* DEVICES_STREAM_GENERATOR_H_ */
