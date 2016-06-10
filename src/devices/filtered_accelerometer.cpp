#include "filtered_accelerometer.h"

FilteredAccelerometer::FilteredAccelerometer (Device* device, Filter* filter)
{
  m_device = std::unique_ptr<Device*> (&device);
  m_filter = std::unique_ptr<Filter*> (&filter);
}
uint8_t* FilteredAccelerometer::get_filtered_data(){
  return NULL;
}
FilteredAccelerometer::~FilteredAccelerometer ()
{

}

