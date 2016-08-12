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
  uint8_t communication_number = (frame->get_attribute () & 0x1F);
  ComponentDescriptorEnum descriptor_enum =
      static_cast<ComponentDescriptorEnum> (NULL);
  std::shared_ptr<ComponentDescriptor> descriptor = NULL;
  if (device != NULL)
    {
      descriptor = device->get_component_descriptor ();
    }
  else if (m_autopilot != NULL
      && m_autopilot->get_communication_number () == communication_number)
    {
      descriptor = m_autopilot->get_component_descriptor ();
    }
  else if (m_stream_generator != NULL
      && m_stream_generator->get_communication_number ()
	  == communication_number)
    {
      descriptor = m_stream_generator->get_component_descriptor ();
    }
  // if descriptor != NULL start interpreting
  if (descriptor != NULL)
    {
      descriptor_enum =
	  static_cast<ComponentDescriptorEnum> (descriptor->get_component_class ()
	      << 16 | descriptor->get_component_attribute () << 8
	      | descriptor->get_component_number ());
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
	if(frame->get_payload().size() > 0){
	m_protocol_engine->set_control_mode (frame->get_payload ().at (0));
	/* In Priority Mode there is autopilot function,
	 * which might interrupt priority commands
	 */
	if (m_protocol_engine->get_control_mode () == PRIORITY_MODE)
	  {
	    m_autopilot->set_active (false);
	  }
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
	case ComponentDescriptorEnum::SERVO_MOTOR_MS:
	  {
	    int8_t* buf = new int8_t[2];
	    buf[0] = frame->get_payload ().at (0);
	    buf[1] = frame->get_payload ().at (1);
	    int16_t angle = IntConverter::int8_to_int16 (buf);
	    delete[] buf;
	    dynamic_cast<ServoMotor*> (device)->set_angle (angle);
	  }
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_FS:
	  {
	    int8_t* buf = new int8_t[2];
	    buf[0] = frame->get_payload ().at (0);
	    buf[1] = frame->get_payload ().at (1);
	    int16_t angle = IntConverter::int8_to_int16 (buf);
	    delete[] buf;
	    dynamic_cast<ServoMotor*> (device)->set_angle (angle);
	  }
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_HOOK:
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
	  m_protocol_engine->send_error (ERROR_UNKNOWN_COMP,
					 (uint8_t*) ERROR_UNKNOWN_COMP_MSG,
					 ERROR_UNKNOWN_COMP_MSG_LENGTH);
	  break;
	}
      break;
    case TagEnum::ERROR:
      //Ignore frame
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
	  {
	    std::vector<uint8_t> payload;
	    uint8_t attribute, *cn, *period_ack;
	    int8_t* tmp = new int8_t[2];
	    // Get communication number
	    tmp[0] = frame->get_payload ().at (0);
	    tmp[1] = frame->get_payload ().at (1);
	    int16_t comm_number = IntConverter::int8_to_int16 (tmp);
	    // Get period
	    tmp[0] = frame->get_payload ().at (2);
	    tmp[1] = frame->get_payload ().at (3);
	    std::shared_ptr<Device> device = m_protocol_engine->get_device (
		comm_number);
	    int16_t period = IntConverter::int8_to_int16 (tmp);
	    if (period > 0)
	      {
		m_stream_generator->add_stream (device, comm_number, period);
	      }
	    else
	      {
		m_stream_generator->disable_stream (comm_number);
	      }
	    Stream* stream = m_stream_generator->get_stream (comm_number);
	    attribute = m_protocol_engine->tlve4_attribute (
		DataStructureIdentifier::INT16, communication_number);
	    period_ack = IntConverter::uint16_to_uint8 (stream->get_period ());
	    cn = IntConverter::uint16_to_uint8 (
		stream->get_communication_number ());
	    payload.push_back (cn[0]);
	    payload.push_back (cn[1]);
	    payload.push_back (period_ack[0]);
	    payload.push_back (period_ack[1]);
	    Frame* frame = m_protocol_engine->create_frame (
		TagEnum::ACKNOWLEDGE_STREAM, attribute, payload.size () + 1,
		payload);
	    m_protocol_engine->send_frame (frame);
	  }
	  break;
	case ComponentDescriptorEnum::AUTOPILOT:
	  {
	    std::vector<uint8_t> payload;
	    uint8_t attribute;
	    int8_t* buf = new int8_t[2];
	    buf[0] = frame->get_payload ().at (0);
	    buf[1] = frame->get_payload ().at (1);
	    int16_t command = IntConverter::int8_to_int16 (buf);
	    buf[0] = frame->get_payload ().at (2);
	    buf[1] = frame->get_payload ().at (3);
	    int16_t direction = IntConverter::int8_to_int16 (buf);
	    int8_t ret = 0;
	    delete[] buf;
	    switch (command)
	      {
	      /* Deactivate autopilot */
	      case COMMAND_AUTOPILOT_OFF:
		ret = m_autopilot->set_active (false);
		break;
		/* Set Course */
	      case COMMAND_SET_COURSE:
		ret = m_autopilot->set_course (direction);
		break;
		/* Hold Course */
	      case COMMAND_HOLD_COURSE:
		ret = m_autopilot->hold_course ();
		break;
		/* Set and Hold Course */
	      case COMMAND_SET_AND_HOLD:
		ret = m_autopilot->set_course (direction);
		if (ret == 1)
		  {
		    ret = m_autopilot->hold_course ();
		  }
		break;
	      }
	    if (ret == 1)
	      {
		attribute = m_protocol_engine->tlve4_attribute (
		    DataStructureIdentifier::INT16,
		    m_autopilot->get_communication_number ());
		uint8_t* ts = IntConverter::uint32_to_uint8 (time (NULL));
		payload.push_back (ts[0]);
		payload.push_back (ts[1]);
		payload.push_back (ts[2]);
		payload.push_back (ts[3]);
		delete[] ts;
		int8_t* status = IntConverter::int16_to_int8 (
		    m_autopilot->get_status ());
		payload.push_back (status[0]);
		payload.push_back (status[1]);
		delete[] status;
		if (m_autopilot->get_status () == STATUS_HOLD_COURSE)
		  {
		    int8_t* direction = IntConverter::int16_to_int8 (
			m_autopilot->get_course ());
		    payload.push_back (direction[0]);
		    payload.push_back (direction[1]);
		    delete[] direction;
		  }
		else
		  {
		    payload.push_back (PADDING_DIRECTION_1);
		    payload.push_back (PADDING_DIRECTION_2);
		  }
		Frame* frame = m_protocol_engine->create_frame (
		    TagEnum::VALUE_RESPONSE_W_TIMESTAMP, attribute,
		    payload.size () + 1, payload);
		m_protocol_engine->send_frame (frame);
	      }
	  }
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
	case ComponentDescriptorEnum::SERVO_MOTOR_MS:
	  {
	    int8_t* buf = new int8_t[2];
	    buf[0] = frame->get_payload ().at (0);
	    buf[1] = frame->get_payload ().at (1);
	    int16_t angle = IntConverter::int8_to_int16 (buf);
	    delete[] buf;
	    dynamic_cast<ServoMotor*> (device)->set_angle (angle);
	  }
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_FS:
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
	  m_protocol_engine->send_error (ERROR_UNKNOWN_COMP,
					 (uint8_t*) ERROR_UNKNOWN_COMP_MSG,
					 ERROR_UNKNOWN_COMP_MSG_LENGTH);
	  break;
	}
      break;
    case TagEnum::REQUEST_VALUE:
      switch (descriptor_enum)
	{
	case ComponentDescriptorEnum::STREAM_CONTROL_UNIT:
	  switch (frame->get_length ())
	    {
	    /* Get all streams */
	    case 1:
	      {
		std::vector<uint8_t> payload;
		std::vector<Stream*> streams =
		    m_stream_generator->get_streams ();
		uint8_t attribute;
		attribute = m_protocol_engine->tlve4_attribute (
		    DataStructureIdentifier::INT16, communication_number);
		for (uint8_t i = 0; i < streams.size (); i++)
		  {
		    payload.push_back (0);
		    payload.push_back (
			m_protocol_engine->get_communication_number (
			    streams.at (i)->get_device ()->get_component_descriptor ()));
		    uint8_t* period = IntConverter::uint16_to_uint8 (
			streams.at (i)->get_period ());
		    payload.push_back (period[0]);
		    payload.push_back (period[1]);
		    delete[] period;
		  }
		Frame* frame = m_protocol_engine->create_frame (
		    TagEnum::VALUE_RESPONSE, attribute, payload.size () + 1,
		    payload);
		m_protocol_engine->send_frame (frame);
	      }
	      break;
	      /* Get one stream */
	    case 2:
	      {
		std::vector<uint8_t> payload;
		uint8_t attribute, comm_number;
		std::shared_ptr<Device> device = m_protocol_engine->get_device (
		    frame->get_payload ().at (0));
		comm_number = m_protocol_engine->get_communication_number (
		    device->get_component_descriptor ());
		Stream* stream = m_stream_generator->get_stream (comm_number);
		attribute = m_protocol_engine->tlve4_attribute (
		    DataStructureIdentifier::INT16, communication_number);
		if (stream != NULL)
		  {
		    payload.push_back (0);
		    payload.push_back (comm_number);
		    uint8_t* period = IntConverter::uint16_to_uint8 (
			stream->get_period ());
		    payload.push_back (period[0]);
		    payload.push_back (period[1]);
		    Frame* frame = m_protocol_engine->create_frame (
			TagEnum::VALUE_RESPONSE, attribute, payload.size () + 1,
			payload);
		    m_protocol_engine->send_frame (frame);
		    delete[] period;
		  }
		else
		  {
		    m_protocol_engine->send_error (
			ERROR_UNKNOWN_STREAM,
			(uint8_t*) ERROR_UNKNOWN_STREAM_MSG,
			ERROR_UNKNOWN_STREAM_MSG_LENGTH);
		  }
	      }
	      break;
	    }
	  break;
	default:
	  m_protocol_engine->send_error (ERROR_UNKNOWN_COMP,
					 (uint8_t*) ERROR_UNKNOWN_COMP_MSG,
					 ERROR_UNKNOWN_COMP_MSG_LENGTH);
	  break;
	}
      break;
    case TagEnum::REQUEST_VALUE_W_TIMESTAMP:
      switch (descriptor_enum)
	{
	/*------------------------------------------
	 Actor
	 ------------------------------------------*/
	case ComponentDescriptorEnum::SERVO_MOTOR_RUDDER:
	  {
	    std::vector<uint8_t> payload;
	    uint8_t* angle = IntConverter::uint16_to_uint8 (
		dynamic_cast<ServoMotor*> (device)->get_angle ());
	    uint8_t attribute = m_protocol_engine->tlve4_attribute (
		DataStructureIdentifier::INT16,
		m_protocol_engine->get_communication_number (
		    device->get_component_descriptor ()));
	    uint8_t* ts = IntConverter::uint32_to_uint8 (time (NULL));
	    payload.push_back (ts[0]);
	    payload.push_back (ts[1]);
	    payload.push_back (ts[2]);
	    payload.push_back (ts[3]);
	    payload.push_back (angle[0]);
	    payload.push_back (angle[1]);
	    delete[] ts;
	    delete[] angle;
	    Frame* frame = m_protocol_engine->create_frame (
		TagEnum::VALUE_RESPONSE_W_TIMESTAMP, attribute,
		payload.size () + 1, payload);
	    m_protocol_engine->send_frame (frame);
	  }
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_MS:
	  {
	    std::vector<uint8_t> payload;
	    uint8_t* angle = IntConverter::uint16_to_uint8 (
		dynamic_cast<ServoMotor*> (device)->get_angle ());
	    uint8_t attribute = m_protocol_engine->tlve4_attribute (
		DataStructureIdentifier::INT16,
		m_protocol_engine->get_communication_number (
		    device->get_component_descriptor ()));
	    uint8_t* ts = IntConverter::uint32_to_uint8 (time (NULL));
	    payload.push_back (ts[0]);
	    payload.push_back (ts[1]);
	    payload.push_back (ts[2]);
	    payload.push_back (ts[3]);
	    payload.push_back (angle[0]);
	    payload.push_back (angle[1]);
	    delete[] ts;
	    delete[] angle;
	    Frame* frame = m_protocol_engine->create_frame (
		TagEnum::VALUE_RESPONSE_W_TIMESTAMP, attribute,
		payload.size () + 1, payload);
	    m_protocol_engine->send_frame (frame);
	  }
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_FS:
	  {
	    std::vector<uint8_t> payload;
	    uint8_t* angle = IntConverter::uint16_to_uint8 (
		dynamic_cast<ServoMotor*> (device)->get_angle ());
	    uint8_t attribute = m_protocol_engine->tlve4_attribute (
		DataStructureIdentifier::INT16,
		m_protocol_engine->get_communication_number (
		    device->get_component_descriptor ()));
	    uint8_t* ts = IntConverter::uint32_to_uint8 (time (NULL));
	    payload.push_back (ts[0]);
	    payload.push_back (ts[1]);
	    payload.push_back (ts[2]);
	    payload.push_back (ts[3]);
	    payload.push_back (angle[0]);
	    payload.push_back (angle[1]);
	    delete[] ts;
	    delete[] angle;
	    Frame* frame = m_protocol_engine->create_frame (
		TagEnum::VALUE_RESPONSE_W_TIMESTAMP, attribute,
		payload.size () + 1, payload);
	    m_protocol_engine->send_frame (frame);
	  }
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR_HOOK:
	  {
	    std::vector<uint8_t> payload;
	    uint8_t* angle = IntConverter::uint16_to_uint8 (
		dynamic_cast<ServoMotor*> (device)->get_angle ());
	    uint8_t attribute = m_protocol_engine->tlve4_attribute (
		DataStructureIdentifier::INT16,
		m_protocol_engine->get_communication_number (
		    device->get_component_descriptor ()));
	    uint8_t* ts = IntConverter::uint32_to_uint8 (time (NULL));
	    payload.push_back (ts[0]);
	    payload.push_back (ts[1]);
	    payload.push_back (ts[2]);
	    payload.push_back (ts[3]);
	    payload.push_back (angle[0]);
	    payload.push_back (angle[1]);
	    delete[] ts;
	    delete[] angle;
	    Frame* frame = m_protocol_engine->create_frame (
		TagEnum::VALUE_RESPONSE_W_TIMESTAMP, attribute,
		payload.size () + 1, payload);
	    m_protocol_engine->send_frame (frame);
	  }
	  break;
	  /*------------------------------------------
	   System Info
	   ------------------------------------------*/
	case ComponentDescriptorEnum::POWER_SUPPLY_SENSING:
	  {
	    std::vector<uint8_t> payload;
	    std::vector<int8_t> data = device->read_data ();
	    uint8_t attribute = m_protocol_engine->tlve4_attribute (
		DataStructureIdentifier::INT16,
		m_protocol_engine->get_communication_number (
		    device->get_component_descriptor ()));
	    uint8_t* ts = IntConverter::uint32_to_uint8 (time (NULL));
	    payload.push_back (ts[0]);
	    payload.push_back (ts[1]);
	    payload.push_back (ts[2]);
	    payload.push_back (ts[3]);
	    if (data.size () > 0)
	      {
		payload.push_back (data.at (0));
		payload.push_back (data.at (1));
		payload.push_back (data.at (2));
		payload.push_back (data.at (3));
	      }
	    //TODO: Error Message?
	    else
	      {
		payload.push_back (0);
		payload.push_back (0);
		payload.push_back (0);
		payload.push_back (0);
	      }
	    delete[] ts;
	    data.clear ();
	    Frame* frame = m_protocol_engine->create_frame (
		TagEnum::VALUE_RESPONSE_W_TIMESTAMP, attribute,
		payload.size () + 1, payload);
	    m_protocol_engine->send_frame (frame);
	  }
	  break;
	case ComponentDescriptorEnum::AUTOPILOT_SYSTEM_INFO:
	  //TODO: response with idk
	  m_protocol_engine->send_error (
	  ERROR_NOT_SUPPORTED_TAG,
					 (uint8_t*) ERROR_NOT_SUPPORTED_TAG_MSG,
					 ERROR_NOT_SUPPORTED_TAG_MSG_LENGTH);
	  break;
	case ComponentDescriptorEnum::BILGE_WATER_DETECTION:
	  dynamic_cast<Hygrometer*> (device);
	  //XXX NOT SUPPORTED YET
	  m_protocol_engine->send_error (
	  ERROR_NOT_SUPPORTED_TAG,
					 (uint8_t*) ERROR_NOT_SUPPORTED_TAG_MSG,
					 ERROR_NOT_SUPPORTED_TAG_MSG_LENGTH);
	  break;
	case ComponentDescriptorEnum::STREAMING_SYSTEM_INFO:
	  //TODO: response with idk
	  m_protocol_engine->send_error (
	  ERROR_NOT_SUPPORTED_TAG,
					 (uint8_t*) ERROR_NOT_SUPPORTED_TAG_MSG,
					 ERROR_NOT_SUPPORTED_TAG_MSG_LENGTH);
	  break;
	case ComponentDescriptorEnum::GPS_DOP:
	  //XXX NOT SUPPORTED YET
	  m_protocol_engine->send_error (
	  ERROR_NOT_SUPPORTED_TAG,
					 (uint8_t*) ERROR_NOT_SUPPORTED_TAG_MSG,
					 ERROR_NOT_SUPPORTED_TAG_MSG_LENGTH);
	  break;
	  /*------------------------------------------
	   Wind
	   ------------------------------------------*/
	case ComponentDescriptorEnum::ANEMOMETER:
	  {
	    std::vector<uint8_t> payload;
	    std::vector<int8_t> data = device->read_data ();
	    uint8_t attribute = m_protocol_engine->tlve4_attribute (
		DataStructureIdentifier::INT16,
		m_protocol_engine->get_communication_number (
		    device->get_component_descriptor ()));
	    uint8_t* ts = IntConverter::uint32_to_uint8 (time (NULL));
	    payload.push_back (ts[0]);
	    payload.push_back (ts[1]);
	    payload.push_back (ts[2]);
	    payload.push_back (ts[3]);
	    if (data.size () > 0)
	      {
		payload.push_back (data.at (0));
		payload.push_back (data.at (1));
	      }
	    //TODO: Error Message
	    else
	      {
		payload.push_back (0);
		payload.push_back (0);
	      }
	    delete[] ts;
	    data.clear ();
	    Frame* frame = m_protocol_engine->create_frame (
		TagEnum::VALUE_RESPONSE_W_TIMESTAMP, attribute,
		payload.size () + 1, payload);
	    m_protocol_engine->send_frame (frame);
	  }
	  break;
	case ComponentDescriptorEnum::WESTON_ANEMOMETER:
	  // XXX NOT SUPPORTED YET
	  m_protocol_engine->send_error (
	  ERROR_NOT_SUPPORTED_TAG,
					 (uint8_t*) ERROR_NOT_SUPPORTED_TAG_MSG,
					 ERROR_NOT_SUPPORTED_TAG_MSG_LENGTH);
	  break;
	case ComponentDescriptorEnum::WIND_VANE:
	  {
	    std::vector<uint8_t> payload;
	    std::vector<int8_t> data = device->read_data ();
	    uint8_t attribute = m_protocol_engine->tlve4_attribute (
		DataStructureIdentifier::INT16,
		m_protocol_engine->get_communication_number (
		    device->get_component_descriptor ()));
	    uint8_t* ts = IntConverter::uint32_to_uint8 (time (NULL));
	    payload.push_back (ts[0]);
	    payload.push_back (ts[1]);
	    payload.push_back (ts[2]);
	    payload.push_back (ts[3]);
	    if (data.size () > 0)
	      {
		payload.push_back (data.at (0));
		payload.push_back (data.at (1));

	      }
	    //TODO: Error Message?
	    else
	      {
		payload.push_back (0);
		payload.push_back (0);
	      }
	    delete[] ts;
	    data.clear ();
	    Frame* frame = m_protocol_engine->create_frame (
		TagEnum::VALUE_RESPONSE_W_TIMESTAMP, attribute,
		payload.size () + 1, payload);
	    m_protocol_engine->send_frame (frame);
	  }
	  break;
	  /*------------------------------------------
	   Positioning
	   ------------------------------------------*/
	case ComponentDescriptorEnum::GPS_POSITION:
	  {
	    if (dynamic_cast<GPS*> (device)->is_active () == true)
	      {
		uint8_t gps_number =
		    m_protocol_engine->get_communication_number (
			device->get_component_descriptor ());
		/* Position data is requested */
		if (communication_number == gps_number)
		  {
		    std::vector<uint8_t> payload;
		    std::vector<int8_t> data;
		    uint32_t timestamp = time (NULL);
		    // If data is older than 500ms, read new
		    if (timestamp
			- dynamic_cast<GPS*> (device)->get_last_data ()->timestamp
			>= 500 * 1000)
		      {
			data = device->read_data ();
		      }
		    gps_data_t* last_data =
			dynamic_cast<GPS*> (device)->get_last_data ();
		    uint8_t attribute = m_protocol_engine->tlve4_attribute (
			DataStructureIdentifier::INT32,
			m_protocol_engine->get_communication_number (
			    device->get_component_descriptor ()));
		    uint8_t* ts = IntConverter::uint32_to_uint8 (time (NULL));
		    payload.push_back (ts[0]);
		    payload.push_back (ts[1]);
		    payload.push_back (ts[2]);
		    payload.push_back (ts[3]);
		    int8_t* longitude = IntConverter::int32_to_int8 (
			last_data->longitude);
		    int8_t* latitude = IntConverter::int32_to_int8 (
			last_data->latitude);
		    payload.push_back (latitude[0]);
		    payload.push_back (latitude[1]);
		    payload.push_back (latitude[2]);
		    payload.push_back (latitude[3]);
		    payload.push_back (longitude[0]);
		    payload.push_back (longitude[1]);
		    payload.push_back (longitude[2]);
		    payload.push_back (longitude[3]);
		    delete[] ts;
		    delete[] longitude;
		    delete[] latitude;
		    data.clear ();
		    Frame* frame = m_protocol_engine->create_frame (
			TagEnum::VALUE_RESPONSE_W_TIMESTAMP, attribute,
			payload.size () + 1, payload);
		    m_protocol_engine->send_frame (frame);
		  }
		/* validity is requested */
		else if (communication_number == gps_number + 1)
		  {
		    std::vector<uint8_t> payload;
		    std::vector<int8_t> data;
		    uint32_t timestamp = time (NULL);
		    // If data is older than 500ms, read new
		    if (timestamp
			- dynamic_cast<GPS*> (device)->get_last_data ()->timestamp
			>= 500 * 1000)
		      {
			data = device->read_data ();
		      }
		    gps_data_t* last_data =
			dynamic_cast<GPS*> (device)->get_last_data ();
		    uint8_t attribute = m_protocol_engine->tlve4_attribute (
			DataStructureIdentifier::INT16,
			m_protocol_engine->get_communication_number (
			    device->get_component_descriptor ()));
		    uint8_t* ts = IntConverter::uint32_to_uint8 (time (NULL));
		    payload.push_back (ts[0]);
		    payload.push_back (ts[1]);
		    payload.push_back (ts[2]);
		    payload.push_back (ts[3]);
		    payload.push_back (last_data->fix_mode);
		    delete[] ts;
		    data.clear ();
		    Frame* frame = m_protocol_engine->create_frame (
			TagEnum::VALUE_RESPONSE_W_TIMESTAMP, attribute,
			payload.size () + 1, payload);
		    m_protocol_engine->send_frame (frame);
		  }
		/*velocity is requested */
		else if (communication_number == gps_number + 2)
		  {
		    std::vector<uint8_t> payload;
		    std::vector<int8_t> data;
		    uint32_t timestamp = time (NULL);
		    // If data is older than 500ms, read new
		    if (timestamp
			- dynamic_cast<GPS*> (device)->get_last_data ()->timestamp
			>= 500 * 1000)
		      {
			data = device->read_data ();
		      }
		    gps_data_t* last_data =
			dynamic_cast<GPS*> (device)->get_last_data ();
		    uint8_t attribute = m_protocol_engine->tlve4_attribute (
			DataStructureIdentifier::INT16,
			m_protocol_engine->get_communication_number (
			    device->get_component_descriptor ()));
		    uint8_t* ts = IntConverter::uint32_to_uint8 (time (NULL));
		    payload.push_back (ts[0]);
		    payload.push_back (ts[1]);
		    payload.push_back (ts[2]);
		    payload.push_back (ts[3]);
		    int8_t* speed = IntConverter::int16_to_int8 (
			last_data->speed);
		    int8_t* direction = IntConverter::int16_to_int8 (
			last_data->direction);
		    payload.push_back (direction[0]);
		    payload.push_back (direction[1]);
		    payload.push_back (speed[0]);
		    payload.push_back (speed[1]);
		    delete[] ts;
		    delete[] speed;
		    delete[] direction;
		    data.clear ();
		    Frame* frame = m_protocol_engine->create_frame (
			TagEnum::VALUE_RESPONSE_W_TIMESTAMP, attribute,
			payload.size () + 1, payload);
		    m_protocol_engine->send_frame (frame);
		  }
	      }
	    else
	      {
		m_protocol_engine->send_error (
		    ERROR_UNKNOWN_COMP, (uint8_t*) ERROR_UNKNOWN_COMP_MSG,
		    ERROR_UNKNOWN_COMP_MSG_LENGTH);
	      }
	  }
	  break;
	  /*------------------------------------------
	   Orientation
	   ------------------------------------------*/
	case ComponentDescriptorEnum::ACCELEROMETER:
	  {
	    std::vector<uint8_t> payload;
	    std::vector<int8_t> data = device->read_data ();
	    uint8_t attribute = m_protocol_engine->tlve4_attribute (
		DataStructureIdentifier::INT16,
		m_protocol_engine->get_communication_number (
		    device->get_component_descriptor ()));
	    uint8_t* ts = IntConverter::uint32_to_uint8 (time (NULL));
	    payload.push_back (ts[0]);
	    payload.push_back (ts[1]);
	    payload.push_back (ts[2]);
	    payload.push_back (ts[3]);
	    if (data.size () > 0)
	      {
		/* Add x value */
		payload.push_back (data.at (0));
		payload.push_back (data.at (1));
		/* Add y value */
		payload.push_back (data.at (2));
		payload.push_back (data.at (3));
		/* Add z value */
		payload.push_back (data.at (4));
		payload.push_back (data.at (5));
	      }
	    else
	    //TODO: Error Message?
	      {
		payload.push_back (0);
		payload.push_back (0);
		payload.push_back (0);
		payload.push_back (0);
		payload.push_back (0);
		payload.push_back (0);
	      }
	    delete[] ts;
	    data.clear ();
	    Frame* frame = m_protocol_engine->create_frame (
		TagEnum::VALUE_RESPONSE_W_TIMESTAMP, attribute,
		payload.size () + 1, payload);
	    m_protocol_engine->send_frame (frame);
	  }
	  break;
	case ComponentDescriptorEnum::COMPASS:
	  {
	    std::vector<uint8_t> payload;
	    std::vector<int8_t> data = device->read_data ();
	    uint8_t attribute = m_protocol_engine->tlve4_attribute (
		DataStructureIdentifier::INT16,
		m_protocol_engine->get_communication_number (
		    device->get_component_descriptor ()));
	    uint8_t* ts = IntConverter::uint32_to_uint8 (time (NULL));
	    payload.push_back (ts[0]);
	    payload.push_back (ts[1]);
	    payload.push_back (ts[2]);
	    payload.push_back (ts[3]);
	    if (data.size () > 0)
	      {
		/* Add x value */
		payload.push_back (data.at (0));
		payload.push_back (data.at (1));
		/* Add y value */
		payload.push_back (data.at (2));
		payload.push_back (data.at (3));
		/* Add z value */
		payload.push_back (data.at (4));
		payload.push_back (data.at (5));
	      }
	    //TODO: Error Message?
	    else
	      {
		payload.push_back (0);
		payload.push_back (0);
		payload.push_back (0);
		payload.push_back (0);
		payload.push_back (0);
		payload.push_back (0);
	      }
	    delete[] ts;
	    data.clear ();
	    Frame* frame = m_protocol_engine->create_frame (
		TagEnum::VALUE_RESPONSE_W_TIMESTAMP, attribute,
		payload.size () + 1, payload);
	    m_protocol_engine->send_frame (frame);
	  }
	  break;
	case ComponentDescriptorEnum::GYROSCOPE:
	  {
	    std::vector<uint8_t> payload;
	    std::vector<int8_t> data = device->read_data ();
	    uint8_t attribute = m_protocol_engine->tlve4_attribute (
		DataStructureIdentifier::INT16,
		m_protocol_engine->get_communication_number (
		    device->get_component_descriptor ()));
	    uint8_t* ts = IntConverter::uint32_to_uint8 (time (NULL));
	    payload.push_back (ts[0]);
	    payload.push_back (ts[1]);
	    payload.push_back (ts[2]);
	    payload.push_back (ts[3]);
	    if (data.size () > 0)
	      {
		/* Add x value */
		payload.push_back (data.at (0));
		payload.push_back (data.at (1));
		/* Add y value */
		payload.push_back (data.at (2));
		payload.push_back (data.at (3));
		/* Add z value */
		payload.push_back (data.at (4));
		payload.push_back (data.at (5));
	      }
	    //TODO: Error Message?
	    else
	      {
		payload.push_back (0);
		payload.push_back (0);
		payload.push_back (0);
		payload.push_back (0);
		payload.push_back (0);
		payload.push_back (0);
	      }
	    delete[] ts;
	    data.clear ();
	    Frame* frame = m_protocol_engine->create_frame (
		TagEnum::VALUE_RESPONSE_W_TIMESTAMP, attribute,
		payload.size () + 1, payload);
	    m_protocol_engine->send_frame (frame);
	  }
	  break;
	case ComponentDescriptorEnum::ORIENTATION_COMPUTED_9DOF:
	  //XXX NOT SUPPORTED YET
	  m_protocol_engine->send_error (
	  ERROR_NOT_SUPPORTED_TAG,
					 (uint8_t*) ERROR_NOT_SUPPORTED_TAG_MSG,
					 ERROR_NOT_SUPPORTED_TAG_MSG_LENGTH);
	  break;
	case ComponentDescriptorEnum::ORIENTATION_COMPUTED_BOAT:
	  //XXX NOT SUPPORTED YET
	  m_protocol_engine->send_error (
	  ERROR_NOT_SUPPORTED_TAG,
					 (uint8_t*) ERROR_NOT_SUPPORTED_TAG_MSG,
					 ERROR_NOT_SUPPORTED_TAG_MSG_LENGTH);
	  break;
	default:
	  m_protocol_engine->send_error (ERROR_UNKNOWN_COMP,
					 (uint8_t*) ERROR_UNKNOWN_COMP_MSG,
					 ERROR_UNKNOWN_COMP_MSG_LENGTH);
	  break;
	}
      break;
    default:
      m_protocol_engine->send_error (ERROR_UNKNOWN_TAG,
				     (uint8_t*) ERROR_UNKNOWN_TAG_MSG,
				     ERROR_UNKNOWN_TAG_MSG_LENGTH);
      break;
    }
}
TLVInterpreter::~TLVInterpreter ()
{

}
