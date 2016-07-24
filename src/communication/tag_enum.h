#ifndef SRC_COMMUNICATION_TAG_ENUM_H_
#define SRC_COMMUNICATION_TAG_ENUM_H_

/**
 * @file
 * @class TagEnum
 * @brief Enums for Tags described in TLVE4 Protocol
 * @details
 * <ul>
 * 	<li>#NO_TAG_DEFINED			( = 0x00)</li>
 * 	<li>#GET_PROTOCOL_VERSION 		( = 0x01)</li>
 * 	<li>#GET_BOAT_ID 			( = 0x02)</li>
 * 	<li>#SET_CONTROL_MODE			( = 0x03)</li>
 * 	<li>#PM_SET	 			( = 0x04)</li>
 * 	<li>#ERROR	 			( = 0x08)</li>
 * 	<li>#GET_BOAT_DESCRIPTION		( = 0x09)</li>
 * 	<li>#GET_CONTROL_MODE			( = 0x0A)</li>
 * 	<li>#SET_VALUE 				( = 0x11)</li>
 * 	<li>#REQUEST_VALUE 			( = 0x12)</li>
 * 	<li>#REQUEST_VALUE_W_TIMESTAMP		( = 0x13)</li>
 * 	<li>#VALUE_PROTOCOL_VERSION		( = 0x81)</li>
 * 	<li>#VALUE_BOAT_ID 			( = 0x82)</li>
 * 	<li>#VALUE_BOAT_DESCRIPTION		( = 0x89)</li>
 * 	<li>#VALUE_CONTROL_MODE			( = 0x8A)</li>
 * 	<li>#ACKNOWLEDGE_STREAM			( = 0x91)</li>
 * 	<li>#VALUE_RESPONSE 			( = 0x92)</li>
 * 	<li>#VALUE_RESPONSE_W_TIMESTAMP		( = 0x93)</li>
 * 	<li>#NUM_TAGS 				( = 18)</li>
 * </ul>
 * @author Rene Kremer
 * @version 0.2
 */
enum class TagEnum
{
  /**
   * TagEnum if there is no Tag defined in that Frame
   * (frame fault or frame in construction)
   */
  NO_TAG_DEFINED = 0x00,
  // Priority Commands
  /**
   * <strong>Priority Command:</strong>
   * <br/>Request to send the protocol version. Responded via VALUE_PROTOCOL_VERSION
   */
  GET_PROTOCOL_VERSION = 0x01,
  /**
   * <strong>Priority Command:</strong>
   * <br/>Request to send the boats ID. Responded via VALUE_BOAT_ID
   */
  GET_BOAT_ID = 0x02,
  /**
   * <strong>Priority Command:</strong>
   * <br/>Sets the control mode of this boat. <br/>Payload contains:
   * MODE (1 BYTE):
   * 	<ul>
   * 		<li>0X00=PRIORITY MODE</li>
   * 		<li>0X01=NORMAL MODE</li>
   * 		<li>0X0F=FAIL SAFE</li>
   * 	</ul>
   */
  SET_CONTROL_MODE = 0x03,
  /**
   * <strong>Priority Command:</strong>
   * <br/>Sets a ServoMotor.
   * <br/>Payload contains:
   * <ul>
   * 	<li>DATA STRUCTURE IDENTIFIER (010B)</li>
   * 	<li>ATTRIBUTE OF SERVO UINT8 (1 BYTE)</li>
   * 	<li>ANGLE RUDDER INT16 (2 BYTE)</li>
   * </ul>
   */
  PM_SET = 0x04,
  /**
   * <strong>Priority Command:</strong> To receive and send a error message.
   * <br/>Payload contains:
   * <ul>
   * 	<li>ERROR CODE UINT8 (1 BYTE)</li>
   * 	<li>ERROR MESSAGE STRING (N BYTE)</li>
   * </ul>
   */
  ERROR = 0x08,
  /**
   * <strong>Priority Command:</strong>
   * <br/>Request to send the boat description. Responded via VALUE_BOAT_DESCRIPTION
   */
  GET_BOAT_DESCRIPTION = 0x09,
  /**
   * <strong>Priority Command:</strong>
   * <br/> Request to send the control mode. Responded via VALUE_CONTROL_MODE
   */
  GET_CONTROL_MODE = 0x0A,
  // Normal-Mode Commands
  /**
   * Sets a value. Payload depends on component
   */
  SET_VALUE = 0x11,
  /**
   * Request a value of a communication device. Responded via VALUE_RESPONSE
   */
  REQUEST_VALUE = 0x12,
  /**
   * Request a value with a timestamp. Responded via VALUE_RESPONSE_W_TIMESTAMP
   */
  REQUEST_VALUE_W_TIMESTAMP = 0x13,
  // Value Commands
  /**
   * Response to GET_PROTOCOL_VERSION. <br/>Payload is:
   * <ul>
   * 	<li>MAJOR VERSION INT8 (1 BYTE)</li>
   * 	<li>MINOR VERSION INT8 (2 BYTE)</li>
   * </ul>
   * <br/>Example: 0X04 0X00 0X00 = V4.0
   */
  VALUE_PROTOCOL_VERSION = 0x81,
  /**
   * Response to GET_BOAT_ID. Payload contains: BOAT ID UINT8 (1 BYTE)
   */
  VALUE_BOAT_ID = 0x82,
  /**
   * Response to GET_BOAT_DESCRIPTION. <br/>Payload contains:
   * <ul>
   * 	<li>COMMUNICATION-NUMBER UINT8 (1 BYTE)</li>
   * 	<li>CLASS OF COMPONENT UINT8 (1 BYTE)</li>
   * 	<li>ATTRIBUTE OF COMPONENT UINT8 (1 BYTE)</li>
   * 	<li>COMPONENT-NO. UINT8 (1 BYTE)</li>
   * </ul>
   * <br/>(repeat for all N system components)
   */
  VALUE_BOAT_DESCRIPTION = 0x89,
  /**
   * Response to GET_CONTROL_MODE.
   * <br/>Payload contains MODE (1 BYTE)
   * <ul>
   * 	 <li>0X00=PRIORITY MODE</li>
   * 	 <li>0X01=NORMAL MODE</li>
   * 	 <li> 0X0F=FAIL SAFE</li>
   * </ul>
   */
  VALUE_CONTROL_MODE = 0x8A,
  /**
   * Response for Streams. Response to Set_VALUE Command of a Stream in StreamGenerator
   * <br/>Payload contains:
   * <ul>
   * 	<li>DATA TYPE AND COMM.- NO. UINT8 (1 BYTE)</li>
   * 	<li>COMM.-NO. OF SENSOR INT16 (2 BYTE)</li>
   * 	<li>PERIOD INT16 (2 BYTE)</li>
   * </ul>
   */
  ACKNOWLEDGE_STREAM = 0x91,
  /**
   * Response to REQUEST_VALUE. Payload depends on communication device
   */
  VALUE_RESPONSE = 0x92,
  /**
   * Response to REQUEST_VALUE_W_TIMESTAMP.
   * <br/>Payload depends on communication device
   * but has at least ATTRIBUTE (1 Byte) + 4 Byte TIMESTAMP in ms
   */
  VALUE_RESPONSE_W_TIMESTAMP = 0x93,
  /**
   * Number of Tags. Upper Bound if there is a need to iterate TagEnums
   */
  NUM_TAGS = 18
};

#endif /* COMMUNICATION_TAG_ENUM_H_ */
