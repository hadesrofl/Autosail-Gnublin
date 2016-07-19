#ifndef DEVICES_STREAM_GENERATOR_THREAD_PARAMS_H_
#define DEVICES_STREAM_GENERATOR_THREAD_PARAMS_H_

#include "stream_generator.h"
#include <memory>

/**
 * @file
 * @class stream_generator_thread_param_t
 * @brief Class for a simple struct used in PThreads
 * for the StreamGenerator.
 * @author Rene Kremer
 * @version 0.2
 */
struct stream_generator_thread_param_t
{
  /**
   * Pointer of the StreamGenerator
   */
  std::shared_ptr<StreamGenerator> generator_ptr;
};



#endif /* DEVICES_STREAM_GENERATOR_THREAD_PARAMS_H_ */
