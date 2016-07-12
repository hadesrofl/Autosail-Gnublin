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
      // TODO: Test without starting GPSd in App but in shell for timing purposes
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
  init ();
}
uint8_t*
GPS::read_data ()
{
  return NULL;
}
int8_t
GPS::read_data (gps_data_t *data)
{
  char command[COMMAND_SIZE];
  snprintf (command, COMMAND_SIZE, "./%s >> %s", SUB_PROGRAM, TMP_DATA_FILE);
  std::ifstream source;
  system (command);
  source.open (TMP_DATA_FILE, std::ios_base::in);
  if (!source)
    {
#ifdef _DEBUG
      std::cerr << "Can't open file!" << std::endl;
#endif
      data->latitude = 0;
      data->longitude = 0;
      data->timestamp.tv_sec = 0;
      data->speed = 0;
      return -1;
    }
  else
    {
      for (std::string line; std::getline (source, line);)
	{
	  std::istringstream in (line);
	  std::string type;
	  in >> type;

	  if (type == "Latitude:")
	    {
	      in >> data->latitude;
	    }
	  else if (type == "Longitude:")
	    {
	      in >> data->longitude;
	    }
	  else if (type == "Speed:")
	    {
	      in >> data->speed;
	    }
	  else if (type == "Timestamp:")
	    {
	      in >> data->timestamp.tv_sec;
	    }
	}
#ifdef _DEBUG
      std::cout << "Latitude: " << data->latitude << std::endl;
      std::cout << "Longitude: " << data->longitude << std::endl;
      std::cout << "Speed: " << data->speed << std::endl;
      std::cout << "Timestamp: " << data->timestamp.tv_sec << std::endl;
#endif
      return 1;
    }
}
GPS::~GPS ()
{
}

