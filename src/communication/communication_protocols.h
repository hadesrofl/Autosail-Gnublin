#ifndef COMMUNICATION_PROTOCOLS_H_
#define COMMUNICATION_PROTOCOLS_H_

/**
 * @file
 * @enum mapper::CommunicationProtocol
 * @ingroup Enums
 * @brief Enum class to switch at start of the firmware to the specified protocol
 * mentioned in the conf file
 *
 * @author Rene Kremer
 * @version 0.2
 */
enum class CommunicationProtocol
{
  /**
   * The given protocol isn't supported by this firmware
   */
  UNSUPPORTED_PROTOCOL = 0x00,
  /**
   * TLVE4 Protocol Version
   */
  TLVE4 = 0x01,
  /**
   * TLVE5 Protocol Version
   */
  TLVE5 = 0x02,
  /**
   * JSON4 Protocol Version
   */
  JSON4 = 0x03,
  /**
   * JSON5 Protocol Version
   */
  JSON5 = 0x04
};

#endif /* COMMUNICATION_PROTOCOLS_H_ */
