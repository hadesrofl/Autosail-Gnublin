#include "device_manager.h"

//Public Functions

DeviceManager::DeviceManager (ProtocolEngine* protocol_engine,
			      std::vector<uint8_t> descriptor_bytes)
{
  if (descriptor_bytes.empty () == false)
    {
      init_sensors (protocol_engine, descriptor_bytes);
    }
  descriptor_bytes.clear ();
}

std::shared_ptr<Device>
DeviceManager::get_device (ComponentDescriptorEnum descriptor_enum)
{
  uint8_t cclass, cattribute, cnumber;
  // Build Descriptor
  cclass = static_cast<uint32_t> (descriptor_enum) >> 16;
  cattribute = static_cast<uint32_t> (descriptor_enum) >> 8;
  cnumber = static_cast<uint32_t> (descriptor_enum) & 0x1F;
  for (uint32_t i = 0; i < m_devices.size (); i++)
    {
      ComponentDescriptor* descriptor =
	  &(*m_devices[i]->get_component_descriptor ());
      if (descriptor->get_component_class () == cclass
	  && descriptor->get_component_attribute () == cattribute
	  && descriptor->get_component_number () == cnumber)
	{
	  return m_devices[i];
	}
    }
  return NULL;
}

DeviceManager::~DeviceManager ()
{
  m_devices.clear ();
}

// Private Functions

int8_t
DeviceManager::init_sensors (ProtocolEngine* protocol_engine,
			     std::vector<uint8_t> descriptor_bytes)
{
  ComponentDescriptorEnum descriptor_enum;
  uint8_t component_class, component_attribute, component_number,
      communication_number, config;
  for (uint32_t i = 0; i < descriptor_bytes.size (); i = i + 5)
    {
      component_class = descriptor_bytes.at (i);
      component_attribute = descriptor_bytes.at (i + 1);
      component_number = descriptor_bytes.at (i + 2);
      communication_number = descriptor_bytes.at (i + 3);
      config = descriptor_bytes.at (i + 4);
      descriptor_enum = static_cast<ComponentDescriptorEnum> (component_class
	  << 16 | component_attribute << 8 | component_number);
      ComponentDescriptor* descriptor = protocol_engine->create_descriptor (
	  component_class, component_attribute, component_number);
      switch (descriptor_enum)
	{
	case ComponentDescriptorEnum::ACCELEROMETER:
	  {
	    std::shared_ptr<Accelerometer> device = std::shared_ptr<
		Accelerometer> (
		new Accelerometer (
		    new I2CParameter (
			static_cast<uint8_t> (DeviceConfig::ACC_ADDR)),
		    static_cast<DeviceConfig> (config), descriptor));
	    m_devices.push_back (device);
	    protocol_engine->insert_communication_table_backward (
		communication_number, &(*device));
	    protocol_engine->insert_communication_table_forward (
		descriptor, communication_number);
	  }
	  break;
	case ComponentDescriptorEnum::ANEMOMETER:
	  break;
	case ComponentDescriptorEnum::COMPASS:
	  {
	    std::shared_ptr<Compass> device = std::shared_ptr<Compass> (
		new Compass (
		    new I2CParameter (
			static_cast<uint8_t> (DeviceConfig::COMPASS_ADDR)),
		    static_cast<DeviceConfig> (config), descriptor));
	    m_devices.push_back (device);
	    protocol_engine->insert_communication_table_backward (
		communication_number, &(*device));
	    protocol_engine->insert_communication_table_forward (
		descriptor, communication_number);
	  }
	  break;
	case ComponentDescriptorEnum::GYROSCOPE:
	  {
	    std::shared_ptr<Gyroscope> device = std::shared_ptr<Gyroscope> (
		new Gyroscope (
		    new I2CParameter (
			static_cast<uint8_t> (DeviceConfig::GYRO_ADDR)),
		    descriptor));
	    m_devices.push_back (device);
	    protocol_engine->insert_communication_table_backward (
		communication_number, &(*device));
	    protocol_engine->insert_communication_table_forward (
		descriptor, communication_number);
	  }
	  break;
	case ComponentDescriptorEnum::GPS_POSITION:
	  {
	    std::shared_ptr<GPS> device = std::shared_ptr<GPS> (
		new GPS (
		    new SerialParameter (GNUBLIN_DEFAULT_SERIAL,
					 static_cast<DeviceConfig> (config)),
		    descriptor));
	    m_devices.push_back (device);
	    protocol_engine->insert_communication_table_backward (
		communication_number, &(*device));
	    protocol_engine->insert_communication_table_forward (
		descriptor, communication_number);
	  }
	  break;
	case ComponentDescriptorEnum::GPS_VELOCITY:
	  break;
	case ComponentDescriptorEnum::BILGE_WATER_DETECTION:
	  break;
	case ComponentDescriptorEnum::SERIAL_LINK:
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_RUDDER:
	  break;
	case ComponentDescriptorEnum::STREAM_CONTROL_UNIT:
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
