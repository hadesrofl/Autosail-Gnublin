#include "tlve_protocol.h"
#include "tlv_frame.h"

#include <vector>

TLVEProtocol::TLVEProtocol()
{

}

TLVFrame TLVEProtocol::get_boat_description()
{
  unsigned char tag = 0, attribute = 0, length = 0, sync = 0;
  std::vector<unsigned char> payload;

	return TLVFrame(tag, attribute, length, payload, sync);
}

TLVFrame* TLVEProtocol::create_frame(unsigned char tag, unsigned char attribute, unsigned char length, std::vector<unsigned char> payload, unsigned char sync)
{
	return new TLVFrame(tag, attribute, length, payload, sync);
}

TLVEProtocol::~TLVEProtocol(){}
