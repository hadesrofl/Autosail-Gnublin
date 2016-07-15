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
private:
  /**
   * Pointer of the Device to watch over in this stream
   */
  std::shared_ptr<Device> m_device;
  /**
   * Time interval to generate new data
   */
  uint16_t m_period;
public:
  Stream (std::shared_ptr<Device> device, uint16_t period)
  {
    m_device = device;
    m_period = period;
  }
  std::shared_ptr<Device>
  get_device () const
  {
    return m_device;
  }
  uint16_t
  get_period () const
  {
    return m_period;
  }
  ~Stream ()
  {
  }

};

#endif /* DEVICES_STREAM_H_ */
