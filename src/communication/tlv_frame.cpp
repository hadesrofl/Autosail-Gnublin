#include "tlv_frame.h"

TLVFrame::TLVFrame (uint8_t tag, uint8_t attribute,
		    uint8_t length, std::vector<uint8_t> payload)
{
  m_tag = tag;
  m_attribute = attribute;
  m_length = length;
  m_payload = payload;
}

TLVFrame::~TLVFrame ()
{
  m_payload.clear();
}
