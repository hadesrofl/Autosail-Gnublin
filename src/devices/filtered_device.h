#ifndef DEVICES_FILTERED_DEVICE_H_
#define DEVICES_FILTERED_DEVICE_H_

#include <memory>
#include "device.h"
#include "../utils/filter.h"

/**
 * @file
 * @class FilteredDevice
 * @brief Class for an abstract FilteredDevice . Uses the data from a Device and filters
 * it with some Filter.
 * @author Rene Kremer
 * @note might need some buffer for read data to insert into the filter to get
 * better results
 * @version 0.2
 */
class FilteredDevice
{
  /**
   * @private
   */
private:
  /**
   * @protected
   */
protected:
  /**
   * Device
   */
  std::unique_ptr<Device*> m_device;
  /**
   * Filter
   */
  std::unique_ptr<Filter*> m_filter;
  /**
   * @public
   */
public:
  /**
   * Gets filtered data from a filtered device. The data and amount of data has to
   * be specified by the device.
   * @return a pointer of data bytes from the filtered device
   */
  virtual uint8_t*
  get_filtered_data () = 0;
  /**
   * Destructor
   */
  virtual
  ~FilteredDevice ()
  {

  }
};

#endif /* DEVICES_FILTERED_DEVICE_H_ */
