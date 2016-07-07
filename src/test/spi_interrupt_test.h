#ifdef _TEST
#ifndef TEST_SPI_INTERRUPT_TEST_H_
#define TEST_SPI_INTERRUPT_TEST_H_

#include <iostream>
#include "../interfaces/spi_thread_param.h"
#include <stdint.h>
#include "asserter.h"
#include <vector>

/**
 * @file
 * @class SPIInterruptTest
 * @brief Class for testing purposes of the interrupt fired by the master select
 * pin of the SPIMasterSelect Interface.
 * Implements some functions to assert that the interrupt is working correctly.
 * @author Rene Kremer
 * @version 0.2
 */
class SPIInterruptTest{
  /**
   * @private
   */
private:
  /**
   * Short Test for causing an interrupt with multiple SPI Devices. As the SerialLink
   * shall check for interrupts, so that frames can be received really quick if the
   * slave wants to send something, it is essential that not all SPI Devices check for
   * interrupts and someone can distinguish between SPI Devices which check on
   * interrupts and which doesn't
   * @returns true on success, otherwise false
   */
  bool master_select_test();
  /**
   * @public
   */
public:
  /**
   * Constructor
   */
  SPIInterruptTest();
  /**
   * Tests all cases and returns a boolean if they passed or not
   * @return true if all cases passed, otherwise false
   */
  bool test_cases();
  /**
   * Destructor
   */
  ~SPIInterruptTest();
};



#endif /* TEST_SPI_INTERRUPT_TEST_H_ */
#endif
