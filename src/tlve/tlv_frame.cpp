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

inline unsigned char
TLVFrame::get_tag () const
{
  return m_tag;
}

inline unsigned char
TLVFrame::get_attribute () const
{
  return m_attribute;
}

inline unsigned char
TLVFrame::get_length () const
{
  return m_length;
}

inline std::vector<unsigned char>
TLVFrame::get_payload () const
{
  return m_payload;
}

inline unsigned char
TLVFrame::get_sync () const
{
  return m_sync;
}

TLVFrame::~TLVFrame ()
{
  m_payload.clear();
}
