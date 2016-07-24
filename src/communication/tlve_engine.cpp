#include "tlve_engine.h"

TLVEEngine::TLVEEngine (std::shared_ptr<StreamGenerator> generator,
			std::shared_ptr<AutoPilot> autopilot,
			std::vector<uint8_t> protocol_version)
{
  m_interpreter = std::unique_ptr<TLVInterpreter> (
      new TLVInterpreter (generator, autopilot, this));
  m_protocol_version = protocol_version;
}

TLVFrame*
TLVEEngine::send_boat_description ()
{
  return new TLVFrame ();
}

TLVFrame*
TLVEEngine::create_frame (TagEnum tag, uint8_t attribute, uint8_t length,
			  std::vector<uint8_t> payload)
{
  return new TLVFrame (tag, attribute, length, payload);
}
TLVFrame*
TLVEEngine::create_frame (TagEnum tag, uint8_t attribute, uint8_t length)
{
  return new TLVFrame (tag, attribute, length);
}

TLVFrame*
TLVEEngine::create_frame ()
{
  return new TLVFrame ();
}
void
TLVEEngine::send_frame (std::shared_ptr<Device> device,
			std::vector<int8_t> data)
{

}
void
TLVEEngine::interpret_frame (Frame* frame)
{
  uint8_t communication_number =
      frame->get_attribute () & COMMUNICATION_NUMBER_BITMASK;
  m_interpreter->interpret_frame (
      &(*m_communication_table_backward[communication_number]), frame);
}

TLVEEngine::~TLVEEngine ()
{

}

