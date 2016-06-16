#ifndef COMMUNICATION_TLVE_ENGINE_H_
#define COMMUNICATION_TLVE_ENGINE_H_

#include "protocol_engine.h"
#include "tlv_frame.h"

class TLVEEngine : virtual public ProtocolEngine
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
   * @public
   */
public:
  /**
   * Constructor
   */
  TLVEEngine ();
  /**
   * Creates a Frame containing the boat description
   * @return the Frame holding the boat description data
   */
  TLVFrame*
  send_boat_description ();
  /**
   * Creates a TLVFrame and returns a pointer to it
   * @param tag is the value of the tag field
   * @param attribute is the value of the attribute field
   * @param length is the amount of bytes of the payload field
   * @param payload is a Byte Vector containing the data of the payload
   * @return a TLVFrame packed with the data
   */
  TLVFrame*
  create_frame (uint8_t tag, uint8_t attribute, uint8_t length,
		std::vector<uint8_t> payload);
  /**
   * Creates a TLVFrame and returns a pointer to it
   * @param tag is the value of the tag field
   * @param attribute is the value of the attribute field
   * @param length is the amount of bytes of the payload field
   * @return a TLVFrame packed with the data
   */
  TLVFrame*
  create_frame (uint8_t tag, uint8_t attribute, uint8_t length);
  /**
   * Creates an empty TLVFrame
   * @return an empty TLVFrame
   */
  TLVFrame*
  create_frame ();
  /**
   * Calls the TLVInterpreter and interprets the frame. The TLVInterpreter
   * calls the function described by the command in the Frame.
   * @param frame is a pointer to the frame which shall be interpreted
   */
  void
  interpret_frame (Frame* frame);
  /**
   * Destructor
   */
  ~TLVEEngine ();
};

#endif /* COMMUNICATION_TLVE_ENGINE_H_ */
