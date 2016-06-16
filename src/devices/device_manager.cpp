#include "device_manager.h"

//Public Functions

DeviceManager::DeviceManager (ProtocolEngine* protocol_engine, std::vector<uint8_t> descriptor_bytes)
{
  if (descriptor_bytes.empty () == false)
    {
      init_sensors (protocol_engine, descriptor_bytes);
    }
  descriptor_bytes.clear ();
}

Device*
DeviceManager::get_device (ComponentDescriptor* descriptor)
{
  Device* dptr = NULL;
  if (m_devices.count (descriptor) > 0)
    {
      dptr = &(*m_devices.at (descriptor));
    }
  return dptr;
}

DeviceManager::~DeviceManager ()
{
  m_devices.clear ();
}

// Private Functions

int8_t
DeviceManager::init_sensors (ProtocolEngine* protocol_engine, std::vector<uint8_t> descriptor_bytes)
{
  /* TODO: After reading the config file, switch case the component descriptor
   and create a device as well as add an entry to the communication table
   */
  ComponentDescriptorEnum descriptor_enum;
  uint8_t component_class, component_attribute, component_number;
  for (uint32_t i = 0; i < descriptor_bytes.size (); i = i + 3)
    {
      component_class = descriptor_bytes.at (i);
      component_attribute = descriptor_bytes.at (i + 1);
      component_number = descriptor_bytes.at (i + 2);
      descriptor_enum = static_cast<ComponentDescriptorEnum> (component_class
	  + component_attribute);
      ComponentDescriptor descriptor =  protocol_engine->get_descriptor_builder()->create_descriptor (
	  component_class, component_attribute, component_number);
      switch (descriptor_enum)
	{
	case ComponentDescriptorEnum::ACCELEROMETER:
	  m_devices.insert (
	      std::make_pair (
		  &descriptor,
		  std::shared_ptr<Accelerometer> (
		      new Accelerometer (
			  new I2CParameter (
			      static_cast<uint8_t> (Device_Config::ACC_ADDR)),
			  Device_Config::ACC_RANGE_2G, descriptor))));


	  break;
	case ComponentDescriptorEnum::ANEMOMETER:
	  break;
	case ComponentDescriptorEnum::COMPASS:
	  break;
	case ComponentDescriptorEnum::GPS:
	  break;
	case ComponentDescriptorEnum::HYGROMETER:
	  break;
	case ComponentDescriptorEnum::SERIAL_LINK:
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR:
	  break;
	case ComponentDescriptorEnum::STREAM_GENERATOR:
	  break;
	case ComponentDescriptorEnum::WESTON_ANEMOMETER:
	  break;
	case ComponentDescriptorEnum::WIND_VANE:
	  break;
	default:
	  // TODO: Something fancy
	  break;
	}
    }
  return 1;
}
