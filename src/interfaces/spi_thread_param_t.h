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

#ifndef INTERFACES_SPI_THREAD_PARAMS_H_
#define INTERFACES_SPI_THREAD_PARAMS_H_

#include "spi_master_select.h"

/**
 * @file
 * @class spi_thread_param_t
 * @ingroup Interfaces
 * @brief Class for a simple struct used in PThreads
 * for the SPIMasterSelect Interface.
 * @author Rene Kremer
 * @version 0.2
 */
struct spi_thread_param_t
{
  /**
   * Pointer to the spi device
   */
  SPIMasterSelect* spi_ptr;
  /**
   * Mutex for counting incoming Frames
   */
  pthread_mutex_t count_mutex;
  /**
   * Condition to wake up main thread to
   */
  pthread_cond_t wakeup_cond;
  /**
   * Count of incoming Frames
   */
  uint32_t frame_count;
};

#endif /* INTERFACES_SPI_THREAD_PARAMS_H_ */
