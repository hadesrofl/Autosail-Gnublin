#ifndef INTERFACES_SPI_THREAD_PARAMS_H_
#define INTERFACES_SPI_THREAD_PARAMS_H_

#include "spi_master_select.h"

/**
 * @file
 * @class SPIThreadParam
 * @brief Class for a simple struct used in PThreads
 * for the SPIMasterSelect Interface.
 * @author Rene Kremer
 * @version 0.2
 */
struct SPIThreadParam
{
  SPIMasterSelect* spi_ptr;
};

#endif /* INTERFACES_SPI_THREAD_PARAMS_H_ */
