#include "../gnublin_wo_smtp.h"
#include "devices/device_manager.h"
#include "devices/stream_generator_thread_params.h"
#include "loader/loader.h"
#include "interfaces/spi_thread_param_t.h"

#ifdef _TEST
#include "test/gcd_test.h"
#include "test/communication_table_test.h"
#include "test/i2c_test.h"
#include "test/timer_test.h"
#include "test/stream_generator_test.h"
#include "test/frame_interpreter_test.h"
#include "test/serial_test.h"
#include "test/acc_test.h"
#include "test/compass_test.h"
#include "test/gyroscope_test.h"
#include "test/windvane_test.h"
#include "test/gps_test.h"

/**
 * Calls test classes for unit testing
 */
void
tests ()
{
  std::vector<bool> tests;
  bool passed;
  GCDTest gcd_test;
  CommunicationTableTest comm_table_test;
  TimerTest timer_test;
  I2CTest echo_test;
  AccTest acc_test;
  acc_test.test_cases ();
  CompassTest comp_test;
  comp_test.test_cases ();
  GyroscopeTest gyro_test;
  gyro_test.test_cases ();
  WindVaneTest wv_test;
  wv_test.test_cases ();
  GPSTest gps_test;
  gps_test.test_cases ();
  passed = echo_test.test_cases ();
  if (passed == true)
    {
      std::cout << "I2C Echo Test passed!" << std::endl;
    }
  else
    {
      std::cout << "Test failed. I2C Echo Test did not pass!" << std::endl;
    }
  tests.push_back (passed);
  passed = gcd_test.test_cases ();
  if (passed == true)
    {
      std::cout << "GCD passed!" << std::endl;
    }
  else
    {
      std::cout << "Test failed. GCD did not pass!" << std::endl;
    }
  tests.push_back (passed);
  passed = comm_table_test.test_cases ();
  if (passed == true)
    {
      std::cout << "Test passed. Communication Table passed!" << std::endl;
    }
  else
    {
      std::cout << "Test failed. Communication Table did not pass!"
	  << std::endl;
    }
  tests.push_back (passed);
  passed = timer_test.test_cases ();
  if (passed == true)
    {
      std::cout << "Test passed. Timer passed!" << std::endl;
    }
  else
    {
      std::cout << "Test failed. Timer did not pass!" << std::endl;
    }
  tests.push_back (passed);
  passed = true;
  for (uint8_t i = 0; i < tests.size (); i++)
    {
      if (tests.at (i) != true)
	{
	  passed = false;
	}
    }
  if (passed == true)
    {
      std::cout << "All Tests passed!" << std::endl;
    }
  else
    {
      std::cout << "Some Tests failed! Read log for more information"
	  << std::endl;
    }
}
#endif
int
main (void)
{
#ifdef _TEST
  tests ();

//  //Tests which will not execute and check itself
//  FrameInterpreterTest interpreter_test;
//  interpreter_test.run_test ();
//  StreamGeneratorTest generator_test;
//  generator_test.test_cases ();
//  SerialTest serial_test;
//  serial_test.test_cases ();

//  //Evaluation Functions
//  AccTest acc_test;
//  acc_test.eval();
//  CompassTest comp_test;
//  comp_test.eval();
//  GyroscopeTest gyro_test;
//  gyro_test.eval();
//  WindVaneTest wv_test;
//  wv_test.eval ();
  //  interpreter_test.eval ();
  //  generator_test.eval();F
#endif
#ifdef _RELEASE
  Loader* loader = new Loader ();

  pthread_t interrupt_thread_a;
  struct spi_thread_param_t params;
  params.spi_ptr =
  dynamic_cast<SPIMasterSelect*> (loader->get_device_manager ()->get_device (
	  ComponentDescriptorEnum::SERIAL_LINK)->get_interface ());
  pthread_mutex_init(&params.count_mutex, NULL);
  pthread_cond_init (&params.wakeup_cond, NULL);
  pthread_create (&interrupt_thread_a, NULL,
      params.spi_ptr->pin_change_interrupt, &params);
  pthread_mutex_lock (&params.count_mutex);
  while (true)
    {
      pthread_cond_wait(&params.wakeup_cond, &params.count_mutex);
      while(params.frame_count > 0)
	{
	  params.frame_count--;
	  loader->get_protocol_engine ()->receive_frame ();
	}
    }
  pthread_mutex_unlock (&params.count_mutex);
  pthread_join (interrupt_thread_a, NULL);
#endif
  return 0;
}
