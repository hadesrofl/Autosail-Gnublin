#include "tlve_engine.h"

// private functions

// public functions

TLVEEngine::TLVEEngine (std::shared_ptr<StreamGenerator> generator,
			std::shared_ptr<AutoPilot> autopilot,
			std::vector<uint8_t> protocol_version, uint8_t boat_id)
{
  m_protocol_version = protocol_version;
  m_boat_id = boat_id;
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
TLVEEngine::send_stream (std::shared_ptr<Device> device,
			 std::vector<int8_t> data)
{

}
void
TLVEEngine::send_frame (Frame* frame)
{
  //TODO: no send at Attribute == 0, may check in Serial Link
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
  delete frame;
}
void
TLVEEngine::interpret_frame (Frame* frame)
{
  uint8_t communication_number;
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

