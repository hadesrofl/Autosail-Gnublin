#ifdef _TEST
#include "frame_interpreter_test.h"

FrameInterpreterTest::FrameInterpreterTest ()
{

}
void
FrameInterpreterTest::print_time (const char* command, timeval begin,
				  timeval end)
{
  std::cout << command << ";" << (begin.tv_sec) << ";" << (begin.tv_usec) / 1000
      << ";" << (end.tv_sec) << ";" << (end.tv_usec) / 1000 << ";"
      << (end.tv_sec - begin.tv_sec) * 1000
	  + (end.tv_usec - begin.tv_usec) / 1000 << ";" << std::endl;
}
void
FrameInterpreterTest::eval ()
{
  Loader* loader = new Loader ();
  std::vector<uint8_t> payload;
  uint8_t comm_number, attribute;
  std::shared_ptr<Device> device;
  std::shared_ptr<ComponentDescriptor> descriptor;
  Frame* frame;
  timeval start, end;
  std::cout
      << "Command;Start Frame Seconds; Start Frame Milliseconds;End Frame Seconds;End Frame Milliseconds;Difference;"
      << std::endl;
  uint16_t counter = 0;
  while (counter != 100)
    {
      counter++;
      // GET PROTOCOL VERSION
      std::cout << "\n------------------------" << "\nGet Protocol Version"
	  << "\n------------------------" << std::endl;
      frame = loader->get_protocol_engine ()->create_frame (
	  TagEnum::GET_PROTOCOL_VERSION, 0, 0);
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time ("Get Protocol Version", start, end);

      // GET BOAT ID
      std::cout << "\n------------------------" << "\nGet Boat ID"
	  << "\n------------------------" << std::endl;
      frame = loader->get_protocol_engine ()->create_frame (
	  TagEnum::GET_BOAT_ID, 0, 0);
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time ("Get Boat ID", start, end);
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
	  print_time ("Set Control Mode", start, end);
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
	  print_time ("Get Control Mode", start, end);
	  payload.push_back (0x01);
	  frame = loader->get_protocol_engine ()->create_frame (
	      TagEnum::SET_CONTROL_MODE, 0, 1, payload);
	  gettimeofday (&start, 0);
	  loader->get_protocol_engine ()->interpret_frame (frame);
	  gettimeofday (&end, 0);
	  print_time ("Set Control Mode", start, end);
	  frame = loader->get_protocol_engine ()->create_frame (
	      TagEnum::GET_CONTROL_MODE, 0, 0);
	  gettimeofday (&start, 0);
	  loader->get_protocol_engine ()->interpret_frame (frame);
	  gettimeofday (&end, 0);
	  print_time ("Get Control Mode", start, end);
	  frame = loader->get_protocol_engine ()->create_frame (
	      TagEnum::GET_CONTROL_MODE, 0, 0);
	  gettimeofday (&start, 0);
	  loader->get_protocol_engine ()->interpret_frame (frame);
	  gettimeofday (&end, 0);
	  print_time ("Set Control Mode", start, end);
	}
      // SET RUDDER
      payload.push_back (0x0A);
      payload.push_back (0xFF);
      std::cout << "\n------------------------" << "\nRudder"
	  << "\n------------------------" << std::endl;
      frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET,
							    0x44, 3, payload);
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time ("PM Set", start, end);

      payload.clear ();
      payload.push_back (0xF5);
      payload.push_back (0x01);
      frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET,
							    0x44, 3, payload);
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time ("PM Set", start, end);
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
      print_time ("Request Value with Timestamp (Rudder)", start, end);
      // SET MAIN SAIL
      payload.push_back (0x0A);
      payload.push_back (0xFF);
      std::cout << "\n------------------------" << "\nMain Sail"
	  << "\n------------------------" << std::endl;
      frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET,
							    0x45, 3, payload);
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time ("PM Set", start, end);
      payload.clear ();
      payload.push_back (0xF5);
      payload.push_back (0x01);
      frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET,
							    0x45, 3, payload);
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time ("PM Set", start, end);
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
      print_time ("Request Value with Timestamp (Rudder)", start, end);
      // SET FORE SAIL
      payload.push_back (0x0A);
      payload.push_back (0xFF);
      std::cout << "\n------------------------" << "\nFore Sail"
	  << "\n------------------------" << std::endl;
      frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET,
							    0x46, 3, payload);
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time ("PM Set", start, end);
      payload.clear ();
      payload.push_back (0xF5);
      payload.push_back (0x01);
      frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET,
							    0x46, 3, payload);
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time ("PM Set", start, end);
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
      print_time ("Request Value with Timestamp (Rudder)", start, end);
      // GET BOAT DESCRIPTION
      std::cout << "\n------------------------" << "\nGet Boat Description"
	  << "\n------------------------" << std::endl;
      frame = loader->get_protocol_engine ()->create_frame (
	  TagEnum::GET_BOAT_DESCRIPTION, 0);
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time ("Get Boat Description", start, end);
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
	  frame = loader->get_protocol_engine ()->create_frame (
	      TagEnum::SET_VALUE, attribute, 5, payload);
	  gettimeofday (&start, 0);
	  loader->get_protocol_engine ()->interpret_frame (frame);
	  gettimeofday (&end, 0);
	  print_time ("Set Value", start, end);
	  std::cout << "\n------------------------" << "\nDeactivate Autopilot"
	      << "\n------------------------" << std::endl;
	  buf = (uint8_t*) IntConverter::int16_to_int8 (0x0000);
	  payload.clear ();
	  payload.push_back (buf[0]);
	  payload.push_back (buf[1]);
	  buf = (uint8_t*) IntConverter::int16_to_int8 (0x0AFF);
	  payload.push_back (buf[0]);
	  payload.push_back (buf[1]);
	  frame = loader->get_protocol_engine ()->create_frame (
	      TagEnum::SET_VALUE, attribute, 5, payload);
	  gettimeofday (&start, 0);
	  loader->get_protocol_engine ()->interpret_frame (frame);
	  gettimeofday (&end, 0);
	  print_time ("Set Value", start, end);
	}
      // GET CURRENT
      device = loader->get_device_manager ()->get_device (
	  ComponentDescriptorEnum::POWER_SUPPLY_SENSING);
      descriptor = device->get_component_descriptor ();
      attribute = loader->get_protocol_engine ()->tlve4_attribute (
	  DataStructureIdentifier::UINT8,
	  loader->get_protocol_engine ()->get_communication_number (
	      descriptor));
      std::cout << "\n------------------------" << "\nGet Current"
	  << "\n------------------------" << std::endl;
      frame = loader->get_protocol_engine ()->create_frame (
	  TagEnum::REQUEST_VALUE_W_TIMESTAMP, attribute, 1);
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time ("Request Value with Timestamp (Current)", start, end);
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
	      print_time ("Request Value with Timestamp (GPS)", start, end);
	      payload.clear ();

	      std::cout << "\n------------------------" << "\nGet GPS Validity"
		  << "\n------------------------" << std::endl;

	      attribute = loader->get_protocol_engine ()->tlve4_attribute (
		  DataStructureIdentifier::UINT8, comm_number + 1);
	      frame = loader->get_protocol_engine ()->create_frame (
		  TagEnum::REQUEST_VALUE_W_TIMESTAMP , attribute, 1);
	      gettimeofday (&start, 0);
	      loader->get_protocol_engine ()->interpret_frame (frame);
	      gettimeofday (&end, 0);
	      print_time ("Request Value with Timestamp (GPS)", start, end);

	      std::cout << "\n------------------------" << "\nGet GPS Velocity"
		  << "\n------------------------" << std::endl;

	      attribute = loader->get_protocol_engine ()->tlve4_attribute (
		  DataStructureIdentifier::UINT8, comm_number + 2);
	      frame = loader->get_protocol_engine ()->create_frame (
		  TagEnum::REQUEST_VALUE_W_TIMESTAMP, attribute, 1);
	      gettimeofday (&start, 0);
	      loader->get_protocol_engine ()->interpret_frame (frame);
	      gettimeofday (&end, 0);
	      print_time ("Request Value with Timestamp (GPS)", start, end);
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
      print_time ("Request Value with Timestamp (Acc)", start, end);
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
      print_time ("Request Value with Timestamp (Compass)", start, end);
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
      print_time ("Request Value with Timestamp (Gyroscope)", start, end);
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
      print_time ("Request Value with Timestamp (Wind Vane)", start, end);
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
      print_time ("Request Value with Timestamp (Anemometer)", start, end);
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
      print_time ("Error", start, end);
      // ERROR UNKNOWN COMPONENT
      std::cout << "\n------------------------"
	  << "\nTag Unknown Component Error" << "\n------------------------"
	  << std::endl;
      comm_number = 0x19;
      attribute = loader->get_protocol_engine ()->tlve4_attribute (
	  DataStructureIdentifier::UINT8, comm_number);
      frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
							    attribute, 1);
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time ("Error", start, end);
      frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET,
							    attribute, 1);
      gettimeofday (&start, 0);
      loader->get_protocol_engine ()->interpret_frame (frame);
      gettimeofday (&end, 0);
      print_time ("Error", start, end);

      // DATA STREAMS
      if (loader->get_stream_generator () != NULL)
	{
	  attribute = loader->get_protocol_engine ()->tlve4_attribute (
	      DataStructureIdentifier::INT16,
	      loader->get_stream_generator ()->get_communication_number ());
	  device = loader->get_device_manager ()->get_device (
	      ComponentDescriptorEnum::ACCELEROMETER);
	  comm_number =
	      loader->get_protocol_engine ()->get_communication_number (
		  device->get_component_descriptor ());
	  payload.push_back (0);
	  payload.push_back (comm_number);
	  payload.push_back (0x09); //2500 ms
	  payload.push_back (0xC4);
	  frame = loader->get_protocol_engine ()->create_frame (
	      TagEnum::SET_VALUE, attribute, payload.size () + 1, payload);
	  std::cout << "Activate Accelerometer Stream" << std::endl;
	  gettimeofday (&start, 0);
	  loader->get_protocol_engine ()->interpret_frame (frame);
	  gettimeofday (&end, 0);
	  print_time ("Set Value (Stream)", start, end);

	  device = loader->get_device_manager ()->get_device (
	      ComponentDescriptorEnum::COMPASS);
	  comm_number =
	      loader->get_protocol_engine ()->get_communication_number (
		  device->get_component_descriptor ());
	  payload.clear ();
	  payload.push_back (0);
	  payload.push_back (comm_number);
	  payload.push_back (0x13); //5000ms
	  payload.push_back (0x88);
	  frame = loader->get_protocol_engine ()->create_frame (
	      TagEnum::SET_VALUE, attribute, payload.size () + 1, payload);
	  std::cout << "Activate Compass Stream" << std::endl;
	  gettimeofday (&start, 0);
	  loader->get_protocol_engine ()->interpret_frame (frame);
	  gettimeofday (&end, 0);
	  print_time ("Set Value (Stream)", start, end);

	  device = loader->get_device_manager ()->get_device (
	      ComponentDescriptorEnum::GYROSCOPE);
	  comm_number =
	      loader->get_protocol_engine ()->get_communication_number (
		  device->get_component_descriptor ());
	  payload.clear ();
	  payload.push_back (0);
	  payload.push_back (comm_number);
	  payload.push_back (0x27); //10000ms
	  payload.push_back (0x10);
	  frame = loader->get_protocol_engine ()->create_frame (
	      TagEnum::SET_VALUE, attribute, payload.size () + 1, payload);
	  std::cout << "Activate Gyroscope Stream" << std::endl;
	  gettimeofday (&start, 0);
	  loader->get_protocol_engine ()->interpret_frame (frame);
	  gettimeofday (&end, 0);
	  print_time ("Set Value (Stream)", start, end);

	  device = loader->get_device_manager ()->get_device (
	      ComponentDescriptorEnum::ACCELEROMETER);
	  comm_number =
	      loader->get_protocol_engine ()->get_communication_number (
		  device->get_component_descriptor ());
	  payload.clear ();
	  payload.push_back (0);
	  payload.push_back (comm_number);
	  payload.push_back (0x00); //0 ms
	  payload.push_back (0x00);
	  frame = loader->get_protocol_engine ()->create_frame (
	      TagEnum::SET_VALUE, attribute, payload.size () + 1, payload);
	  std::cout << "Deactivate Accelerometer Stream" << std::endl;
	  gettimeofday (&start, 0);
	  loader->get_protocol_engine ()->interpret_frame (frame);
	  gettimeofday (&end, 0);
	  print_time ("Set Value (Stream)", start, end);

	  device = loader->get_device_manager ()->get_device (
	      ComponentDescriptorEnum::ACCELEROMETER);
	  comm_number =
	      loader->get_protocol_engine ()->get_communication_number (
		  device->get_component_descriptor ());
	  payload.clear ();
	  payload.push_back (0);
	  payload.push_back (comm_number);
	  payload.push_back (0x1D); //7500 ms
	  payload.push_back (0x4C);
	  frame = loader->get_protocol_engine ()->create_frame (
	      TagEnum::SET_VALUE, attribute, payload.size () + 1, payload);
	  std::cout << "Activate Accelerometer Stream" << std::endl;
	  gettimeofday (&start, 0);
	  loader->get_protocol_engine ()->interpret_frame (frame);
	  gettimeofday (&end, 0);
	  print_time ("Set Value (Stream)", start, end);

	  device = loader->get_device_manager ()->get_device (
	      ComponentDescriptorEnum::GPS_POSITION);
	  if (GPS* v = dynamic_cast<GPS*> (&(*(device))))
	    {
	      if (v->is_active () == true)
		{
		  comm_number =
		      loader->get_protocol_engine ()->get_communication_number (
			  device->get_component_descriptor ());
		  attribute =
		      loader->get_protocol_engine ()->tlve4_attribute (
			  DataStructureIdentifier::INT16,
			  loader->get_stream_generator ()->get_communication_number ());
		  payload.clear ();
		  payload.push_back (0);
		  payload.push_back (comm_number);
		  payload.push_back (0x1D); //7500 ms
		  payload.push_back (0x4C);
		  frame = loader->get_protocol_engine ()->create_frame (
		      TagEnum::SET_VALUE, attribute, payload.size () + 1,
		      payload);
		  std::cout << "Activate GPS Position Stream" << std::endl;
		  gettimeofday (&start, 0);
		  loader->get_protocol_engine ()->interpret_frame (frame);
		  gettimeofday (&end, 0);
		  print_time ("Set Value (Stream)", start, end);

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
		      TagEnum::SET_VALUE, attribute, payload.size () + 1,
		      payload);
		  std::cout << "Activate GPS Validity Stream" << std::endl;
		  gettimeofday (&start, 0);
		  loader->get_protocol_engine ()->interpret_frame (frame);
		  gettimeofday (&end, 0);
		  print_time ("Set Value (Stream)", start, end);

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
		      TagEnum::SET_VALUE, attribute, payload.size () + 1,
		      payload);
		  std::cout << "Activate GPS Velocity Stream" << std::endl;
		  gettimeofday (&start, 0);
		  loader->get_protocol_engine ()->interpret_frame (frame);
		  gettimeofday (&end, 0);
		  print_time ("Set Value (Stream)", start, end);
		}
	    }
	  // GET COMPASS STREAM
	  device = loader->get_device_manager ()->get_device (
	      ComponentDescriptorEnum::COMPASS);
	  comm_number =
	      loader->get_protocol_engine ()->get_communication_number (
		  device->get_component_descriptor ());
	  payload.clear ();
	  payload.push_back (comm_number);
	  frame = loader->get_protocol_engine ()->create_frame (
	      TagEnum::REQUEST_VALUE, attribute, payload.size () + 1, payload);
	  std::cout << "Get Compass" << std::endl;
	  gettimeofday (&start, 0);
	  loader->get_protocol_engine ()->interpret_frame (frame);
	  gettimeofday (&end, 0);
	  print_time ("Request Value (Compass Stream)", start, end);
	  // GET ALL STREAMS
	  payload.clear ();
	  frame = loader->get_protocol_engine ()->create_frame (
	      TagEnum::REQUEST_VALUE, attribute, 1);
	  std::cout << "Get all streams" << std::endl;
	  gettimeofday (&start, 0);
	  loader->get_protocol_engine ()->interpret_frame (frame);
	  gettimeofday (&end, 0);
	  print_time ("Request Value (All Streams)", start, end);
	}
    }
}
void
FrameInterpreterTest::run_test ()
{
  Loader* loader = new Loader ();
  SPIParameter* spi_param = new SPIParameter (0, DeviceConfig::SPI_SPEED_1MHZ,
					      true);
  SPIMasterSelect* spi = new SPIMasterSelect (spi_param->get_device_file (),
					      spi_param->get_speed (), 11);
  pthread_t interrupt_thread_a, test_thread;
  struct spi_thread_param_t params;
  params.spi_ptr = spi;
  pthread_mutex_init (&params.count_mutex, NULL);

  pthread_cond_init (&params.wakeup_cond, NULL);
  pthread_create (&interrupt_thread_a, NULL,
		  params.spi_ptr->pin_change_interrupt, &params);
  pthread_create (&test_thread, NULL, test_teensy, NULL);
  pthread_mutex_lock (&params.count_mutex);

  pthread_cond_wait (&params.wakeup_cond, &params.count_mutex);
  sleep (5);
  while (params.frame_count > 0)
    {
      std::cout << "\nFrame Count: " << params.frame_count << std::endl;
      loader->get_protocol_engine ()->receive_frame ();
      params.frame_count--;
    }
}
void*
FrameInterpreterTest::test_teensy (void* params)
{
  Loader* loader = new Loader ();
  std::vector<uint8_t> payload;
  uint8_t comm_number, attribute;
  std::shared_ptr<Device> device;
  std::shared_ptr<ComponentDescriptor> descriptor;
  Frame* frame;
  // GET PROTOCOL VERSION
  std::cout << "\n------------------------" << "\nGet Protocol Version"
      << "\n------------------------" << std::endl;
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::GET_PROTOCOL_VERSION, 0, 0);
  loader->get_protocol_engine ()->send_frame (frame);
//  GET BOAT ID
  std::cout << "\n------------------------" << "\nGet Boat ID"
      << "\n------------------------" << std::endl;
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::GET_BOAT_ID, 0,
							0);
  loader->get_protocol_engine ()->send_frame (frame);
//   SET CONTROL MODE
  payload.push_back (0x00);
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::SET_CONTROL_MODE, 0, 1, payload);
  std::cout << "\n------------------------" << "\nSet Control Mode"
      << "\n------------------------" << std::endl;
  if (loader->get_autopilot () != NULL)
    {
      loader->get_protocol_engine ()->send_frame (frame);
    }
  payload.clear ();
  // GET CONTROL MODE
  frame = loader->get_protocol_engine ()->create_frame (
      TagEnum::GET_CONTROL_MODE, 0, 0);
  if (loader->get_autopilot () != NULL)
    {
      loader->get_protocol_engine ()->send_frame (frame);
      payload.push_back (0x01);
      frame = loader->get_protocol_engine ()->create_frame (
	  TagEnum::SET_CONTROL_MODE, 0x01, 1);
      loader->get_protocol_engine ()->send_frame (frame);
      frame = loader->get_protocol_engine ()->create_frame (
	  TagEnum::GET_CONTROL_MODE, 0, 0);
      loader->get_protocol_engine ()->send_frame (frame);
    }
  // SET RUDDER
  payload.clear ();
  payload.push_back (0x0A);
  payload.push_back (0xFF);
  std::cout << "\n------------------------" << "\nRudder"
      << "\n------------------------" << std::endl;
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET, 0x44,
							payload.size () + 1,
							payload);
  loader->get_protocol_engine ()->send_frame (frame);

  payload.clear ();
  payload.push_back (0xF5);
  payload.push_back (0x01);
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET, 0x44,
							payload.size () + 1,
							payload);
  loader->get_protocol_engine ()->send_frame (frame);
//  // GET RUDDER
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
  loader->get_protocol_engine ()->send_frame (frame);
  // SET MAIN SAIL
  payload.push_back (0x0A);
  payload.push_back (0xFF);
  std::cout << "\n------------------------" << "\nMain Sail"
      << "\n------------------------" << std::endl;
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET, 0x45,
							payload.size () + 1,
							payload);
  loader->get_protocol_engine ()->send_frame (frame);
  payload.clear ();
  payload.push_back (0xF5);
  payload.push_back (0x01);
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET, 0x45,
							payload.size () + 1,
							payload);
  loader->get_protocol_engine ()->send_frame (frame);
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
  loader->get_protocol_engine ()->send_frame (frame);
  // SET FORE SAIL
  payload.push_back (0x0A);
  payload.push_back (0xFF);
  std::cout << "\n------------------------" << "\nFore Sail"
      << "\n------------------------" << std::endl;
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET, 0x46,
							payload.size () + 1,
							payload);
  loader->get_protocol_engine ()->send_frame (frame);
  payload.clear ();
  payload.push_back (0xF5);
  payload.push_back (0x01);
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET, 0x46,
							payload.size () + 1,
							payload);
  loader->get_protocol_engine ()->send_frame (frame);
//  // GET FORE SAIL
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
  loader->get_protocol_engine ()->send_frame (frame);
  // GET BOAT DESCRIPTION
//  std::cout << "\n------------------------" << "\nGet Boat Description"
//      << "\n------------------------" << std::endl;
//  frame = loader->get_protocol_engine ()->create_frame (
//      TagEnum::GET_BOAT_DESCRIPTION, 0);
//  loader->get_protocol_engine ()->send_frame (frame);
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
							    attribute,
							    payload.size () + 1,
							    payload);
      loader->get_protocol_engine ()->send_frame (frame);
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
							    attribute,
							    payload.size () + 1,
							    payload);
      loader->get_protocol_engine ()->send_frame (frame);
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
  loader->get_protocol_engine ()->send_frame (frame);
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
	  loader->get_protocol_engine ()->send_frame (frame);
	  payload.clear ();
	  std::cout << "\n------------------------" << "\nGet GPS Validity"
	      << "\n------------------------" << std::endl;
	  attribute = loader->get_protocol_engine ()->tlve4_attribute (
	      DataStructureIdentifier::UINT8, comm_number + 1);
	  frame = loader->get_protocol_engine ()->create_frame (
	      TagEnum::REQUEST_VALUE_W_TIMESTAMP, attribute, 1);
	  loader->get_protocol_engine ()->send_frame (frame);
	  std::cout << "\n------------------------" << "\nGet GPS Velocity"
	      << "\n------------------------" << std::endl;
	  attribute = loader->get_protocol_engine ()->tlve4_attribute (
	      DataStructureIdentifier::UINT8, comm_number + 2);
	  frame = loader->get_protocol_engine ()->create_frame (
	      TagEnum::REQUEST_VALUE_W_TIMESTAMP, attribute, 1);
	  loader->get_protocol_engine ()->send_frame (frame);
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
  loader->get_protocol_engine ()->send_frame (frame);
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
  loader->get_protocol_engine ()->send_frame (frame);
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
  loader->get_protocol_engine ()->send_frame (frame);
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
  loader->get_protocol_engine ()->send_frame (frame);
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
  loader->get_protocol_engine ()->send_frame (frame);
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
  loader->get_protocol_engine ()->send_frame (frame);
  // ERROR UNKNOWN COMPONENT
  std::cout << "\n------------------------" << "\nTag Unknown Component Error"
      << "\n------------------------" << std::endl;
  comm_number = 0x19;
  attribute = loader->get_protocol_engine ()->tlve4_attribute (
      DataStructureIdentifier::UINT8, comm_number);
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
							attribute, 1);
  loader->get_protocol_engine ()->send_frame (frame);
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::PM_SET,
							attribute, 1);
  loader->get_protocol_engine ()->send_frame (frame);
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
      std::cout << "\n------------------------"
	  << "\nActivate Accelerometer Stream" << "\n------------------------"
	  << std::endl;
      loader->get_protocol_engine ()->send_frame (frame);
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
      std::cout << "\n------------------------" << "\nActivate Compass Stream"
	  << "\n------------------------" << std::endl;
      loader->get_protocol_engine ()->send_frame (frame);
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
      std::cout << "\n------------------------" << "\nActivate Gyroscope Stream"
	  << "\n------------------------" << std::endl;
      loader->get_protocol_engine ()->send_frame (frame);
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
      std::cout << "\n------------------------"
	  << "\nDeactivate Accelerometer Stream" << "\n------------------------"
	  << std::endl;
      loader->get_protocol_engine ()->send_frame (frame);
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
      std::cout << "\n------------------------"
	  << "\nActivate Accelerometer Stream" << "\n------------------------"
	  << std::endl;
      loader->get_protocol_engine ()->send_frame (frame);
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
	      std::cout << "\n------------------------"
		  << "\nActivate GPS Position Stream"
		  << "\n------------------------" << std::endl;
	      loader->get_protocol_engine ()->send_frame (frame);
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
	      std::cout << "\n------------------------"
		  << "\nActivate GPS Validity Stream"
		  << "\n------------------------" << std::endl;
	      loader->get_protocol_engine ()->send_frame (frame);
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
	      std::cout << "\n------------------------"
		  << "\nActivate GPS Velocity Stream"
		  << "\n------------------------" << std::endl;
	      loader->get_protocol_engine ()->send_frame (frame);
	    }
	}
      // GET COMPASS STREAM
      device = loader->get_device_manager ()->get_device (
	  ComponentDescriptorEnum::COMPASS);
      comm_number = loader->get_protocol_engine ()->get_communication_number (
	  device->get_component_descriptor ());
      payload.clear ();
      attribute = loader->get_protocol_engine ()->tlve4_attribute (
	  DataStructureIdentifier::UINT8,
	  loader->get_stream_generator ()->get_communication_number ());
      payload.push_back (comm_number);
      frame = loader->get_protocol_engine ()->create_frame (
	  TagEnum::REQUEST_VALUE, attribute, payload.size () + 1, payload);
      std::cout << "\n------------------------" << "\nGet Compass"
	  << "\n------------------------" << std::endl;
      loader->get_protocol_engine ()->send_frame (frame);
      // GET ALL STREAMS
      payload.clear ();
      frame = loader->get_protocol_engine ()->create_frame (
	  TagEnum::REQUEST_VALUE, attribute, 1);
      std::cout << "\n------------------------" << "\nGet all streams"
	  << "\n------------------------" << std::endl;
      loader->get_protocol_engine ()->send_frame (frame);
    }
  return NULL;
}

FrameInterpreterTest::~FrameInterpreterTest ()
{
}
#endif
