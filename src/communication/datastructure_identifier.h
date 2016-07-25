#ifndef COMMUNICATION_DATA_STRUCTURE_IDENTIFIER_H_
#define COMMUNICATION_DATA_STRUCTURE_IDENTIFIER_H_

/**
 * @file
 * @enum mapper::DataStructureIdentifier
 * @ingroup Enums
 * @brief Enums for the DataStructureIdentifier described in TLVE4 Protocol
 * @author Rene Kremer
 * @version 0.2
 */
enum class DataStructureIdentifier
{
  /**
   * unsigned 8 bit integer
   */
  UINT8 = 0x0,
  /**
   * signed 8 bit integer
   */
  INT8 = 0x1,
  /**
   * signed 16 bit integer
   */
  INT16 = 0x2,
  /**
   * signed 32 bit integer
   */
  INT32 = 0x3,
  /**
   * ASCII coded String
   */
  STRING = 0x4,
  /**
   * Number of DataStructureIdentifiers for iteration purposes
   */
  NUM_IDENTIFIERS
};

#endif /* COMMUNICATION_DATA_STRUCTURE_IDENTIFIER_H_ */
