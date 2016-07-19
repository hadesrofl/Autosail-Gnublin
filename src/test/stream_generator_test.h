#ifdef _TEST
#ifndef TEST_STREAM_GENERATOR_TEST_H_
#define TEST_STREAM_GENERATOR_TEST_H_

#include <iostream>
#include <vector>
#include "asserter.h"
#include "../bridge/loader.h"
#include "../devices/device_manager.h"

class StreamGeneratorTest
{
private:
  bool
  stream_test();
public:
  StreamGeneratorTest ();
  bool
  test_cases();
  ~StreamGeneratorTest ();
};

#endif /* TEST_STREAM_GENERATOR_TEST_H_ */
#endif
