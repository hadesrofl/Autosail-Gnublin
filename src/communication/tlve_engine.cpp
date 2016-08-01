#include "tlve_engine.h"

// public functions

TLVEEngine::TLVEEngine (std::vector<uint8_t> protocol_version, uint8_t boat_id)
{
  m_protocol_version = protocol_version;
  m_boat_id = boat_id;
  m_last_communication_number = 0;
}

void
TLVEEngine::start_interpreter (std::shared_ptr<StreamGenerator> generator,
			       std::shared_ptr<AutoPilot> autopilot)
{
  m_interpreter = std::unique_ptr<TLVInterpreter> (
      new TLVInterpreter (generator, autopilot, this));
}

TLVFrame*
TLVEEngine::send_boat_description ()
{
  return new TLVFrame ();
}
TLVFrame*
TLVEEngine::create_frame (TagEnum tag, uint8_t attribute, uint8_t length)
{
  return new TLVFrame (tag, attribute, length);
}
TLVFrame*
TLVEEngine::create_frame (TagEnum tag, uint8_t attribute, uint8_t length,
			  std::vector<uint8_t> payload)
{
  return new TLVFrame (tag, attribute, length, payload);
}
TLVFrame*
TLVEEngine::create_frame (TagEnum tag, uint8_t length)
{
  return new TLVFrame (tag, length);
}

TLVFrame*
TLVEEngine::create_frame ()
{
  return new TLVFrame ();
}
void
TLVEEngine::send_stream (Stream* stream, std::vector<int8_t> data)
{
  std::vector<uint8_t> payload;
  std::shared_ptr<Device> device = stream->get_device ();
  uint8_t * ts = IntConverter::uint32_to_uint8 (time (NULL));
  payload.push_back (ts[0]);
  payload.push_back (ts[1]);
  payload.push_back (ts[2]);
  payload.push_back (ts[3]);
  for (uint8_t i = 0; i < data.size (); i++)
    {
      payload.push_back (data.at (i));
    }
  std::cout << "Send Stream..." << std::endl;
  uint8_t attribute = tlve4_attribute (
      device->get_datastructure_id (),
      stream->get_communication_number());
  Frame* frame = create_frame (TagEnum::VALUE_RESPONSE_W_TIMESTAMP, attribute,
			       payload.size () + 1, payload);
  send_frame (frame);
  payload.clear ();
}
void
TLVEEngine::send_frame (Frame* frame)
{
#ifdef _TEST
  std::cout << "Sending Frame..." << std::endl;
  std::cout << "Frame: " << std::endl;
  std::cout << "Tag: " << static_cast<int> (frame->get_tag ()) << "\t"
      << "Length: " << static_cast<int> (frame->get_length ()) << std::endl;
  std::cout << "Payload: " << std::endl;
  std::cout << "Attribute: " << static_cast<int> (frame->get_attribute ());
  std::cout << "\tData: ";
  for (uint8_t i = 0; i < frame->get_payload ().size (); i++)
    {
      std::cout << static_cast<int> (frame->get_payload ().at (i)) << " ";
    }
  std::cout << std::endl;
#endif
  uint8_t size, i;
  uint8_t* buf;
  i = 0;
  if (frame->get_attribute () != 0)
    {
      // Tag, Length, Attribute, Sync Byte + Payload Size
      size = 4 + frame->get_payload ().size ();
      buf = new uint8_t[size];
      buf[i] = static_cast<uint8_t> (frame->get_tag ());
      i++;
      buf[i] = frame->get_length ();
      i++;
      buf[i] = frame->get_attribute ();
      i++;
    }
  else
    {
      // Tag, Length, Sync Byte + Payload Size
      size = 3 + frame->get_payload ().size ();
      buf = new uint8_t[size];
      buf[i] = static_cast<uint8_t> (frame->get_tag ());
      i++;
      buf[i] = frame->get_length ();
      i++;
    }
  for (uint8_t j = 0; j < frame->get_payload ().size (); j++)
    {
      buf[i] = frame->get_payload ().at (j);
      i++;
    }
  buf[i] = SYNC_BYTE;
#ifdef _TEST
  std::cout << "Before sending to SerialLink \nData: ";
  for (uint8_t j = 0; j < size; j++)
    {
      std::cout << static_cast<int> (buf[j]) << " ";
    }
  std::cout << std::endl;
  std::cout << "Size: " << static_cast<int> (size) << std::endl;
#endif
  m_serial_link->write (buf, size);
  delete frame;
}

void
TLVEEngine::send_error (uint8_t code, uint8_t* msg, uint8_t msg_length)
{
  std::vector<uint8_t> payload;
  for (uint8_t i = 0; i < msg_length; i++)
    {
      payload.push_back (msg[i]);
    }
#ifdef _DEBUG
  std::cout << "Message: ";
  for (uint8_t i = 0; i < payload.size (); i++)
    {
      std::cout << payload.at (i);
    }
  std::cout << std::endl;
#endif
  uint8_t attribute = tlve4_attribute (DataStructureIdentifier::STRING, code);
  Frame* frame = create_frame (TagEnum::ERROR, attribute, payload.size () + 1,
			       payload);
  send_frame (frame);
}
void
TLVEEngine::interpret_frame (Frame* frame)
{
  uint8_t communication_number = 0;
  Device* device = NULL;
  if (frame->get_tag () != TagEnum::PM_SET)
    {
      communication_number =
	  frame->get_attribute () & COMMUNICATION_NUMBER_BITMASK;
    }
  else
    {
      switch (frame->get_attribute ())
	{
	// Rudder
	case 0x44:
	  communication_number = 0x01;
	  break;
	  // Main Sail
	case 0x45:
	  communication_number = 0x02;
	  break;
	  // Fore Sail
	case 0x46:
	  communication_number = 0x03;
	  break;
	}
    }
  if (communication_number != 0)
    {
      device = &(*m_communication_table_backward[communication_number]);
    }
  m_interpreter->interpret_frame (device, frame);
}

TLVEEngine::~TLVEEngine ()
{

}

