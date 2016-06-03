#include "tlve_protocol.h"
#include "tlv_frame.h"

#include <vector>

TLVEProtocol::TLVEProtocol()
{

}

TLVFrame TLVEProtocol::get_boat_description()
{
  uint8_t tag = 0, attribute = 0, length = 0;
  std::vector<uint8_t> payload;

	return TLVFrame(tag, attribute, length, payload);
}

TLVFrame* TLVEProtocol::create_frame(uint8_t tag, uint8_t attribute, uint8_t length, std::vector<uint8_t> payload)
{
	return new TLVFrame(tag, attribute, length, payload);
}

TLVEProtocol::~TLVEProtocol(){}
