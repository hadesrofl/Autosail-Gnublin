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
 * @version 0.2
 */
class FilteredDevice{
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
  std::unique_ptr<Device> m_device;
  /**
   * Filter
   */
  std::unique_ptr<Filter> m_filter;
  /**
   * @public
   */
public:
  /**
   * Constructor
   */
  FilteredDevice(){

  }
  /**
   * Destructor
   */
  virtual ~FilteredDevice(){

  }
};



#endif /* DEVICES_FILTERED_DEVICE_H_ */
