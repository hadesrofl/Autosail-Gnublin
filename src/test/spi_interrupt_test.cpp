#ifdef _TEST
#include "spi_interrupt_test.h"

// public functions
SPIInterruptTest::SPIInterruptTest ()
{

}
bool
SPIInterruptTest::test_cases(){
  std::vector<bool> passed;
  Asserter asserter;
  passed.push_back(master_select_test());
  return asserter.check_asserts(passed, 1);
}
SPIInterruptTest::~SPIInterruptTest ()
{

}
// private functions
bool
SPIInterruptTest::master_select_test ()
{
  std::cout << "---------------------------------" << std::endl;
  std::cout << "Starting SPI Interrupt Test" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  SPIMasterSelect* spi_a = new SPIMasterSelect ((char*) "/dev/spidev0.0", 16000,
						11);
  SPIMasterSelect* spi_b = new SPIMasterSelect ((char*) "/dev/spidev0.0", 16000,
						0);
  pthread_t interrupt_thread_a;
  struct spi_thread_param_t params_a;
  params_a.spi_ptr = spi_a;
  uint8_t i = 0;
  while (i < 5)
    {
      pthread_create (&interrupt_thread_a, NULL, spi_a->pin_change_interrupt,
		      &params_a);
      pthread_join (interrupt_thread_a, NULL);
      i++;
      std::cout << "Interrupts: " << i << std::endl;
    }
  std::cout << "SPI A: " << std::endl;
  std::cout << " SPI Trigger Action: "
      << static_cast<char*> (spi_a->get_trigger_action ()) << std::endl;
  std::cout << " SPI Interrupted: " << spi_a->get_interrupt_state ()
      << std::endl;

  std::cout << "SPI B: " << std::endl;
  std::cout << " SPI Trigger Action: "
      << static_cast<char*> (spi_b->get_trigger_action ()) << std::endl;
  std::cout << " SPI Interrupted: " << spi_b->get_interrupt_state ()
      << std::endl;

  std::cout << "Delete SPI A" << std::endl;
  delete spi_a;
  std::cout << "Delete SPI B" << std::endl;
  delete spi_b;
  std::cout << "---------------------------------" << std::endl;
  return true;
}
#endif
