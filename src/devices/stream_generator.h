#ifndef DEVICES_STREAM_GENERATOR_H_
#define DEVICES_STREAM_GENERATOR_H_

#include "../utils/timer.h"
#include <memory>
#include "../communication/protocol_engine.h"
#include "../utils/calculation.h"
#include "stream.h"

/*
 * Forward Declaration because of recursive include of header files
 */
class ProtocolEngine;
/**
 * @file
 * @class StreamGenerator
 * @brief Class for a StreamGenerator. A StreamGenerator creates data
 * streams using a Timer that interrupts at a specific period.
 * After that interrupt an integer will increase.
 *
 * @detail A StreamGenerator creates data streams using a Timer
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
  /**
   * Pointer to the ProtocolEngine for sending frames of data
   */
  std::shared_ptr<ProtocolEngine> m_protocol_engine;
  /**
   * List of Streams that will be checked for data
   */
  std::vector<Stream*> m_streams;
  /**
   * List of Periods to determine gcd and max value from
   */
  std::vector<uint16_t> m_periods;
  /**
   * Counts how many interrupts happened
   */
  static uint32_t m_interrupt_counter;
  /**
   * Timer that causes the software interrupt in Linux
   */
  std::unique_ptr<Timer> m_timer;
  /**
   * Shortest period in ms for a stream to be generated
   */
  static uint32_t m_min_period;
  /**
   * Max value for the counter (longest period) to check if one cycle through all
   * streams is finished or there are some streams left to handle
   */
  uint32_t m_max_period;
  /**
   * Region Mutex for accessing resources
   */
  static pthread_mutex_t m_region_mutex;
  /**
   * Handler for the Timer Interrupt. Will be called if the Timer interrupts
   * @param signo is the signal number for a software interrupt in Linux
   */
  static void
  timer_handler (int signo);
  /**
   * Sets the shortest period for the timer but only if the new period is
   * shorter than the previous one.
   * @param period is the time for the timer to be called
   */
  inline void
  set_min_period (uint32_t period)
  {
    if (period <= m_min_period || m_min_period == 0)
      {
	std::cout << "Period set to: " << period << std::endl;
	m_min_period = period;
	if (m_timer->set_timer (m_min_period) == m_min_period)
	  {
	    std::cout << "Set Timer!" << std::endl;
	  }
      }
  }
  /**
   * Sets the longest period
   * @param period is the new longest period
   */
  inline void
  set_max_period (uint32_t period)
  {
    if (m_max_period < period)
      {
	m_max_period = period;
	std::cout << "Set Max Period to: " << m_max_period << std::endl;
      }
  }
  /**
   * @public
   */
public:
  /**
   * Constructor for the StreamGenerator
   */
  StreamGenerator ();
  /**
   * Adds a device with a period to the stream generator
   * @param device is a pointer to the Device to watch over
   * @param period is the time interval to send data of the device
   */
  void
  add_stream (std::shared_ptr<Device> device, uint32_t period);
  /**
   *
   */
  static void *
  run_generator (void* params);
  /**
   * Gets the list of streams
   * @return the list of streams of this StreamGenerator
   */
  std::vector<Stream*>
  get_streams ()
  {
    return m_streams;
  }
  /**
   * Gets the shortest period of streams
   * @return the shortest period in the list of streams
   */
  uint32_t
  get_min_period () const
  {
    return m_min_period;
  }
  /**
   * Gets the longest period of streams
   * @return the longest period in the list of streams
   */
  uint32_t
  get_max_period () const
  {
    return m_max_period;
  }
  /**
   * Gets the longest period of streams
   * @return the longest period in the list of streams
   */
  uint32_t
  get_interrupt_counter () const
  {
    return m_interrupt_counter;
  }
  /**
   * Destructor
   */
  ~StreamGenerator ();
};

#endif /* DEVICES_STREAM_GENERATOR_H_ */
