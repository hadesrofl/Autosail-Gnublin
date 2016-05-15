#include "tlv_frame.h"

TLVFrame::TLVFrame (unsigned char tag, unsigned char attribute,
		    unsigned char length, std::vector<unsigned char> payload,
		    unsigned char sync)
{
  m_tag = tag;
  m_attribute = attribute;
  m_length = length;
  m_payload = payload;
  m_sync = sync;
}

TLVFrame::~TLVFrame ()
{
  m_payload.clear();
}
