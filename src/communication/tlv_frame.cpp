#include "tlv_frame.h"

TLVFrame::TLVFrame ()
{
  m_tag = 0;
  m_attribute = 0;
  m_length = 0;
}
TLVFrame::TLVFrame (uint8_t tag, uint8_t attribute, uint8_t length,
		    std::vector<uint8_t> payload)
{

  m_tag = tag;
  m_attribute = attribute;
  m_length = length;
  for (uint32_t i = 0; i < payload.size (); i++)
    {
      m_payload.push_back (payload.at (i));
    }
}
TLVFrame::TLVFrame (uint8_t tag, uint8_t attribute, uint8_t length)
{
  m_tag = tag;
  m_attribute = attribute;
  m_length = length;
}
bool
TLVFrame::validate_frame ()
{
  return true;
}
TLVFrame::~TLVFrame ()
{

}

