#include "filtered_accelerometer.h"

FilteredAccelerometer::FilteredAccelerometer (I2CParameter* interface_parameter,
					      Device_Config device_config,
					      Filter* filter)
{
  m_device = std::unique_ptr<Device> (new Accelerometer (interface_parameter, device_config));
  m_filter = std::unique_ptr<Filter> (filter);
}
FilteredAccelerometer::~FilteredAccelerometer ()
{

}

