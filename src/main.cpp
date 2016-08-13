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
  tests.push_back(passed);
  passed = gcd_test.test_cases ();
  if (passed == true)
    {
      std::cout << "GCD passed!" << std::endl;
    }
  else
    {
      std::cout << "Test failed. GCD did not pass!" << std::endl;
    }
  tests.push_back(passed);
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
  tests.push_back(passed);
  passed = timer_test.test_cases ();
  if (passed == true)
    {
      std::cout << "Test passed. Timer passed!" << std::endl;
    }
  else
    {
      std::cout << "Test failed. Timer did not pass!" << std::endl;
    }
  tests.push_back(passed);
  passed = true;
  for(uint8_t i = 0; i < tests.size();i++){
      if(tests.at(i) != true){
	  passed = false;
      }
  }
  if(passed == true){
      std::cout << "All Tests passed!" << std::endl;
  }else{
      std::cout << "Some Tests failed! Read log for more information" << std::endl;
  }
}
/**
 * Test function for gps latency
 */
void
gps_csv ()
{
  Loader* loader = new Loader ();
  std::shared_ptr<DeviceManager> dmanager = loader->get_device_manager ();
  timeval begin, end;
  GPS* gps = dynamic_cast<GPS*> (&(*(dmanager->get_device (
      ComponentDescriptorEnum::GPS_POSITION))));
  std::vector<int8_t> data;
  std::cout << "Latitude;Longitude;Speed;Timestamp;Needed Time;" << std::endl;
  for (int32_t i = 0; i < 1000; i++)
    {
      if (gps != NULL)
	{
	  gettimeofday (&begin, NULL);
	  data = gps->read_data ();
	  if (data.size () == 0)
	    {
	      int8_t* test_latitude = new int8_t[4];
	      test_latitude[0] = data[0];
	      test_latitude[1] = data[1];
	      test_latitude[2] = data[2];
	      test_latitude[3] = data[3];
	      int8_t* test_longitude = new int8_t[4];
	      test_longitude[0] = data[4];
	      test_longitude[1] = data[5];
	      test_longitude[2] = data[6];
	      test_longitude[3] = data[7];
	      int8_t* test_speed = new int8_t[4];
	      test_speed[0] = data[8];
	      test_speed[1] = data[9];
	      test_speed[2] = data[10];
	      test_speed[3] = data[11];
	      int8_t* test_timestamp = new int8_t[4];
	      test_timestamp[0] = data[12];
	      test_timestamp[1] = data[13];
	      test_timestamp[2] = data[14];
	      test_timestamp[3] = data[15];
	      int32_t latitude = IntConverter::int8_to_int32 (test_latitude);
	      int32_t longitude = IntConverter::int8_to_int32 (test_longitude);
	      int32_t speed = IntConverter::int8_to_int32 (test_speed);
	      int32_t timestamp = IntConverter::int8_to_int32 (test_timestamp);
	      delete[] test_latitude;
	      delete[] test_longitude;
	      delete[] test_speed;
	      delete[] test_timestamp;
	      std::cout << latitude << ";" << longitude << ";" << speed << ";"
		  << timestamp << ";";
	    }
	  gettimeofday (&end, NULL);
	  std::cout
	      << (end.tv_sec - begin.tv_sec) * 1000
		  + (end.tv_usec - begin.tv_usec) / 1000 << ";" << std::endl;
	}
    }
}
#endif
int
main (void)
{
#ifdef _TEST
  tests ();
//  gps_csv ();
    // Tests which will not execute and check itself
//  FrameInterpreterTest interpreter_test;
//  interpreter_test.run_test ();
//  StreamGeneratorTest generator_test;
//  generator_test.test_cases ();
//  SerialTest serial_test;
//  serial_test.test_cases ();
#endif
#ifdef _RELEASE
  Loader* loader = new Loader ();
//  std::vector<uint8_t> payload;
//  std::shared_ptr<Device> device;
//  uint8_t attribute, comm_number;
//  Frame* frame;

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
	  // GET ACCELEROMETER
//	  std::cout << "\n------------------------" << "\nGet Accelerometer"
//	      << "\n------------------------" << std::endl;
//	  device = loader->get_device_manager ()->get_device (
//	      ComponentDescriptorEnum::ACCELEROMETER);
//	  comm_number =
//	      loader->get_protocol_engine ()->get_communication_number (
//		  device->get_component_descriptor ());
//	  attribute = loader->get_protocol_engine ()->tlve4_attribute (
//	      DataStructureIdentifier::UINT8, comm_number);
//	  frame = loader->get_protocol_engine ()->create_frame (
//	      TagEnum::REQUEST_VALUE_W_TIMESTAMP, attribute, 1);
//	  loader->get_protocol_engine ()->interpret_frame (frame);
	}
    }
  pthread_mutex_unlock (&params.count_mutex);
  pthread_join (interrupt_thread_a, NULL);
#endif
#ifdef _DEBUG
  Loader* loader = new Loader ();
  std::shared_ptr<Device> device = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::ACCELEROMETER);
  while(true)
    {
      device->read_data ();
      sleep(1);
    }
#endif
  return 0;
}
