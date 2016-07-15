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
  SPIMasterSelect* spi_ptr;
};

#endif /* INTERFACES_SPI_THREAD_PARAMS_H_ */
