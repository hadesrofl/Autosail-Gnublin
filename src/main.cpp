#include "../gnublin_wo_smtp.h"
#include "devices/device_manager.h"
#include "bridge/loader.h"
#include "devices/stream_generator_thread_params.h"

#ifdef _TEST
#include "test/gcd_test.h"
#include "test/communication_table_test.h"
#include "test/echo_test.h"
#include "test/spi_interrupt_test.h"
#include "test/timer_test.h"

void
tests ()
{
  GCDTest gcd_test;
  CommunicationTableTest comm_table_test;
  TimerTest timer_test;
  bool passed;
  passed = gcd_test.test_cases ();
  if (passed == true)
    {
      std::cout << "GCD passed!" << std::endl;
    }
  else
    {
      std::cout << "Test failed. GCD did not pass!" << std::endl;
    }
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
  passed = timer_test.test_cases ();
  if (passed == true)
    {
      std::cout << "Test passed. Timer passed!" << std::endl;
    }
  else
    {
      std::cout << "Test failed. Timer did not pass!" << std::endl;
    }

  /*int8_t ret = spi_interrupt_test();
   if(ret == 1)
   {
   std::cout << "Test passed. SPI Interrupt works fine!" << std::endl;
   }
   */
  /*if (i2c_teensy_test () == 1)
   {
   std::cout << "Test passed. I2C works fine!" << std::endl;
   }
   else
   {
   std::cout << "Test failed. I2C has errors while sending/receiving!"
   << std::endl;
   }*/
}
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
//  tests ();
  //gps_csv ();
  Loader* loader = new Loader ();
  std::vector<uint8_t> payload;
  Frame* frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::GET_PROTOCOL_VERSION, 0, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::GET_BOAT_ID, 0,
							0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  payload.push_back (0x00);
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::SET_CONTROL_MODE, 0, 1, payload);
  loader->get_protocol_engine ()->interpret_frame (frame);
  payload.clear ();
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::GET_CONTROL_MODE, 0, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  payload.push_back (0x01);
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::SET_CONTROL_MODE, 0, 1, payload);
  loader->get_protocol_engine ()->interpret_frame (frame);
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::GET_CONTROL_MODE, 0, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
#endif
#ifndef _TEST
  Loader* loader = new Loader ();
  std::shared_ptr<DeviceManager> dmanager = loader->get_device_manager ();
  std::shared_ptr<Device> device_a = dmanager->get_device (ComponentDescriptorEnum::GYROSCOPE);
  std::shared_ptr<Device> device_b = dmanager->get_device (
      ComponentDescriptorEnum::ACCELEROMETER);
  std::shared_ptr<Device> device_c = dmanager->get_device (ComponentDescriptorEnum::COMPASS);
  int8_t *acc_data, *gyro_data, *compass_data, *gps_data;
  timeval begin, end;
  std::shared_ptr<Device> device_d = dmanager->get_device (
      ComponentDescriptorEnum::GPS_POSITION);
  GPS* gps = reinterpret_cast<GPS*> (&(*(device_d)));
  bool active = true;
  std::shared_ptr<StreamGenerator> generator = loader->get_stream_generator ();
  stream_generator_thread_param_t* generator_params =
  new stream_generator_thread_param_t;

  generator_params->generator_ptr = generator;

  pthread_t generator_thread = loader->start_generator ();
  generator->add_stream (device_a, 2500);
  generator->add_stream (device_b, 10000);
  generator->add_stream (device_c, 5000);
  generator->add_stream (device_d, 10000);
  while (active)
    {
//      if (device_a != NULL)
//	{
//	  gyro_data = device_a->read_data ();
//	  sleep (1);
//	}
//      else
//	{
//	  active = false;
//	}
//      if (device_b != NULL)
//	{
//	  acc_data = device_b->read_data ();
//	  sleep (1);
//	}
//      else
//	{
//	  active = false;
//	}
//      if (device_c != NULL)
//	{
//	  compass_data = device_c->read_data ();
//	  sleep (1);
//	}
//      else
//	{
//	  active = false;
//	}

//      if(gps != NULL)
//	{
//	  gettimeofday(&begin, NULL);
//	  gps_data = gps->read_data ();
//	  gettimeofday(&end, NULL);
//	  std::cout << "Needed Time to get Data in ms " <<
//	  (end.tv_sec - begin.tv_sec)*1000 + (end.tv_usec - begin.tv_usec)/1000 <<
//	  std::endl;
//	}
    }
  pthread_join (generator_thread, NULL);
#endif
  return 0;
}
