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

#ifndef DEVICES_STREAM_GENERATOR_THREAD_PARAMS_H_
#define DEVICES_STREAM_GENERATOR_THREAD_PARAMS_H_

#include "stream_generator.h"
#include <memory>

/**
 * @file
 * @class stream_generator_thread_param_t
 * @ingroup Devices
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
