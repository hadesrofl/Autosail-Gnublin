#ifndef TLVE_T_L_V_E_PROTOCOL_H
#define TLVE_T_L_V_E_PROTOCOL_H

#include <vector>
#include "tlv_frame.h"

/**
 * @file
 * @class TLVEProtocol
 * @brief Class for the TLVE Protocol. Contains the communication numbers of the
 * components the boat has and packs TLVFrames (see TLVFrame) for the communication.
 * @author Rene Kremer
 * @version 0.2
 */
class TLVEProtocol
{
  /**
   * @private
   */
private:
  /**
   * Enums for the communication numbers of the components
   */
  enum class CommunicationNumber
  {
    GPS, HYGROMETER
  };
  /**
   * @public
   */
public:
  /**
   * Constructor
   */
  TLVEProtocol ();
  /**
   * Gets the description of the boat as specified in the TLVE4-Protocol and sends
   * the initial message and communication numbers
   * @return a TLVFrame packed with the data that shall be sent
   */
  TLVFrame
  get_boat_description ();
  /**
   * Creates a TLV Frame and returns it
   * @param tag is the value of the tag field
   * @param attribute is the value of the attribute field
   * @param length is the amount of bytes of the payload field
   * @param payload is a Byte Vector containing the data of the payload
   * @return a TLVFrame packed with the data
   */
  TLVFrame*
  create_frame (uint8_t tag, uint8_t attribute,
		uint8_t length, std::vector<uint8_t> payload);
  /**
   * Destructor
   */
  ~TLVEProtocol ();

};
#endif
