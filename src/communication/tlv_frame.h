#ifndef TLVE_T_L_V_FRAME_H
#define TLVE_T_L_V_FRAME_H

#include <vector>
#include <stdint.h>

#define SYNC_BIT 0x01

/**
 * @file
 * @class TLVFrame
 * @brief Class for a TLV Frame send as packet via the TLVE4-Protocol (see TLVEProtocol)
 * @author Rene Kremer
 * @version 0.2
 */
class TLVFrame
{
  /**
   * @private
   */
private:
  /**
   * Byte containing the tag
   */
  uint8_t m_tag;
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
  /**
   * Constructor
   * @param tag byte of the tag field
   * @param attribute byte of the attribute field
   * @param length byte of the length of the payload
   * @param payload vector of bytes for the payload of the frame
   */
  TLVFrame (uint8_t tag, uint8_t attribute, uint8_t length,
	    std::vector<uint8_t> payload);
  /**
   * Gets the tag field
   * @return tag byte of the frame
   */
  inline uint8_t
  get_tag () const
  {
    return m_tag;
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
   * Gets the length of the payload
   * @return byte for the length of the payload
   */
  inline uint8_t
  get_length () const
  {
    return m_length;
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
   * Destructor
   */
  ~TLVFrame ();

};
#endif
