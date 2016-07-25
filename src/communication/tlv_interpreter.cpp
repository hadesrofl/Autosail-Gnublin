#include "tlv_interpreter.h"

TLVInterpreter::TLVInterpreter (std::shared_ptr<StreamGenerator> generator,
				std::shared_ptr<AutoPilot> autopilot,
				ProtocolEngine* protocol_engine)
{
  m_stream_generator = generator;
  m_autopilot = autopilot;
  m_protocol_engine = std::shared_ptr<ProtocolEngine> (protocol_engine);
}
void
TLVInterpreter::interpret_frame (Device* device, Frame* frame)
{
  DataStructureIdentifier data_structure_id =
      static_cast<DataStructureIdentifier> (frame->get_attribute () >> 5);
  ComponentDescriptorEnum descriptor_enum =
      static_cast<ComponentDescriptorEnum> (NULL);
  if (device != NULL)
    {
      std::shared_ptr<ComponentDescriptor> descriptor =
	  device->get_component_descriptor ();
      descriptor_enum =
	  static_cast<ComponentDescriptorEnum> (descriptor->get_component_class ()
	      << 16 | descriptor->get_component_attribute () << 8
	      | descriptor->get_component_number ());
      std::cout << "Class: "
	  << static_cast<int> (descriptor->get_component_class ())
	  << "\tAttribute: "
	  << static_cast<int> (descriptor->get_component_attribute ())
	  << "\tNumber: "
	  << static_cast<int> (descriptor->get_component_number ())
	  << std::endl;
//      std::cout << "Descriptor Enum: " << static_cast<int> (descriptor_enum)
//	  << std::endl;
    }

  switch (frame->get_tag ())
    {
    /* Priority Commands */
    case TagEnum::GET_PROTOCOL_VERSION:
      {
	std::vector<uint8_t> protocol_version =
	    m_protocol_engine->get_protocol_version ();
	uint8_t attribute = m_protocol_engine->tlve4_attribute (
	    DataStructureIdentifier::INT8, 0x00);
	Frame* frame = m_protocol_engine->create_frame (
	    TagEnum::VALUE_PROTOCOL_VERSION, attribute, 4, protocol_version);
	m_protocol_engine->send_frame (frame);
      }
      break;
    case TagEnum::GET_BOAT_ID:
      {
	std::vector<uint8_t> payload;
	payload.push_back (m_protocol_engine->get_boat_id ());
	Frame* frame = m_protocol_engine->create_frame (TagEnum::VALUE_BOAT_ID,
							0, 1, payload);
	m_protocol_engine->send_frame (frame);
	payload.clear ();
      }
      break;
    case TagEnum::SET_CONTROL_MODE:
      {
	m_protocol_engine->set_control_mode (frame->get_payload ().at (0));
	/* In Priority Mode there is autopilot function,
	 * which might interrupt priority commands
	 */
	if (m_protocol_engine->get_control_mode () == 0x00)
	  {
	    m_autopilot->autopilot_on (false);
	  }
      }
      break;
    case TagEnum::PM_SET:
      switch (descriptor_enum)
	{
	case ComponentDescriptorEnum::SERVO_MOTOR_RUDDER:
	  {
	    int8_t* buf = new int8_t[2];
	    buf[0] = frame->get_payload ().at (0);
	    buf[1] = frame->get_payload ().at (1);
	    int16_t angle = IntConverter::int8_to_int16 (buf);
	    delete[] buf;
	    dynamic_cast<ServoMotor*> (device)->set_angle (angle);
	  }
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_MAIN_SAIL:
	  {
	    int8_t* buf = new int8_t[2];
	    buf[0] = frame->get_payload ().at (0);
	    buf[1] = frame->get_payload ().at (1);
	    int16_t angle = IntConverter::int8_to_int16 (buf);
	    delete[] buf;
	    dynamic_cast<ServoMotor*> (device)->set_angle (angle);
	  }
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_FORE_SAIL:
	  {
	    int8_t* buf = new int8_t[2];
	    buf[0] = frame->get_payload ().at (0);
	    buf[1] = frame->get_payload ().at (1);
	    int16_t angle = IntConverter::int8_to_int16 (buf);
	    delete[] buf;
	    dynamic_cast<ServoMotor*> (device)->set_angle (angle);
	  }
	  break;
	default:
	  break;
	}
      break;
    case TagEnum::ERROR:
      //TODO: Do something?
      break;
    case TagEnum::GET_BOAT_DESCRIPTION:
      {
	std::vector<uint8_t> payload;
	map<std::shared_ptr<ComponentDescriptor>, uint8_t> comm_table =
	    m_protocol_engine->get_communication_table_forward ();
	typedef std::map<std::shared_ptr<ComponentDescriptor>, uint8_t,
	    std::string>::iterator it_type;
	for (it_type iterator = comm_table.begin ();
	    iterator != comm_table.end (); iterator++)
	  {
	    payload.push_back (iterator->second);
	    payload.push_back (iterator->first->get_component_class ());
	    payload.push_back (iterator->first->get_component_attribute ());
	    payload.push_back (iterator->first->get_component_number ());
	  }
	uint8_t attribute = m_protocol_engine->tlve4_attribute (
	    DataStructureIdentifier::UINT8, 0x00);
	Frame* frame = m_protocol_engine->create_frame (
	    TagEnum::VALUE_BOAT_DESCRIPTION, attribute, payload.size () + 1,
	    payload);
	m_protocol_engine->send_frame (frame);
      }
      break;
    case TagEnum::GET_CONTROL_MODE:
      {
	std::vector<uint8_t> payload;
	payload.push_back (m_protocol_engine->get_control_mode ());
	Frame* frame = m_protocol_engine->create_frame (
	    TagEnum::VALUE_CONTROL_MODE, 0, 1, payload);
	m_protocol_engine->send_frame (frame);
	payload.clear ();
      }
      break;
      /* Normal Mode */
    case TagEnum::SET_VALUE:
      switch (descriptor_enum)
	{
	/*------------------------------------------
	 On-Board Software
	 ------------------------------------------*/
	case ComponentDescriptorEnum::STREAM_CONTROL_UNIT:
	  //TODO: Get some other fancy idea for getting Stream Generator
	  //maybe add StreamGenerator to Interpreter? & BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::AUTOPILOT:
	  //TODO: Do something!
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_RUDDER:
	  {
	    int8_t* buf = new int8_t[2];
	    buf[0] = frame->get_payload ().at (0);
	    buf[1] = frame->get_payload ().at (1);
	    int16_t angle = IntConverter::int8_to_int16 (buf);
	    delete[] buf;
	    dynamic_cast<ServoMotor*> (device)->set_angle (angle);
	  }
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_MAIN_SAIL:
	  {
	    int8_t* buf = new int8_t[2];
	    buf[0] = frame->get_payload ().at (0);
	    buf[1] = frame->get_payload ().at (1);
	    int16_t angle = IntConverter::int8_to_int16 (buf);
	    delete[] buf;
	    dynamic_cast<ServoMotor*> (device)->set_angle (angle);
	  }
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_FORE_SAIL:
	  {
	    int8_t* buf = new int8_t[2];
	    buf[0] = frame->get_payload ().at (0);
	    buf[1] = frame->get_payload ().at (1);
	    int16_t angle = IntConverter::int8_to_int16 (buf);
	    delete[] buf;
	    dynamic_cast<ServoMotor*> (device)->set_angle (angle);
	  }
	  break;
	default:
	  break;
	}
      break;
    case TagEnum::REQUEST_VALUE:
      //TODO: Do something!
      switch (frame->get_length ())
	{
	/* Get all streams */
	case 1:
	  break;
	  /* Get one stream */
	case 2:
	  break;
	}

      break;
    case TagEnum::REQUEST_VALUE_W_TIMESTAMP:
      switch (descriptor_enum)
	{
	/*------------------------------------------
	 Actor
	 ------------------------------------------*/
	case ComponentDescriptorEnum::POSITION_RUDDER:
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::POSITION_MAIN_SAIL:
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::POSITION_FORE_SAIL:
	  //TODO: BlackMagic Commands
	  break;
	  /*------------------------------------------
	   System Info
	   ------------------------------------------*/
	case ComponentDescriptorEnum::POWER_SUPPLY_SENSING:
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::GPS_VALIDITY_LEA_6H:
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::AUTOPILOT_SYSTEM_INFO:
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::BILGE_WATER_DETECTION:
	  dynamic_cast<Hygrometer*> (device);
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::STREAMING_SYSTEM_INFO:
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::GPS_SYSTEM_INFO:
	  //TODO: BlackMagic Commands
	  break;
	  /*------------------------------------------
	   Wind
	   ------------------------------------------*/
	case ComponentDescriptorEnum::ANEMOMETER:
	  dynamic_cast<Anemometer*> (device);
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::WESTON_ANEMOMETER:
	  dynamic_cast<WestonAnemometer*> (device);
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::WIND_VANE:
	  dynamic_cast<WindVane*> (device);
	  //TODO: BlackMagic Commands
	  break;
	  /*------------------------------------------
	   Speed
	   ------------------------------------------*/
	case ComponentDescriptorEnum::GPS_VELOCITY:
	  dynamic_cast<GPS*> (device);
	  //TODO: BlackMagic Commands
	  break;
	  /*------------------------------------------
	   Positioning
	   ------------------------------------------*/
	case ComponentDescriptorEnum::GPS_POSITION:

	  dynamic_cast<GPS*> (device);
	  //TODO: BlackMagic Commands
	  break;
	  /*------------------------------------------
	   Orientation
	   ------------------------------------------*/
	case ComponentDescriptorEnum::ACCELEROMETER:
	  dynamic_cast<Accelerometer*> (device);
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::COMPASS:
	  dynamic_cast<Compass*> (device);
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::GYROSCOPE:
	  dynamic_cast<Gyroscope*> (device);
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::ORIENTATION_COMPUTED_9DOF:
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::ORIENTATION_COMPUTED_BOAT:
	  //TODO: BlackMagic Commands
	  break;
	default:
	  //TODO: something fancy
	  break;
	}
      break;
    default:
      //TODO: Ignore?
      break;
    }
}
TLVInterpreter::~TLVInterpreter ()
{

}
