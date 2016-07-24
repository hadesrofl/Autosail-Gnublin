#include "tlv_interpreter.h"

TLVInterpreter::TLVInterpreter (std::shared_ptr<StreamGenerator> generator,
				std::shared_ptr<AutoPilot> autopilot,
				ProtocolEngine* protocol_engine)
{
  m_stream_generator = generator;
  m_autopilot = autopilot;
  m_protocol_engine = std::shared_ptr<ProtocolEngine> (protocol_engine);
}
Frame*
TLVInterpreter::interpret_frame (Device* device, Frame* frame)
{
  DataStructureIdentifier data_structure_id =
      static_cast<DataStructureIdentifier> (frame->get_attribute () >> 5);
  std::shared_ptr<ComponentDescriptor> descriptor =
      device->get_component_descriptor ();
  ComponentDescriptorEnum descriptor_enum =
      static_cast<ComponentDescriptorEnum> (descriptor->get_component_class ()
	  + descriptor->get_component_attribute ());

  switch (frame->get_tag ())
    {
    // Priority Commands
    case TagEnum::GET_PROTOCOL_VERSION:
      //TODO: Do something!
      break;
    case TagEnum::GET_BOAT_ID:
      //TODO: Do something!
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
	/*------------------------------------------
	 Actor
	 ------------------------------------------*/
	case ComponentDescriptorEnum::SERVO_MOTOR_RUDDER:
	  dynamic_cast<ServoMotor*> (device);
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_MAIN_SAIL:
	  dynamic_cast<ServoMotor*> (device);
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_FORE_SAIL:
	  dynamic_cast<ServoMotor*> (device);
	  //TODO: BlackMagic Commands
	  break;
	default:
	  break;
	}
      //TODO: Do something!
      break;
    case TagEnum::ERROR:
      //TODO: Do something?
      break;
    case TagEnum::GET_BOAT_DESCRIPTION:
      //TODO: Do something!
      break;
    case TagEnum::GET_CONTROL_MODE:
      //TODO: Do something!
      break;
      //TODO: Add other Commands
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
	  break;
	  /*------------------------------------------
	   System Info
	   ------------------------------------------*/
	case ComponentDescriptorEnum::POWER_SUPPLY_SENSING:
	  break;
	case ComponentDescriptorEnum::POSITION_RUDDER:
	  break;
	case ComponentDescriptorEnum::POSITION_MAIN_SAIL:
	  break;
	case ComponentDescriptorEnum::POSITION_FORE_SAIL:
	  break;
	case ComponentDescriptorEnum::GPS_VALIDITY_LEA_6H:
	  break;
	case ComponentDescriptorEnum::AUTOPILOT_SYSTEM_INFO:
	  break;
	case ComponentDescriptorEnum::BILGE_WATER_DETECTION:
	  dynamic_cast<Hygrometer*> (device);
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::STREAMING_SYSTEM_INFO:
	  break;
	case ComponentDescriptorEnum::GPS_SYSTEM_INFO:
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
	  break;
	case ComponentDescriptorEnum::ORIENTATION_COMPUTED_BOAT:
	  break;
	default:
	  break;
	}
      break;
    case TagEnum::REQUEST_VALUE:
      //TODO: Do something!
      break;
    case TagEnum::REQUEST_VALUE_W_TIMESTAMP:
      //TODO: Do something!
      break;
    default:
      //TODO: Ignore?
      break;
    }
  return NULL;
}
TLVInterpreter::~TLVInterpreter ()
{

}
