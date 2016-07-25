#ifndef COMMUNICATION_T_L_V_FRAME_H
#define COMMUNICATION_T_L_V_FRAME_H

#include <vector>
#include <stdint.h>
#include "tag_enum.h"

/**
 * @file
 * @class Frame
 * @ingroup Communication
 * @brief Class for a abstract Frame send as packet via the specific ProtocolEngine
 * @author Rene Kremer
 * @version 0.2
 */
class Frame
{
  /**
   * @private
   */
private:
  /**
   * @protected
   */
protected:
  /**
   * Byte containing the tag
   */
  TagEnum m_tag;
  /**
   * Byte containing the attribute
   */

  uint8_t m_attribute;
  /**
   * Byte containing the length of the payload of the frame
   */

  uint8_t m_length;
  /**
   * Byte Vector of containing all bytes of the payload. Size is specified by m_length
   */

  std::vector<uint8_t> m_payload;
  /**
   * @public
   */
public:

  Frame ()
  {
    m_tag = TagEnum::NO_TAG_DEFINED;
    m_attribute = 0;
    m_length = 0;
  }
  /**
   * Gets the tag field
   * @return tag byte of the frame
   */
  inline TagEnum
  get_tag () const
  {
    return m_tag;
  }
  /**
   * Sets a new tag byte to the Frame
   * @param tag is the new tag of the Frame
   */
  inline void
  set_tag (TagEnum tag)
  {
    m_tag = tag;
  }
  /**
   * Gets the attribute field
   * @return attribute byte of the frame
   */
  inline uint8_t
  get_attribute () const
  {
    return m_attribute;
  }
  /**
   * Sets a new attribute byte to the Frame
   * @param attribute is the new attribute of the Frame
   */
  inline void
  set_attribute (uint8_t attribute)
  {
    m_attribute = attribute;
  }
  /**
   * Gets the length of the payload
   * @return byte for the length of the payload
   */
  inline uint8_t
  get_length () const
  {
    return m_length;
  }
  /**
   * Sets a new length byte to the Frame
   * @param length is the new length byte of the Frame
   */
  inline void
  set_length (uint8_t length)
  {
    m_length = length;
  }
  /**
   * Gets the bytes of the payload
   * @return a vector of the bytes of the payload
   */
  inline std::vector<uint8_t>
  get_payload () const
  {
    return m_payload;
  }
  /**
   * Clears the old payload and sets a new one
   * @param payload is the new payload of this Frame
   */
  inline void
  set_payload (std::vector<uint8_t> payload)
  {
    m_payload.clear ();
    for (uint32_t i = 0; i < payload.size (); i++)
      {
	m_payload.push_back (payload.at (i));
      }
  }
  /**
   * Adds a new element to the payload of this Frame
   * @param element is the new element to add to the payload
   */
  inline void
  add_to_payload (uint8_t element)
  {
    m_payload.push_back (element);
  }
  /**
   * Virtual Function: Validates this Frame and returns either true or false
   * @return true if it is ok, otherwise false
   */
  virtual bool
  validate_frame () = 0;
  /**
   * Destructor
   */
  virtual ~Frame ()
  {
    m_payload.clear ();
  }

};
#endif
