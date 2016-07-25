#ifndef UTILS_INT_CONVERTER_H_
#define UTILS_INT_CONVERTER_H_

#include <stdint.h>

/**
 * @file
 * @class IntConverter
 * @ingroup Utils
 * @brief Class to convert different integer values.
 * @author Rene Kremer
 * @version 0.2
 */
class IntConverter
{
public:
  /**
   * Converts multiple int8_t into one int32_t (msb -> lsb)
   * @param input is a pointer containing multiple int8_t (msb -> lsb)
   * @return one int32_t out of the multiple int8_t
   */
  static int32_t
  int8_to_int32 (int8_t* input)
  {
    uint32_t tmp32 = (uint8_t) input[0] << 24 | (uint8_t) input[1] << 16
	| (uint8_t) input[2] << 8 | (uint8_t) input[3];
    int32_t output = (int32_t) tmp32;
    return output;
  }
  /**
   * Converts multiple uint8_t into one uint32_t (msb -> lsb)
   * @param input is a pointer containing multiple uint8_t (msb -> lsb)
   * @return one uint32_t out of the multiple uint8_t
   */
  static uint32_t
  uint8_to_uint32 (uint8_t* input)
  {
    uint32_t output = input[0] << 24 | input[1] << 16 | input[2] << 8
	| input[3];
    return output;
  }
  /**
   * Converts one int32_t into multiple int8_t (msb -> lsb)
   * @param input is one int32_t (msb -> lsb)
   * @return an array of int8_t  out of one int32_t
   */
  static int8_t*
  int32_to_int8 (int32_t input)
  {
    uint8_t* tmp = new uint8_t[4];
    int8_t* output = new int8_t[4];
    tmp[0] = input >> 24;
    output[0] = tmp[0] <= 127 ? tmp[0] : tmp[0] - 256;
    tmp[1] = input >> 16;
    output[1] = tmp[1] <= 127 ? tmp[1] : tmp[1] - 256;
    tmp[2] = input >> 8;
    output[2] = tmp[2] <= 127 ? tmp[2] : tmp[2] - 256;
    tmp[3] = input & 0xFF;
    output[3] = tmp[3] <= 127 ? tmp[3] : tmp[3] - 256;
    return output;
  }
  /**
   * Converts one int16_t into multiple int8_t (msb -> lsb)
   * @param input is one int16_t (msb -> lsb)
   * @return an array of int8_t  out of one int32_t
   */
  static int8_t*
  int16_to_int8 (int16_t input)
  {
    uint8_t* tmp = new uint8_t[2];
    int8_t* output = new int8_t[2];
    tmp[0] = input >> 8;
    output[0] = tmp[2] <= 127 ? tmp[2] : tmp[2] - 256;
    tmp[1] = input & 0xFF;
    output[1] = tmp[3] <= 127 ? tmp[3] : tmp[3] - 256;
    return output;
  }
  /**
   * Converts one uint32_t into multiple uint8_t (msb -> lsb)
   * @param input is one uint32_t (msb -> lsb)
   * @return an array of uint8_t  out of one uint32_t
   */
  static uint8_t*
  uint32_to_uint8 (uint32_t input)
  {
    uint8_t* output = new uint8_t[4];
    output[0] = input >> 24;
    output[1] = input >> 16;
    output[2] = input >> 8;
    output[3] = input & 0xFF;
    return output;
  }
  /**
   * Converts one uint16_t into multiple uint8_t (msb -> lsb)
   * @param input is one uint16_t (msb -> lsb)
   * @return an array of uint8_t  out of one uint32_t
   */
  static uint8_t*
  uint16_to_uint8 (uint16_t input)
  {
    uint8_t* output = new uint8_t[2];
    output[0] = input >> 8;
    output[1] = input & 0xFF;
    return output;
  }
  /**
   * Converts multiple uint8_t (msb -> lsb) into one uint16_t
   * @param input is a pointer containing multiple uint8_t (msb -> lsb)
   * @return an uint16_t
   */
  static uint16_t
  uint8_to_uint16 (uint8_t* input)
  {
    uint16_t output = input[0] << 8 | input[1];
    return output;
  }
  /**
   * Converts multiple uint8_t (msb -> lsb) into one uint16_t
   * @param input is a pointer containing multiple uint8_t (msb -> lsb)
   * @return an uint16_t
   */
  static int16_t
  int8_to_int16 (int8_t* input)
  {
    uint16_t tmp = (uint8_t) input[0] << 8 | (uint8_t) input[1];
    int16_t output = (int16_t) tmp;
    return output;
  }
};

#endif /* UTILS_INT_CONVERTER_H_ */
