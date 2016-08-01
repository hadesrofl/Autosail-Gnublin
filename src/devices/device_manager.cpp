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
	  {
	    std::shared_ptr<Anemometer> device =
		std::shared_ptr<Anemometer> (
		    new Anemometer (
			new I2CParameter (
			    static_cast<uint8_t> (DeviceConfig::ANEMOMETER_ADDRESS)),
			descriptor));
	    m_devices.push_back (device);
	    protocol_engine->insert_communication_table_backward (
		communication_number, &(*device));
	    protocol_engine->insert_communication_table_forward (
		descriptor, communication_number);
	  }
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
	    uint8_t comp_class, comp_attribute, comp_number, comm_number;
	    ComponentDescriptor* val_desc, *vel_desc;
	    std::shared_ptr<GPS> device = std::shared_ptr<GPS> (
		new GPS (
		    new SerialParameter (GNUBLIN_DEFAULT_SERIAL,
					 static_cast<DeviceConfig> (config)),
		    descriptor));
	    m_devices.push_back (device);
	    /* add GPS_POSITION component for communication purposes */
	    protocol_engine->insert_communication_table_backward (
		communication_number, &(*device));
	    protocol_engine->insert_communication_table_forward (
		descriptor, communication_number);
	    /* add GPS_VALIDITY component for communication purposes */
	    comp_class =
		static_cast<uint32_t> (ComponentDescriptorEnum::GPS_VALIDITY_LEA_6H)
		    >> 16;
	    comp_attribute =
		static_cast<uint16_t> (ComponentDescriptorEnum::GPS_VALIDITY_LEA_6H)
		    >> 8;
	    comp_number =
		static_cast<uint8_t> (ComponentDescriptorEnum::GPS_VALIDITY_LEA_6H);
	    val_desc = protocol_engine->create_descriptor (comp_class,
							    comp_attribute,
							    comp_number);
	    comm_number = protocol_engine->get_last_communication_number () + 1;
	    protocol_engine->insert_communication_table_backward (comm_number,
								  &(*device));
	    comm_number = protocol_engine->get_last_communication_number ();
	    protocol_engine->insert_communication_table_forward (val_desc,
								 comm_number);
	    /* add GPS_VELOCITY component for communication purposes */
	    comp_class =
		static_cast<uint32_t> (ComponentDescriptorEnum::GPS_VELOCITY)
		    >> 16;
	    comp_attribute =
		static_cast<uint16_t> (ComponentDescriptorEnum::GPS_VELOCITY)
		    >> 8;
	    comp_number =
		static_cast<uint8_t> (ComponentDescriptorEnum::GPS_VELOCITY);
	    vel_desc = protocol_engine->create_descriptor (comp_class,
							    comp_attribute,
							    comp_number);

	    comm_number = protocol_engine->get_last_communication_number () + 1;
	    protocol_engine->insert_communication_table_backward (comm_number,
								  &(*device));
	    comm_number = protocol_engine->get_last_communication_number ();
	    protocol_engine->insert_communication_table_forward (vel_desc,
								 comm_number);
	  }
	  break;
	case ComponentDescriptorEnum::GPS_VELOCITY:
	  break;
	case ComponentDescriptorEnum::BILGE_WATER_DETECTION:
	  break;
	case ComponentDescriptorEnum::POWER_SUPPLY_SENSING:
	  {
	    std::shared_ptr<Battery> device = std::shared_ptr<Battery> (
		new Battery (
		    new SPIParameter (0, DeviceConfig::SPI_SPEED_1MHZ, true),
		    descriptor));
	    m_devices.push_back (device);
	    protocol_engine->insert_communication_table_backward (
		communication_number, &(*device));
	    protocol_engine->insert_communication_table_forward (
		descriptor, communication_number);
	  }
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_RUDDER:
	  {
	    std::shared_ptr<ServoMotor> device = std::shared_ptr<ServoMotor> (
		new ServoMotor (
		    new SPIParameter (0, DeviceConfig::SPI_SPEED_1MHZ, true),
		    descriptor, MECHANIC_RUDDER));
	    m_devices.push_back (device);
	    protocol_engine->insert_communication_table_backward (
		communication_number, &(*device));
	    uint8_t comp_class =
		static_cast<uint32_t> (ComponentDescriptorEnum::POSITION_RUDDER)
		    >> 16;
	    uint8_t comp_attribute =
		static_cast<uint16_t> (ComponentDescriptorEnum::POSITION_RUDDER)
		    >> 8;
	    uint8_t comp_number =
		static_cast<uint8_t> (ComponentDescriptorEnum::POSITION_RUDDER);
	    ComponentDescriptor* comp_desc =
		protocol_engine->create_descriptor (comp_class, comp_attribute,
						    comp_number);
	    /* for POSITION_RUDDER */
	    protocol_engine->insert_communication_table_forward (
		comp_desc, communication_number);
	    /* for SERVO_RUDDER */
	    protocol_engine->insert_communication_table_forward (
		descriptor, communication_number);
	  }
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_MS:
	  {
	    std::shared_ptr<ServoMotor> device = std::shared_ptr<ServoMotor> (
		new ServoMotor (
		    new SPIParameter (0, DeviceConfig::SPI_SPEED_1MHZ, true),
		    descriptor, MECHANIC_MS));
	    m_devices.push_back (device);
	    protocol_engine->insert_communication_table_backward (
		communication_number, &(*device));
	    uint8_t comp_class =
		static_cast<uint32_t> (ComponentDescriptorEnum::POSITION_MS)
		    >> 16;
	    uint8_t comp_attribute =
		static_cast<uint16_t> (ComponentDescriptorEnum::POSITION_MS)
		    >> 8;
	    uint8_t comp_number =
		static_cast<uint8_t> (ComponentDescriptorEnum::POSITION_MS);
	    ComponentDescriptor* comp_desc =
		protocol_engine->create_descriptor (comp_class, comp_attribute,
						    comp_number);
	    /* for POSITION_MS */
	    protocol_engine->insert_communication_table_forward (
		comp_desc, communication_number);
	    /* for SERVO_MS */
	    protocol_engine->insert_communication_table_forward (
		descriptor, communication_number);
	  }
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_FS:
	  {
	    std::shared_ptr<ServoMotor> device = std::shared_ptr<ServoMotor> (
		new ServoMotor (
		    new SPIParameter (0, DeviceConfig::SPI_SPEED_1MHZ, true),
		    descriptor, MECHANIC_FS));
	    m_devices.push_back (device);
	    protocol_engine->insert_communication_table_backward (
		communication_number, &(*device));
	    uint8_t comp_class =
		static_cast<uint32_t> (ComponentDescriptorEnum::POSITION_FS)
		    >> 16;
	    uint8_t comp_attribute =
		static_cast<uint16_t> (ComponentDescriptorEnum::POSITION_FS)
		    >> 8;
	    uint8_t comp_number =
		static_cast<uint8_t> (ComponentDescriptorEnum::POSITION_FS);
	    ComponentDescriptor* comp_desc =
		protocol_engine->create_descriptor (comp_class, comp_attribute,
						    comp_number);
	    /* for POSITION_FS */
	    protocol_engine->insert_communication_table_forward (
		comp_desc, communication_number);
	    /* for SERVO_FS */
	    protocol_engine->insert_communication_table_forward (
		descriptor, communication_number);
	  }
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_HOOK:
	  {
	    std::shared_ptr<ServoMotor> device = std::shared_ptr<ServoMotor> (
		new ServoMotor (
		    new SPIParameter (0, DeviceConfig::SPI_SPEED_1MHZ, true),
		    descriptor, MECHANIC_HOOK));
	    m_devices.push_back (device);
	    protocol_engine->insert_communication_table_backward (
		communication_number, &(*device));
	    uint8_t comp_class =
		static_cast<uint32_t> (ComponentDescriptorEnum::POSITION_HOOK)
		    >> 16;
	    uint8_t comp_attribute =
		static_cast<uint16_t> (ComponentDescriptorEnum::POSITION_HOOK)
		    >> 8;
	    uint8_t comp_number =
		static_cast<uint8_t> (ComponentDescriptorEnum::POSITION_HOOK);
	    ComponentDescriptor* comp_desc =
		protocol_engine->create_descriptor (comp_class, comp_attribute,
						    comp_number);
	    /* for POSITION_HOOK */
	    protocol_engine->insert_communication_table_forward (
		comp_desc, communication_number);
	    /* for SERVO_HOOK */
	    protocol_engine->insert_communication_table_forward (
		descriptor, communication_number);
	  }
	  break;
	case ComponentDescriptorEnum::SERIAL_LINK:
	  {
	    std::shared_ptr<SerialLink> device = std::shared_ptr<SerialLink> (
		new SerialLink (
		    new SPIParameter (0, DeviceConfig::SPI_SPEED_1MHZ, true),
		    descriptor));
	    m_devices.push_back (device);
	    protocol_engine->insert_communication_table_backward (
		communication_number, &(*device));
	    protocol_engine->insert_communication_table_forward (
		descriptor, communication_number);
	  }
	  break;
	case ComponentDescriptorEnum::WESTON_ANEMOMETER:
	  {
	    std::shared_ptr<WestonAnemometer> device =
		std::shared_ptr<WestonAnemometer> (
		    new WestonAnemometer (
			new I2CParameter (
			    static_cast<uint8_t> (DeviceConfig::WESTON_ANEMOMETER_ADDRESS)),
			descriptor));
	    m_devices.push_back (device);
	    protocol_engine->insert_communication_table_backward (
		communication_number, &(*device));
	    protocol_engine->insert_communication_table_forward (
		descriptor, communication_number);
	  }
	  break;
	case ComponentDescriptorEnum::WIND_VANE:
	  {
	    std::shared_ptr<WindVane> device = std::shared_ptr<WindVane> (
		new WindVane (
		    new I2CParameter (
			static_cast<uint8_t> (DeviceConfig::WIND_VANE_ADDRESS)),
		    descriptor));
	    m_devices.push_back (device);
	    protocol_engine->insert_communication_table_backward (
		communication_number, &(*device));
	    protocol_engine->insert_communication_table_forward (
		descriptor, communication_number);
	  }
	  break;
	default:
	  // No communication Device
	  protocol_engine->insert_communication_table_forward (descriptor, 0);
	  break;
	}
    }
  return 1;
}
