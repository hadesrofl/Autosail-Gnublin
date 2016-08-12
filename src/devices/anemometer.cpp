#include "anemometer.h"

// Private Functions
int8_t
Anemometer::init ()
{
  return -1;
}
// Public Functions
Anemometer::Anemometer (I2CParameter *interface_parameter,
			ComponentDescriptor* descriptor)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (interface_parameter->get_device_file (),
	       interface_parameter->get_address ()));
  set_component_descriptor (descriptor);
  m_device_parameter = std::unique_ptr<I2CParameter> (interface_parameter);
  m_datastructure_id = DataStructureIdentifier::INT16;
  init ();
}
std::vector<int8_t>
Anemometer::read_data ()
{
  //Set Register Pointer to first Data Register
  uint8_t register_address = ANEMOMETER_DATA_REGISTER;
  Device::write (&register_address, 1);
  uint8_t* buf = new uint8_t[DeviceConfig::ANEMOMETER_DATA_LENGTH];
  std::vector<int8_t> data;
  Device::read (buf,
		static_cast<int16_t> (DeviceConfig::ANEMOMETER_DATA_LENGTH));
  data.push_back (buf[1]);
  data.push_back (buf[0]);
  delete[] buf;
  return data;
}
Anemometer::~Anemometer ()
{
}

