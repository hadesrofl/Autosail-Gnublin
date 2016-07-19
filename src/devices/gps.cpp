#include "gps.h"

// Private Functions
int8_t
GPS::init ()
{
  char command[COMMAND_SIZE];
  SerialParameter* parameter =
      dynamic_cast<SerialParameter*> (&(*m_device_parameter));
  if (parameter != NULL)
    {
      snprintf (command, COMMAND_SIZE, "stty -F %s %d",
		parameter->get_device_file (), parameter->get_baudrate ());
      // Set Baudrate of UART
      system (command);
      // Start GPSd
      snprintf (command,
      COMMAND_SIZE,
		"gpsd -n %s", parameter->get_device_file ());
      // First Kill old GPSd before starting a new one
      system ("killall gpsd");
      system (command);
      return 1;
    }
  else
    {
      return -1;
    }

}
// Public Functions
GPS::GPS (SerialParameter *interface_parameter, ComponentDescriptor* descriptor)
{
  m_interface_port = std::unique_ptr<Serial> (
      new Serial (interface_parameter->get_device_file (),
		  interface_parameter->get_baudrate ()));
  set_component_descriptor (descriptor);
  m_device_parameter = std::unique_ptr<SerialParameter> (interface_parameter);
  m_datastructure_id = DataStructureIdentifier::INT32;
  init ();
}
std::vector<int8_t>
GPS::read_data ()
{
  gps_data_t* raw_data = new gps_data_t;
  std::vector<int8_t> data;
  char command[COMMAND_SIZE];
  snprintf (command, COMMAND_SIZE, "%s > %s", SUB_PROGRAM, TMP_DATA_FILE);
  std::ifstream source;
#ifdef _DEBUG
  std::cout << "GPS Read Begin" << std::endl;
#endif
  system (command);
  source.open (TMP_DATA_FILE, std::ios_base::in);
  if (!source)
    {
#ifdef _DEBUG
      std::cerr << "Can't open file!" << std::endl;
#endif
      raw_data->latitude = 0.0;
      raw_data->longitude = 0.0;
      raw_data->timestamp = 0;
      raw_data->speed = 0.0;
#ifdef _DEBUG
      std::cout << "GPS Read End" << std::endl;
#endif
      return data;
    }
  else
    {
      for (std::string line; std::getline (source, line);)
	{
	  float tmp;
	  std::istringstream in (line);
	  std::string type;
	  in >> type;
	  if (type == "Latitude:")
	    {
	      in >> tmp;
	      raw_data->latitude = tmp * DECIMAL_SHIFT_POSITION;
	    }
	  else if (type == "Longitude:")
	    {
	      in >> tmp;
	      raw_data->longitude = tmp * DECIMAL_SHIFT_POSITION;
	    }
	  else if (type == "Speed:")
	    {
	      in >> tmp;
	      raw_data->speed = tmp * DECIMAL_SHIFT_SPEED;
	    }
	  else if (type == "Timestamp:")
	    {
	      in >> raw_data->timestamp;
	    }
	}
      int8_t* tmp_latitude = new int8_t[4];
      int8_t* tmp_longitude = new int8_t[4];
      int8_t* tmp_speed = new int8_t[4];
      int8_t* tmp_timestamp = new int8_t[4];
      tmp_latitude = IntConverter::int32_to_int8 (raw_data->latitude);
      tmp_longitude = IntConverter::int32_to_int8 (raw_data->longitude);
      tmp_speed = IntConverter::int32_to_int8 (raw_data->speed);
      tmp_timestamp = IntConverter::int32_to_int8 (raw_data->timestamp);

      for (int8_t i = 0; i < 4; i++)
	{
	  data.push_back(tmp_latitude[i]);
	}
      for (int8_t i = 0; i < 4; i++)
	{
	  data.push_back(tmp_longitude[i]);
	}
      for (int8_t i = 0; i < 4; i++)
	{
	  data.push_back(tmp_speed[i]);
	}
      for (int8_t i = 0; i < 4; i++)
	{
	  data.push_back(tmp_timestamp[i]);
	}
#ifdef _DEBUG
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
      int32_t latitude = IntConverter::int8_to_int32(test_latitude);
      int32_t longitude = IntConverter::int8_to_int32(test_longitude);
      int32_t speed = IntConverter::int8_to_int32(test_speed);
      int32_t timestamp = IntConverter::int8_to_int32(test_timestamp);
      delete[] test_latitude;
      delete[] test_longitude;
      delete[] test_speed;
      delete[] test_timestamp;
      std::cout << "Latitude raw: " << raw_data->latitude << std::endl;
      std::cout << "Longitude raw: " << raw_data->longitude << std::endl;
      std::cout << "Speed raw: " << raw_data->speed << std::endl;
      std::cout << "Timestamp raw: " << raw_data->timestamp << std::endl;
      std::cout << "Latitude data: " << latitude << std::endl;
      std::cout << "Longitude data: " << longitude << std::endl;
      std::cout << "Speed data: " << speed << std::endl;
      std::cout << "Timestamp data: " << timestamp << std::endl;
      std::cout << "GPS Read End" << std::endl;
#endif
      delete[] tmp_latitude;
      delete[] tmp_longitude;
      delete[] tmp_speed;
      delete[] tmp_timestamp;
      delete[] raw_data;
      return data;
    }
}
GPS::~GPS ()
{
}

