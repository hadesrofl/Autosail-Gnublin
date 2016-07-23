#ifndef INTERFACES_SPI_THREAD_PARAMS_H_
#define INTERFACES_SPI_THREAD_PARAMS_H_

#include "spi_master_select.h"

/**
 * @file
 * @class spi_thread_param_t
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
   * Bool to determine if an interrupt occured
   */
  bool interrupted;
};

#endif /* INTERFACES_SPI_THREAD_PARAMS_H_ */
