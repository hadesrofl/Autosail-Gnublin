/**
 * Copyright 2016 Rene Kremer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef COMMUNICATION_TLV_FRAME_H_
#define COMMUNICATION_TLV_FRAME_H_

#include "frame.h"

/**
 * Sync Byte at the end of each frame
 */
#define SYNC_BYTE 0x52
/**
 * @file
 * @class TLVFrame
 * @ingroup Communication
 * @brief Class for a TLVE4 Frame. Represents the Data Structure of a TLVE4 Frame.
 *
 * @author Rene Kremer
 * @version 0.2
 */
class TLVFrame : virtual public Frame
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
   * @param tag byte of the tag field
   * @param attribute byte of the attribute field
   * @param length byte of the length of the payload
   * @param payload vector of bytes for the payload of the frame
   */
  TLVFrame (TagEnum tag, uint8_t attribute, uint8_t length,
	    std::vector<uint8_t> payload);
  /**
   * Constructor
   * @param tag byte of the tag field
   * @param attribute byte of the attribute field
   * @param length byte of the length of the payload
   */
  TLVFrame (TagEnum tag, uint8_t attribute, uint8_t length);
  /**
   * Constructor
   * @param tag byte of the tag field
   * @param length byte of the length of the payload
   */
  TLVFrame (TagEnum tag, uint8_t length);
  /**
   * Constructor for an empty Frame
   */
  TLVFrame ();
  /**
   * Validates this TLVFrame
   * @return true if it is ok, otherwise false
   */
  bool
  validate_frame ();
  /**
   * Returns the Sync Byte
   * @return an uint8_t sync byte for the TLVFrame
   */
  inline uint8_t
  get_sync ()
  {
    return SYNC_BYTE;
  }
  /**
   * Destructor
   */
  ~TLVFrame ();
};

#endif /* COMMUNICATION_TLV_FRAME_H_ */
