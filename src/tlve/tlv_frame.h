#ifndef KLASSENDIAGRAMM_TLVE_T_L_V_FRAME_H
#define KLASSENDIAGRAMM_TLVE_T_L_V_FRAME_H

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
   */
  TLVFrame ();
  /**
   * Destructor
   */
  ~TLVFrame ();

};
#endif
