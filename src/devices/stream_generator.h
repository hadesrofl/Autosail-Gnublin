#ifndef DEVICES_STREAM_GENERATOR_H_
#define DEVICES_STREAM_GENERATOR_H_

#include "../utils/timer.h"
#include <memory>
#include "../communication/protocol_engine.h"
#include "../utils/calculation.h"
#include "stream.h"
#include "../devices/gps.h"

/*
 * Forward Declaration because of recursive include of header files
 */
class ProtocolEngine;
/**
 * @file
 * @class StreamGenerator
 * @ingroup Devices
 * @brief Class for a StreamGenerator. A StreamGenerator creates data
 * streams using a Timer that interrupts at a specific period.
 * After that interrupt an integer will increase.
 *
 * @details A StreamGenerator creates data streams using a Timer
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
   * Pointer to the ComponentDescriptor of this component
   */
  std::shared_ptr<ComponentDescriptor> m_descriptor;
  /**
   * Communication number of this component
   */
  uint8_t m_communication_number;
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
  static uint16_t m_interrupt_counter;
  /**
   * Timer that causes the software interrupt in Linux
   */
  std::unique_ptr<Timer> m_timer;
  /**
   * Shortest period in ms for a stream to be generated
   */
  static uint16_t m_min_period;
  /**
   * Max value for the counter (longest period) to check if one cycle through all
   * streams is finished or there are some streams left to handle
   */
  uint16_t m_max_period;
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
  set_min_period (uint16_t period)
  {
#ifdef _DEBUG
    std::cout << "Period set to: " << period << std::endl;
#endif
    m_min_period = period;
    m_timer->set_timer (m_min_period);
#ifdef _DEBUG
    std::cout << "Set Timer!" << std::endl;
#endif
  }
  /**
   * Checks the list of periods for the longest period and sets it as max period.
   * Will be called if a period is removed as there needs to be a check
   * if the max period is still the same.
   * @param period is the removed period
   * @return the max period, which was found, on success or 0 on a fail
   */
  inline uint16_t
  check_max_period (uint16_t period)
  {
    uint16_t max = 0;
    // nothing changes
    if (m_max_period > period)
      {
	max = m_max_period;
      }
    // something changes
    else
      {
	for (uint8_t i = 0; i < m_periods.size (); i++)
	  {
	    if (max < m_periods.at (i))
	      {
		max = m_periods.at (i);
	      }
	  }
	if (max != 0)
	  {
	    m_max_period = max;
	  }
      }
    return max;
  }
  /**
   * Lookup a Device in the list of Streams and return its Stream
   * @param comm_number is the communication number of the Device in the Stream
   * @return a pointer to the Stream containing the device or NULL,
   * if there is no such device in the Streams
   */
  Stream*
  lookup_device (uint8_t comm_number);
  /**
   * Sets the longest period
   * @param period is the new longest period
   */
  inline void
  set_max_period (uint16_t period)
  {
    if (m_max_period < period)
      {
	m_max_period = period;
#ifdef _DEBUG
	std::cout << "Set Max Period to: " << m_max_period << std::endl;
#endif
      }
  }
  /**
   * @public
   */
public:
  /**
   * Constructor for the StreamGenerator
   * @param descriptor is a pointer to the ComponentDescriptor of this component
   * @param communication_number is the communication number as integer
   */
  StreamGenerator (std::shared_ptr<ComponentDescriptor> descriptor,
		   uint8_t communication_number);
  /**
   * Adds a device with a period to the stream generator
   * @param device is a pointer to the Device to watch over
   * @param communication_number is the communication number of the Device
   * @param period is the time interval to send data of the device
   * @return 1 on success, otherwise -1
   */
  int8_t
  add_stream (std::shared_ptr<Device> device, uint8_t communication_number,
	      uint16_t period);
  /**
   * Disables a Stream
   * @param comm_number is the communication number of the Device of the Stream
   * @return 1 on success, otherwise false
   */
  int8_t
  disable_stream (uint8_t comm_number);
  /**
   * Function for a thread to run the generator and collect data from the streams
   * @param params is the stream_generator_thread_param_t for this thread
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
   * Searches the list of streams for a stream of a specific device
   * @param comm_number is the communication number of the Device of the Stream
   * @return a pointer to the stream or NULL if the device could not be found
   */
  Stream*
  get_stream (uint8_t comm_number) const
  {
    for (uint16_t i = 0; i < m_streams.size (); i++)
      {
	if (m_streams.at (i)->get_communication_number () == comm_number)
	  {
	    return m_streams.at (i);
	  }
      }
    return NULL;
  }
  /**
   * Gets the shortest period of streams
   * @return the shortest period in the list of streams
   */
  uint16_t
  get_min_period () const
  {
    return m_min_period;
  }
  /**
   * Gets the longest period of streams
   * @return the longest period in the list of streams
   */
  uint16_t
  get_max_period () const
  {
    return m_max_period;
  }
  /**
   * Gets the longest period of streams
   * @return the longest period in the list of streams
   */
  uint16_t
  get_interrupt_counter () const
  {
    return m_interrupt_counter;
  }
  /**
   * Gets the ComponentDescriptor of this component
   * @return the descriptor of this specific device
   */
  inline std::shared_ptr<ComponentDescriptor>
  get_component_descriptor () const
  {
    return m_descriptor;
  }
  /**
   * Returns the communication number of this device
   * @return an integer with the communication number
   */
  inline uint8_t
  get_communication_number () const
  {
    return m_communication_number;
  }
  /**
   * Sets a ProtocolEngine to this StreamGenerator.
   * Used for sending the data streams via a Frame to some receiver
   * @param engine is a pointer to the ProtocolEngine
   */
  void
  set_protocol_engine (std::shared_ptr<ProtocolEngine> engine)
  {
    m_protocol_engine = engine;
  }
  /**
   * Destructor
   */
  ~StreamGenerator ();
};

#endif /* DEVICES_STREAM_GENERATOR_H_ */
