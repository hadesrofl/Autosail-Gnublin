#ifndef DEVICES_STREAM_H_
#define DEVICES_STREAM_H_

#include "device.h"
#include <stdint.h>
/**
 * @file
 * @class Stream
 * @brief Class used in StreamGenerator. Contains a Device and the period to
 * generate new data
 * @author Rene Kremer
 * @version 0.2
 */
class Stream
{
  /**
   * @private
   */
private:
  /**
   * Pointer of the Device to watch over in this stream
   */
  std::shared_ptr<Device> m_device;
  /**
   * Time interval to generate new data
   */
  uint32_t m_period;
  /**
   * Is the Stream active or disabled?
   */
  bool m_active;
  /**
   * @public
   */
public:
  /**
   * Constructor - Sets this Stream active for a given period and device
   * @param device is the pointer to the Device
   * @param period is the period triggering this Stream
   */
  Stream (std::shared_ptr<Device> device, uint32_t period)
  {
    m_device = device;
    m_period = period;
    m_active = true;
  }
  /**
   * Gets the Device of this Stream
   * @return a pointer to the Device
   */
  std::shared_ptr<Device>
  get_device () const
  {
    return m_device;
  }
  /**
   * Gets the period in ms triggering this Stream
   * @return period in ms to trigger the Stream
   */
  uint32_t
  get_period () const
  {
    return m_period;
  }
  /**
   *Sets a new period to triggering this stream. Activates the Stream
   *@param period is the new period
   */
  void
  set_period (uint32_t period)
  {
    m_period = period;
    set_active (true);
  }
  /**
   * Sets this Stream to active (true) or disabled (false)
   * @param active is a bool determining if the Stream is active or disabled
   */
  void
  set_active (bool active)
  {
    m_active = active;
  }
  /**
   * Is the Stream active or disabled?
   * @return true if it is active, otherwise false
   */
  bool
  is_active () const
  {
    return m_active;
  }
  /**
   * Destructor
   */
  ~Stream ()
  {
  }

};

#endif /* DEVICES_STREAM_H_ */
