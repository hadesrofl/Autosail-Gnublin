#include "tlve_protocol.h"

#include <vector>

TLVEProtocol::TLVEProtocol()
{

}

TLVFrame TLVEProtocol::get_boat_description()
{
	return TLVFrame();
}

TLVFrame TLVEProtocol::create_frame(unsigned char tag, unsigned char attribute, unsigned char length, std::vector<unsigned char> payload, unsigned char sync)
{
	return TLVFrame();
}

TLVEProtocol::~TLVEProtocol(){}
