#include "gps.h"

// Private Functions
int8_t
GPS::init ()
{
  m_last_data->direction = 0;
  m_last_data->fix_mode = 0;
  m_last_data->latitude = 0;
  m_last_data->longitude = 0;
  m_last_data->speed = 0;
  m_last_data->timestamp = 0;
  int32_t result;
  char command[COMMAND_SIZE];
  SerialParameter* parameter =
      dynamic_cast<SerialParameter*> (&(*m_device_parameter));
  if (parameter != NULL)
    {
      snprintf (command, COMMAND_SIZE, "stty -F %s %d",
		parameter->get_device_file (), parameter->get_baudrate ());
      // Set Baudrate of UART
      result = system (command);
      // 256 == no such device, so GPS is not active
      if (result == 256)
	{
	  return -1;
	}
      // Create ramdisk dir
      snprintf(command, COMMAND_SIZE, "mkdir /media/ramdisk");
      system(command);
      // map memory to ramdisk dir with ramfs file system
      snprintf(command, COMMAND_SIZE, "mount -t ramfs ramfs /media/ramdisk");
      system(command);
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
  m_last_data = new gps_data_t;
  int8_t ret = init ();
  if (ret == -1)
    {
      m_active = false;
    }
  else
    {
      m_active = true;
    }
}
std::vector<int8_t>
GPS::read_data ()
{
  std::vector<int8_t> data;
  if (m_active == true)
    {
      gps_data_t* raw_data = new gps_data_t;
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
	  raw_data->direction = 0;
	  raw_data->fix_mode = 0;
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
		  raw_data->speed = (tmp * DECIMAL_SHIFT_SPEED) / 5;
		}
	      else if (type == "Timestamp:")
		{
		  in >> raw_data->timestamp;
		}
	      else if (type == "Fix:")
		{
		  in >> raw_data->fix_mode;
		}
	      else if (type == "Direction:")
		{
		  in >> raw_data->direction;
		}
	    }

	  int8_t* tmp_latitude = new int8_t[4];
	  int8_t* tmp_longitude = new int8_t[4];
	  int8_t* tmp_speed = new int8_t[2];
	  int8_t* tmp_direction = new int8_t[2];
	  int8_t* tmp_timestamp = new int8_t[4];
	  tmp_latitude = IntConverter::int32_to_int8 (raw_data->latitude);
	  tmp_longitude = IntConverter::int32_to_int8 (raw_data->longitude);
	  tmp_speed = IntConverter::int16_to_int8 (raw_data->speed);
	  tmp_direction = IntConverter::int16_to_int8 (raw_data->direction);
	  tmp_timestamp = IntConverter::int32_to_int8 (raw_data->timestamp);

	  m_last_data->fix_mode = raw_data->fix_mode;
	  m_last_data->longitude = raw_data->longitude;
	  m_last_data->latitude = raw_data->latitude;
	  m_last_data->speed = raw_data->speed;
	  m_last_data->direction = raw_data->direction;
	  m_last_data->timestamp = raw_data->timestamp;

	  data.push_back (raw_data->fix_mode);
	  for (int8_t i = 0; i < 4; i++)
	    {
	      data.push_back (tmp_latitude[i]);
	    }
	  for (int8_t i = 0; i < 4; i++)
	    {
	      data.push_back (tmp_longitude[i]);
	    }
	  for (int8_t i = 0; i < 2; i++)
	    {
	      data.push_back (tmp_speed[i]);
	    }
	  for (int8_t i = 0; i < 2; i++)
	    {
	      data.push_back (tmp_direction[i]);
	    }
	  for (int8_t i = 0; i < 4; i++)
	    {
	      data.push_back (tmp_timestamp[i]);
	    }
#ifdef _DEBUG
	  int8_t fix = data[0];
	  int8_t* test_latitude = new int8_t[4];
	  test_latitude[0] = data[1];
	  test_latitude[1] = data[2];
	  test_latitude[2] = data[3];
	  test_latitude[3] = data[4];
	  int8_t* test_longitude = new int8_t[4];
	  test_longitude[0] = data[5];
	  test_longitude[1] = data[6];
	  test_longitude[2] = data[7];
	  test_longitude[3] = data[8];
	  int8_t* test_speed = new int8_t[2];
	  test_speed[0] = data[9];
	  test_speed[1] = data[10];
	  int8_t* test_direction = new int8_t[2];
	  test_direction[0] = data[11];
	  test_direction[1] = data[12];
	  int8_t* test_timestamp = new int8_t[4];
	  test_timestamp[0] = data[13];
	  test_timestamp[1] = data[14];
	  test_timestamp[2] = data[15];
	  test_timestamp[3] = data[16];
	  int32_t latitude = IntConverter::int8_to_int32(test_latitude);
	  int32_t longitude = IntConverter::int8_to_int32(test_longitude);
	  int16_t speed = IntConverter::int8_to_int16(test_speed);
	  int16_t direction = IntConverter::int8_to_int16(test_direction);
	  int32_t timestamp = IntConverter::int8_to_int32(test_timestamp);
	  delete[] test_latitude;
	  delete[] test_longitude;
	  delete[] test_speed;
	  delete[] test_direction;
	  delete[] test_timestamp;
	  std::cout << "Fix raw: " << raw_data->fix_mode << std::endl;
	  std::cout << "Latitude raw: " << raw_data->latitude << std::endl;
	  std::cout << "Longitude raw: " << raw_data->longitude << std::endl;
	  std::cout << "Speed raw: " << raw_data->speed << std::endl;
	  std::cout << "Direction raw: " << raw_data->direction << std::endl;
	  std::cout << "Timestamp raw: " << raw_data->timestamp << std::endl;
	  std::cout << "Fix: " << fix << std::endl;
	  std::cout << "Latitude data: " << latitude << std::endl;
	  std::cout << "Longitude data: " << longitude << std::endl;
	  std::cout << "Speed data: " << speed << std::endl;
	  std::cout << "Direction data: " << direction << std::endl;
	  std::cout << "Timestamp data: " << timestamp << std::endl;
	  std::cout << "GPS Read End" << std::endl;
#endif
	  delete[] tmp_latitude;
	  delete[] tmp_longitude;
	  delete[] tmp_speed;
	  delete[] tmp_timestamp;
	  delete[] tmp_direction;
	  delete[] raw_data;
	}
    }
  return data;
}
GPS::~GPS ()
{
}

