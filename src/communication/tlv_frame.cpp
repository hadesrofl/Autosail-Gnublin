#include "tlv_frame.h"
#include <iostream>

TLVFrame::TLVFrame ()
{
  m_tag = TagEnum::NO_TAG_DEFINED;
  m_attribute = 0;
  m_length = 0;
}
TLVFrame::TLVFrame (TagEnum tag, uint8_t attribute, uint8_t length,
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
TLVFrame::TLVFrame (TagEnum tag, uint8_t attribute, uint8_t length)
{
  m_tag = tag;
  m_attribute = attribute;
  m_length = length;
}
TLVFrame::TLVFrame (TagEnum tag, uint8_t length)
{
  m_tag = tag;
  m_attribute = 0;
  m_length = length;
}
bool
TLVFrame::validate_frame ()
//TODO: add functionality
{
  return true;
}
TLVFrame::~TLVFrame ()
{

}

