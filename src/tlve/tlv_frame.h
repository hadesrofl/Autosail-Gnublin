#ifndef TLVE_T_L_V_FRAME_H
#define TLVE_T_L_V_FRAME_H

#include <vector>

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
  unsigned char m_tag;
  /**
   * Byte containing the attribute
   */

  unsigned char m_attribute;
  /**
   * Byte containing the length of the payload of the frame
   */

  unsigned char m_length;
  /**
   * Byte Vector of containing all bytes of the payload. Size is specified by m_length
   */

  std::vector<unsigned char> m_payload;
  /**
   * Byte containing the sync
   */
  unsigned char m_sync;
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
   * @param sync byte of the sync field
   */
  TLVFrame (unsigned char tag, unsigned char attribute, unsigned char length,
	    std::vector<unsigned char> payload, unsigned char sync);
  /**
   * Gets the tag field
   * @return tag byte of the frame
   */
  inline unsigned char
  get_tag () const
  {
    return m_tag;
  }
  /**
   * Gets the attribute field
   * @return attribute byte of the frame
   */
  inline unsigned char
  get_attribute () const
  {
    return m_attribute;
  }
  /**
   * Gets the length of the payload
   * @return byte for the length of the payload
   */
  inline unsigned char
  get_length () const
  {
    return m_length;
  }
  /**
   * Gets the bytes of the payload
   * @return a vector of the bytes of the payload
   */
  inline std::vector<unsigned char>
  get_payload () const
  {
    return m_payload;
  }
  /**
   * Gets the sync field
   * @return byte of the sync of the frame
   */
  inline unsigned char
  get_sync () const
  {
    return m_sync;
  }
  /**
   * Destructor
   */
  ~TLVFrame ();

};
#endif
