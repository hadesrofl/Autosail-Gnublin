#include "../gnublin_wo_smtp.h"
#include "devices/device_manager.h"
#include "bridge/loader.h"

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
  bool passed = gcd_test.test_cases ();
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
  DeviceManager* dmanager = loader->get_device_manager ();
  timeval begin, end;
  GPS* gps = dynamic_cast<GPS*> (dmanager->get_device (
      ComponentDescriptorEnum::GPS_POSITION));
  gps_data_t* gps_data = new gps_data_t;
  std::cout << "Latitude;Longitude;Speed;Timestamp;Needed Time;" << std::endl;
  for (int32_t i = 0; i < 1000; i++)
    {
      if (gps != NULL)
	{
	  gettimeofday (&begin, NULL);
	  if (gps->read_data (gps_data) > 0)
	    {
	      std::cout << gps_data->latitude << ";" << gps_data->longitude
		  << ";" << gps_data->speed << ";" << gps_data->timestamp
		  << ";";
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
  //tests ();
  gps_csv ();
#endif
#ifndef _TEST
  Loader* loader = new Loader ();
  DeviceManager* dmanager = loader->get_device_manager ();
  /*Device* device_a = dmanager->get_device (ComponentDescriptorEnum::GYROSCOPE);
   Device* device_b = dmanager->get_device (
   ComponentDescriptorEnum::ACCELEROMETER);
   Device* device_c = dmanager->get_device (ComponentDescriptorEnum::COMPASS);
   uint8_t *acc_data, *gyro_data, *compass_data;
   */
  timeval begin, end;
  GPS* gps = dynamic_cast<GPS*> (dmanager->get_device (
	  ComponentDescriptorEnum::GPS_POSITION));
  gps_data_t* gps_data = new gps_data_t;
  bool active = true;
  while (active)
    {
      /* if (device_a != NULL)
       {
       gyro_data = device_a->read_data ();
       sleep (1);
       }
       else
       {
       active = false;
       }
       if (device_b != NULL)
       {
       acc_data = device_b->read_data ();
       sleep (1);
       }
       else
       {
       active = false;
       }

       if (device_c != NULL)
       {
       compass_data = device_c->read_data ();
       sleep (1);
       }
       else
       {
       active = false;
       }
       */
      if(gps != NULL)
	{
	  gettimeofday(&begin, NULL);
	  if(gps->read_data (gps_data) > 0)
	    {
	      std::cout << "Latitude: " << gps_data->latitude << std::endl;
	      std::cout << "Longitude: " << gps_data->longitude << std::endl;
	      std::cout << "Speed: " << gps_data->speed << std::endl;
	      std::cout << "Timestamp: " << gps_data->timestamp.tv_sec << std::endl;
	    }

	  gettimeofday(&end, NULL);
	  std::cout << "Needed Time to get Data in ms " <<
	  (end.tv_sec - begin.tv_sec)*1000 + (end.tv_usec - begin.tv_usec)/1000 <<
	  std::endl;
	}
      //sleep(6);
    }
#endif
  return 0;
}
