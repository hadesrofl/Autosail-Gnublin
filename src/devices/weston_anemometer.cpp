#include "weston_anemometer.h"

// Private Functions
int8_t
WestonAnemometer::init ()
{
  return -1;
}
// Public Functions
WestonAnemometer::WestonAnemometer (I2CParameter *interface_parameter)
{
  m_device_parameter = std::unique_ptr<I2CParameter> (interface_parameter);
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (interface_parameter->get_device_file (),
	       interface_parameter->get_address ()));
  set_device_id (Descriptor::WESTON_ANEMOMETER);
  init ();
}
uint8_t*
WestonAnemometer::read_data ()
{
  uint8_t* data_ptr = NULL;
  return data_ptr;
}
WestonAnemometer::~WestonAnemometer ()
{
}

