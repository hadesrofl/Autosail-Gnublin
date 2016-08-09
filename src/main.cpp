#include "../gnublin_wo_smtp.h"
#include "devices/device_manager.h"
#include "devices/stream_generator_thread_params.h"
#include "loader/loader.h"
#include "interfaces/spi_thread_param_t.h"

#ifdef _TEST
#include "test/gcd_test.h"
#include "test/communication_table_test.h"
#include "test/echo_test.h"
#include "test/spi_interrupt_test.h"
#include "test/timer_test.h"
#include "test/stream_generator_test.h"

/**
 * Prints time for frame_test
 */
void
print_time (timeval begin, timeval end)
{
  std::cout << (begin.tv_sec) + (begin.tv_usec) << ";"
      << (end.tv_sec) + (end.tv_usec) << ";"
      << (end.tv_sec - begin.tv_sec) * 1000
	  + (end.tv_usec - begin.tv_usec) / 1000 << ";" << std::endl;
}
/**
 * Calls test classes for unit testing
 */
void
tests ()
{
  bool passed;
  GCDTest gcd_test;
  CommunicationTableTest comm_table_test;
  TimerTest timer_test;
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
/**
 * Test function for Frame Interpreter.
 */
void
frame_test ()
{
  Loader* loader = new Loader ();
  std::vector<uint8_t> payload;
  uint8_t comm_number, attribute;
  std::shared_ptr<Device> device;
  std::shared_ptr<ComponentDescriptor> descriptor;
  Frame* frame;
  timeval start, end;
  std::cout << "Start Interpret Frame;End Interpret Frame;Difference;"
      << std::endl;
  // GET PROTOCOL VERSION
  std::cout << "\n------------------------" << "\nGet Protocol Version"
      << "\n------------------------" << std::endl;
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::GET_PROTOCOL_VERSION, 0, 0);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);

  // GET BOAT ID
  std::cout << "\n------------------------" << "\nGet Boat ID"
      << "\n------------------------" << std::endl;
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::GET_BOAT_ID, 0,
							0);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  // SET CONTROL MODE
  payload.push_back (0x00);
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::SET_CONTROL_MODE, 0, 1, payload);
  std::cout << "\n------------------------" << "\nSet Control Mode"
      << "\n------------------------" << std::endl;
  if (loader->get_autopilot () != NULL)
    {
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time (start, end);
    }
  payload.clear ();
  // GET CONTROL MODE
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::GET_CONTROL_MODE, 0, 0);
  if (loader->get_autopilot () != NULL)
    {
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time (start, end);
      payload.push_back (0x01);
      frame = loader->get_protocol_engine ()->create_frame (
	  TagEnum::SET_CONTROL_MODE, 0, 1, payload);
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time (start, end);
      frame = loader->get_protocol_engine ()->create_frame (
	  TagEnum::GET_CONTROL_MODE, 0, 0);
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time (start, end);
      frame = loader->get_protocol_engine ()->create_frame (
	  TagEnum::GET_CONTROL_MODE, 0, 0);
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time (start, end);
    }
  // SET RUDDER
  payload.push_back (0x0A);
  payload.push_back (0xFF);
  std::cout << "\n------------------------" << "\nRudder"
      << "\n------------------------" << std::endl;
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET, 0x44,
							3, payload);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);

  payload.clear ();
  payload.push_back (0xF5);
  payload.push_back (0x01);
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET, 0x44,
							3, payload);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  // GET RUDDER
  payload.clear ();
  std::cout << "\n------------------------" << "\nGet Rudder Position"
      << "\n------------------------" << std::endl;
  attribute =
      loader->get_protocol_engine ()->tlve4_attribute (
	  DataStructureIdentifier::UINT8,
	  loader->get_protocol_engine ()->get_communication_number (
	      loader->get_device_manager ()->get_device (
		  ComponentDescriptorEnum::SERVO_MOTOR_RUDDER)->get_component_descriptor ()));
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::REQUEST_VALUE_W_TIMESTAMP, attribute, 1);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  // SET MAIN SAIL
  payload.push_back (0x0A);
  payload.push_back (0xFF);
  std::cout << "\n------------------------" << "\nMain Sail"
      << "\n------------------------" << std::endl;
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET, 0x45,
							3, payload);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  payload.clear ();
  payload.push_back (0xF5);
  payload.push_back (0x01);
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET, 0x45,
							3, payload);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  // GET MAIN SAIL
  payload.clear ();
  std::cout << "\n------------------------" << "\nGet Main Sail"
      << "\n------------------------" << std::endl;
  attribute =
      loader->get_protocol_engine ()->tlve4_attribute (
	  DataStructureIdentifier::UINT8,
	  loader->get_protocol_engine ()->get_communication_number (
	      loader->get_device_manager ()->get_device (
		  ComponentDescriptorEnum::SERVO_MOTOR_RUDDER)->get_component_descriptor ()));
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::REQUEST_VALUE_W_TIMESTAMP, attribute, 1);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  // SET FORE SAIL
  payload.push_back (0x0A);
  payload.push_back (0xFF);
  std::cout << "\n------------------------" << "\nFore Sail"
      << "\n------------------------" << std::endl;
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET, 0x46,
							3, payload);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  payload.clear ();
  payload.push_back (0xF5);
  payload.push_back (0x01);
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET, 0x46,
							3, payload);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  // GET FORE SAIL
  std::cout << "\n------------------------" << "\nGet Fore Sail"
      << "\n------------------------" << std::endl;
  attribute =
      loader->get_protocol_engine ()->tlve4_attribute (
	  DataStructureIdentifier::UINT8,
	  loader->get_protocol_engine ()->get_communication_number (
	      loader->get_device_manager ()->get_device (
		  ComponentDescriptorEnum::SERVO_MOTOR_RUDDER)->get_component_descriptor ()));
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::REQUEST_VALUE_W_TIMESTAMP, attribute, 1);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  // GET BOAT DESCRIPTION
  std::cout << "\n------------------------" << "\nGet Boat Description"
      << "\n------------------------" << std::endl;
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::GET_BOAT_DESCRIPTION, 0);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  // SET AUTOPILOT COURSE
  if (loader->get_autopilot () != NULL)
    {
      std::cout << "\n------------------------"
	  << "\nSet Autopilot to new Course" << "\n------------------------"
	  << std::endl;
      uint8_t* buf = (uint8_t*) IntConverter::int16_to_int8 (0x0001);
      payload.push_back (buf[0]);
      payload.push_back (buf[1]);
      buf = (uint8_t*) IntConverter::int16_to_int8 (0x0AFF);
      payload.push_back (buf[0]);
      payload.push_back (buf[1]);
      delete[] buf;
      attribute = loader->get_protocol_engine ()->tlve4_attribute (
	  DataStructureIdentifier::INT16,
	  loader->get_autopilot ()->get_communication_number ());
      frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
							    attribute, 5,
							    payload);
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time (start, end);
      std::cout << "\n------------------------" << "\nDeactivate Autopilot"
	  << "\n------------------------" << std::endl;
      buf = (uint8_t*) IntConverter::int16_to_int8 (0x0000);
      payload.clear ();
      payload.push_back (buf[0]);
      payload.push_back (buf[1]);
      buf = (uint8_t*) IntConverter::int16_to_int8 (0x0AFF);
      payload.push_back (buf[0]);
      payload.push_back (buf[1]);
      frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
							    attribute, 5,
							    payload);
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time (start, end);
    }
  // GET CURRENT
  device = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::POWER_SUPPLY_SENSING);
  descriptor = device->get_component_descriptor ();
  attribute = loader->get_protocol_engine ()->tlve4_attribute (
      DataStructureIdentifier::UINT8,
      loader->get_protocol_engine ()->get_communication_number (descriptor));
  std::cout << "\n------------------------" << "\nGet Current"
      << "\n------------------------" << std::endl;
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::REQUEST_VALUE_W_TIMESTAMP, attribute, 1);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  payload.clear ();
  // GET GPS POSITION, VALIDITY AND VELOCITY
  device = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::GPS_POSITION);
  if (GPS* v = dynamic_cast<GPS*> (&(*(device))))
    {
      if (v->is_active () == true)
	{
	  std::cout << "\n------------------------" << "\nGet GPS Position"
	      << "\n------------------------" << std::endl;
	  descriptor = device->get_component_descriptor ();
	  comm_number =
	      loader->get_protocol_engine ()->get_communication_number (
		  descriptor);
	  attribute = loader->get_protocol_engine ()->tlve4_attribute (
	      DataStructureIdentifier::UINT8,
	      loader->get_protocol_engine ()->get_communication_number (
		  device->get_component_descriptor ()));
	  frame = loader->get_protocol_engine ()->create_frame (
	      TagEnum::REQUEST_VALUE_W_TIMESTAMP, attribute, 1);
	  gettimeofday (&start, 0);
	  loader->get_protocol_engine ()->interpret_frame (frame);
	  gettimeofday (&end, 0);
	  print_time (start, end);
	  payload.clear ();

	  std::cout << "\n------------------------" << "\nGet GPS Validity"
	      << "\n------------------------" << std::endl;

	  attribute = loader->get_protocol_engine ()->tlve4_attribute (
	      DataStructureIdentifier::UINT8, comm_number + 1);
	  frame = loader->get_protocol_engine ()->create_frame (
	      TagEnum::REQUEST_VALUE_W_TIMESTAMP, attribute, 1);
	  gettimeofday (&start, 0);
	  loader->get_protocol_engine ()->interpret_frame (frame);
	  gettimeofday (&end, 0);
	  print_time (start, end);

	  std::cout << "\n------------------------" << "\nGet GPS Velocity"
	      << "\n------------------------" << std::endl;

	  attribute = loader->get_protocol_engine ()->tlve4_attribute (
	      DataStructureIdentifier::UINT8, comm_number + 2);
	  frame = loader->get_protocol_engine ()->create_frame (
	      TagEnum::REQUEST_VALUE_W_TIMESTAMP, attribute, 1);
	  gettimeofday (&start, 0);
	  loader->get_protocol_engine ()->interpret_frame (frame);
	  gettimeofday (&end, 0);
	  print_time (start, end);
	}
    }
  // GET ACCELEROMETER
  std::cout << "\n------------------------" << "\nGet Accelerometer"
      << "\n------------------------" << std::endl;
  device = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::ACCELEROMETER);
  comm_number = loader->get_protocol_engine ()->get_communication_number (
      device->get_component_descriptor ());
  attribute = loader->get_protocol_engine ()->tlve4_attribute (
      DataStructureIdentifier::UINT8, comm_number);
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::REQUEST_VALUE_W_TIMESTAMP, attribute, 1);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  // GET COMPASS
  std::cout << "\n------------------------" << "\nGet Compass"
      << "\n------------------------" << std::endl;
  device = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::COMPASS);
  comm_number = loader->get_protocol_engine ()->get_communication_number (
      device->get_component_descriptor ());
  attribute = loader->get_protocol_engine ()->tlve4_attribute (
      DataStructureIdentifier::UINT8, comm_number);
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::REQUEST_VALUE_W_TIMESTAMP, attribute, 1);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  // GET GYROSCOPE
  std::cout << "\n------------------------" << "\nGet Gyroscope"
      << "\n------------------------" << std::endl;
  device = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::GYROSCOPE);
  comm_number = loader->get_protocol_engine ()->get_communication_number (
      device->get_component_descriptor ());
  attribute = loader->get_protocol_engine ()->tlve4_attribute (
      DataStructureIdentifier::UINT8, comm_number);
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::REQUEST_VALUE_W_TIMESTAMP, attribute, 1);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  // GET WIND VANE
  std::cout << "\n------------------------" << "\nGet Windvane"
      << "\n------------------------" << std::endl;
  device = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::WIND_VANE);
  comm_number = loader->get_protocol_engine ()->get_communication_number (
      device->get_component_descriptor ());
  attribute = loader->get_protocol_engine ()->tlve4_attribute (
      DataStructureIdentifier::UINT8, comm_number);
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::REQUEST_VALUE_W_TIMESTAMP, attribute, 1);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  // GET ANEMOMETER
  std::cout << "\n------------------------" << "\nGet Anemometer"
      << "\n------------------------" << std::endl;
  device = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::ANEMOMETER);
  comm_number = loader->get_protocol_engine ()->get_communication_number (
      device->get_component_descriptor ());
  attribute = loader->get_protocol_engine ()->tlve4_attribute (
      DataStructureIdentifier::UINT8, comm_number);
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::REQUEST_VALUE_W_TIMESTAMP, attribute, 1);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  // ERROR UNKNOWN TAG
  std::cout << "\n------------------------" << "\nTag Unknown Tag Error"
      << "\n------------------------" << std::endl;
  device = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::ANEMOMETER);
  comm_number = loader->get_protocol_engine ()->get_communication_number (
      device->get_component_descriptor ());
  attribute = loader->get_protocol_engine ()->tlve4_attribute (
      DataStructureIdentifier::UINT8, comm_number);
  frame = loader->get_protocol_engine ()->create_frame (
      static_cast<TagEnum> (0x45), attribute, 1);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  // ERROR UNKNOWN COMPONENT
  std::cout << "\n------------------------" << "\nTag Unknown Component Error"
      << "\n------------------------" << std::endl;
  comm_number = 0x19;
  attribute = loader->get_protocol_engine ()->tlve4_attribute (
      DataStructureIdentifier::UINT8, comm_number);
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
							attribute, 1);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET,
							attribute, 1);
  gettimeofday (&start, 0);
  loader->get_protocol_engine ()->interpret_frame (frame);
  gettimeofday (&end, 0);
  print_time (start, end);

  // DATA STREAMS
  if (loader->get_stream_generator () != NULL)
    {
      attribute = loader->get_protocol_engine ()->tlve4_attribute (
	  DataStructureIdentifier::INT16,
	  loader->get_stream_generator ()->get_communication_number ());
      device = loader->get_device_manager ()->get_device (
	  ComponentDescriptorEnum::ACCELEROMETER);
      comm_number = loader->get_protocol_engine ()->get_communication_number (
	  device->get_component_descriptor ());
      payload.push_back (0);
      payload.push_back (comm_number);
      payload.push_back (0x09); //2500 ms
      payload.push_back (0xC4);
      frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
							    attribute,
							    payload.size () + 1,
							    payload);
      std::cout << "Activate Accelerometer Stream" << std::endl;
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time (start, end);

      device = loader->get_device_manager ()->get_device (
	  ComponentDescriptorEnum::COMPASS);
      comm_number = loader->get_protocol_engine ()->get_communication_number (
	  device->get_component_descriptor ());
      payload.clear ();
      payload.push_back (0);
      payload.push_back (comm_number);
      payload.push_back (0x13); //5000ms
      payload.push_back (0x88);
      frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
							    attribute,
							    payload.size () + 1,
							    payload);
      std::cout << "Activate Compass Stream" << std::endl;
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time (start, end);

      device = loader->get_device_manager ()->get_device (
	  ComponentDescriptorEnum::GYROSCOPE);
      comm_number = loader->get_protocol_engine ()->get_communication_number (
	  device->get_component_descriptor ());
      payload.clear ();
      payload.push_back (0);
      payload.push_back (comm_number);
      payload.push_back (0x27); //10000ms
      payload.push_back (0x10);
      frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
							    attribute,
							    payload.size () + 1,
							    payload);
      std::cout << "Activate Gyroscope Stream" << std::endl;
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time (start, end);

      device = loader->get_device_manager ()->get_device (
	  ComponentDescriptorEnum::ACCELEROMETER);
      comm_number = loader->get_protocol_engine ()->get_communication_number (
	  device->get_component_descriptor ());
      payload.clear ();
      payload.push_back (0);
      payload.push_back (comm_number);
      payload.push_back (0x00); //0 ms
      payload.push_back (0x00);
      frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
							    attribute,
							    payload.size () + 1,
							    payload);
      std::cout << "Deactivate Accelerometer Stream" << std::endl;
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time (start, end);

      device = loader->get_device_manager ()->get_device (
	  ComponentDescriptorEnum::ACCELEROMETER);
      comm_number = loader->get_protocol_engine ()->get_communication_number (
	  device->get_component_descriptor ());
      payload.clear ();
      payload.push_back (0);
      payload.push_back (comm_number);
      payload.push_back (0x1D); //7500 ms
      payload.push_back (0x4C);
      frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
							    attribute,
							    payload.size () + 1,
							    payload);
      std::cout << "Activate Accelerometer Stream" << std::endl;
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time (start, end);

      device = loader->get_device_manager ()->get_device (
	  ComponentDescriptorEnum::GPS_POSITION);
      if (GPS* v = dynamic_cast<GPS*> (&(*(device))))
	{
	  if (v->is_active () == true)
	    {
	      comm_number =
		  loader->get_protocol_engine ()->get_communication_number (
		      device->get_component_descriptor ());
	      attribute = loader->get_protocol_engine ()->tlve4_attribute (
		  DataStructureIdentifier::INT16,
		  loader->get_stream_generator ()->get_communication_number ());
	      payload.clear ();
	      payload.push_back (0);
	      payload.push_back (comm_number);
	      payload.push_back (0x1D); //7500 ms
	      payload.push_back (0x4C);
	      frame = loader->get_protocol_engine ()->create_frame (
		  TagEnum::SET_VALUE, attribute, payload.size () + 1, payload);
	      std::cout << "Activate GPS Position Stream" << std::endl;
	      gettimeofday (&start, 0);
	      loader->get_protocol_engine ()->interpret_frame (frame);
	      gettimeofday (&end, 0);
	      print_time (start, end);

	      device = loader->get_device_manager ()->get_device (
		  ComponentDescriptorEnum::GPS_POSITION);
	      comm_number =
		  loader->get_protocol_engine ()->get_communication_number (
		      device->get_component_descriptor ()) + 1;
	      payload.clear ();
	      payload.push_back (0);
	      payload.push_back (comm_number);
	      payload.push_back (0x1D); //7500 ms
	      payload.push_back (0x4C);
	      frame = loader->get_protocol_engine ()->create_frame (
		  TagEnum::SET_VALUE, attribute, payload.size () + 1, payload);
	      std::cout << "Activate GPS Validity Stream" << std::endl;
	      gettimeofday (&start, 0);
	      loader->get_protocol_engine ()->interpret_frame (frame);
	      gettimeofday (&end, 0);
	      print_time (start, end);

	      device = loader->get_device_manager ()->get_device (
		  ComponentDescriptorEnum::GPS_POSITION);
	      comm_number =
		  loader->get_protocol_engine ()->get_communication_number (
		      device->get_component_descriptor ()) + 2;
	      payload.clear ();
	      payload.push_back (0);
	      payload.push_back (comm_number);
	      payload.push_back (0x1D); //7500 ms
	      payload.push_back (0x4C);
	      frame = loader->get_protocol_engine ()->create_frame (
		  TagEnum::SET_VALUE, attribute, payload.size () + 1, payload);
	      std::cout << "Activate GPS Velocity Stream" << std::endl;
	      gettimeofday (&start, 0);
	      loader->get_protocol_engine ()->interpret_frame (frame);
	      gettimeofday (&end, 0);
	      print_time (start, end);
	    }
	}
      // GET COMPASS STREAM
      device = loader->get_device_manager ()->get_device (
	  ComponentDescriptorEnum::COMPASS);
      comm_number = loader->get_protocol_engine ()->get_communication_number (
	  device->get_component_descriptor ());
      payload.clear ();
      payload.push_back (comm_number);
      frame = loader->get_protocol_engine ()->create_frame (
	  TagEnum::REQUEST_VALUE, attribute, payload.size () + 1, payload);
      std::cout << "Get Compass" << std::endl;
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time (start, end);
      // GET ALL STREAMS
      payload.clear ();
      frame = loader->get_protocol_engine ()->create_frame (
	  TagEnum::REQUEST_VALUE, attribute, 1);
      std::cout << "Get all streams" << std::endl;
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time (start, end);
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
  frame_test ();

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
