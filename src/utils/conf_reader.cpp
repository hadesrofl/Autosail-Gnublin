#include "conf_reader.h"

ConfReader::ConfReader ()
{
  m_file = FW_CONFIG;
  read_config ();
}

ConfReader::ConfReader (const char* file_name)
{
  m_file = file_name;
  read_config ();
}
int8_t
ConfReader::read_config ()
{
  std::ifstream source;
  source.open (FW_CONFIG, std::ios_base::in);
  bool stream_controller, autopilot;
  stream_controller = false;
  autopilot = false;
  if (source.is_open ())
    {
      std::string line;
      while (std::getline (source, line))
	{
	  uint16_t tmp;
	  std::istringstream in (line);
	  std::string type;
	  in >> type;
	  if (type == "Boat-ID:")
	    {
	      in >> std::hex >> tmp;
	      m_boat_id = tmp;
	    }
	  else if (type == "Protocol:")
	    {
	      in >> std::hex >> tmp;
	      m_protocol_config.push_back (tmp);
	    }
	  else if (type == "Version:")
	    {
	      // Major Number
	      in >> tmp;
	      m_protocol_config.push_back (tmp);
	      // First Minor Number
	      in >> tmp;
	      m_protocol_config.push_back (tmp);
	      // Second Minor Number
	      in >> tmp;
	      m_protocol_config.push_back (tmp);
	    }
	  else if (type == "Component:")
	    {
	      std::string name;
	      in >> name;
	      if (name == "Stream-Controlling-Unit")
		{
		  stream_controller = true;
		  autopilot = false;
		}
	      else if (name == "Autopilot")
		{
		  stream_controller = false;
		  autopilot = true;
		}
	      else
		{
		  autopilot = false;
		  stream_controller = false;
		}
	    }
	  else if (stream_controller == true)
	    {
	      if (type == "Component-Class:")
		{
		  in >> std::hex >> tmp;
		  m_stream_generator_config.push_back (tmp);
		}
	      else if (type == "Component-Attribute:")
		{
		  in >> std::hex >> tmp;
		  m_stream_generator_config.push_back (tmp);
		}
	      else if (type == "Component-Number:")
		{
		  in >> std::hex >> tmp;
		  m_stream_generator_config.push_back (tmp);
		}
	      else if (type == "Communication-Number:")
		{
		  in >> std::hex >> tmp;
		  m_stream_generator_config.push_back (tmp);
		}
	      else if (type == "Config:")
		{
		  in >> std::hex >> tmp;
		  m_stream_generator_config.push_back (tmp);
		}
	    }
	  else if (autopilot == true)
	    {
	      if (type == "Component-Class:")
		{
		  in >> std::hex >> tmp;
		  m_autopilot_config.push_back (tmp);
		}
	      else if (type == "Component-Attribute:")
		{
		  in >> std::hex >> tmp;
		  m_autopilot_config.push_back (tmp);
		}
	      else if (type == "Component-Number:")
		{
		  in >> std::hex >> tmp;
		  m_autopilot_config.push_back (tmp);
		}
	      else if (type == "Communication-Number:")
		{
		  in >> std::hex >> tmp;
		  m_autopilot_config.push_back (tmp);
		}
	      else if (type == "Config:")
		{
		  in >> std::hex >> tmp;
		  m_autopilot_config.push_back (tmp);
		}
	    }
	  else if (type == "Component-Class:")
	    {
	      in >> std::hex >> tmp;
	      m_device_configs.push_back (tmp);
	    }
	  else if (type == "Component-Attribute:")
	    {
	      in >> std::hex >> tmp;
	      m_device_configs.push_back (tmp);
	    }
	  else if (type == "Component-Number:")
	    {
	      in >> std::hex >> tmp;
	      m_device_configs.push_back (tmp);
	    }
	  else if (type == "Communication-Number:")
	    {
	      in >> std::hex >> tmp;
	      m_device_configs.push_back (tmp);
	    }
	  else if (type == "Config:")
	    {
	      in >> std::hex >> tmp;
	      m_device_configs.push_back (tmp);
	    }
	}
      return 1;
    }
  return -1;
}

