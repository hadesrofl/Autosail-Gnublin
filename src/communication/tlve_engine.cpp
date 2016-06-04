#include "tlve_engine.h"

TLVEEngine::TLVEEngine ()
{

}

TLVFrame*
TLVEEngine::send_boat_description ()
{
  return new TLVFrame ();
}

TLVFrame*
TLVEEngine::create_frame (uint8_t tag, uint8_t attribute, uint8_t length,
			  std::vector<uint8_t> payload)
{
  return new TLVFrame (tag, attribute, length, payload);
}
TLVFrame*
TLVEEngine::create_frame (uint8_t tag, uint8_t attribute, uint8_t length)
{
  return new TLVFrame (tag, attribute, length);
}

TLVFrame*
TLVEEngine::create_frame ()
{
  return new TLVFrame ();
}

TLVEEngine::~TLVEEngine ()
{

}

