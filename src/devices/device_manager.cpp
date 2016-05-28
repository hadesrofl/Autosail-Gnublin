#include "device_manager.h"

//Public Functions

DeviceManager::DeviceManager ()
{
  Device_ID devices[static_cast<int> (Device_ID::NUM_DEVICES)];
  if ((read_config (DEVICE_CONFIG, devices)) > 0)
    {
      init_sensors (devices);
    }
}

Device*
DeviceManager::get_sensor (Device_ID id)
{
  Device* dptr = NULL;
  if (m_devices.count (id) > 0)
    {
      dptr = &(*m_devices.at (id));
    }
  return dptr;
}

DeviceManager::~DeviceManager ()
{
  m_devices.clear ();
}

// Private Functions

int8_t
DeviceManager::init_sensors (Device_ID devices[])
{
  uint16_t tmp, j;
  // i = i + 2 to skip the name of the device and go to the id
  for (uint32_t i = 0; i < m_config_values.size (); i = i + 2)
    {
      tmp = 0;
      j = 0;
      while (m_config_values[i + 1][j] != '\0')
	{
	  tmp = (tmp * DECIMAL_SHIFT)
	      + static_cast<int16_t> (m_config_values[i + 1][j] - ASCII_SHIFT);
	  j++;
	}
      Device_ID id = static_cast<Device_ID> (tmp);
      switch (id)
	{
	case Device_ID::ACCELEROMETER:
	  m_devices.insert (
	      std::make_pair (
		  Device_ID::ACCELEROMETER,
		  std::unique_ptr<Accelerometer> (
		      new Accelerometer (
			  static_cast<int> (Sensor_Param::ACC_ADDR),
			  Sensor_Param::ACC_RANGE_2G))));
	  std::cout << "Accelerometer DONE!" << std::endl;
	  break;
	case Device_ID::COMPASS:
	  m_devices.insert (
	      std::make_pair (
		  Device_ID::COMPASS,
		  std::unique_ptr<Compass> (
		      new Compass (
			  static_cast<int> (Sensor_Param::COMPASS_ADDR)))));
	  std::cout << "Compass DONE!" << std::endl;
	  break;
	case Device_ID::GPS:
	  m_devices.insert (
	      std::make_pair (
		  Device_ID::GPS,
		  std::unique_ptr<GPS> (
		      new GPS (static_cast<int> (Sensor_Param::GPS_BAUD)))));
	  break;
	case Device_ID::GYROSCOPE:
	  m_devices.insert (
	      std::make_pair (
		  Device_ID::GYROSCOPE,
		  std::unique_ptr<Gyroscope> (
		      new Gyroscope (
			  static_cast<int> (Sensor_Param::GYRO_ADDR)))));
	  break;
	case Device_ID::HYGROMETER:
	  //m_devices.insert(std::make_pair(Sensor::HYGROMETER, std::unique_ptr<Hygrometer> (new Hygrometer(static_cast<int>(Sensor_Params::HYGRO_ADDR)))));
	  break;
	case Device_ID::WIND_SENSOR:

	  //m_devices.insert(std::make_pair(Sensor::WIND_SENSOR, std::unique_ptr<WindSensor> (new WindSensor(static_cast<int>(Sensor_Params::WIND_SENSOR_ADDR)))));
	  break;
	default:
	  std::cerr << "False ID!" << std::endl;
	  break;
	}
    }
  return 1;
}

int8_t
DeviceManager::store_line (uint8_t* value, uint16_t value_length)
{
  uint8_t* stored_value = new uint8_t[value_length];
  for (uint16_t i = 0; i < value_length; i++)
    {
      stored_value[i] = value[i];
    }
  m_config_values.push_back (stored_value);
  return 1;
}

int8_t
DeviceManager::read_config (const char* file, Device_ID devices[])
{
  std::ifstream input;
  uint8_t length = 50;
  uint16_t value_length = 0;
  bool equals_seen = false;
  uint8_t* value = new uint8_t[length];
  char temp_c;

  input.open (file);
  if (input.is_open () == true)
    {
      while (input.eof () == false)
	{
	  input.get (temp_c);
	  if (temp_c == '\n')
	    {
	      if (array_is_empty (value, value_length) == false)
		{
		  store_line (value, value_length);
		  clear_array (value, value_length);
		  value_length = 0;
		}
	      equals_seen = false;
	    }
	  if (!(isspace (temp_c)) && temp_c != 0)
	    {
	      if (equals_seen == false)
		{
		  if (temp_c == '=')
		    {
		      equals_seen = true;
		    }
		}
	      else
		{
		  value[value_length] = temp_c;
		  value_length++;
		}
	    }
	}
      equals_seen = false;
      input.close ();
    }
  else
    {
      std::cout << "Error while opening file!" << std::endl;
      delete[] value;
      return -1;
    }
  delete[] value;
  return 1;
}

uint16_t
DeviceManager::clear_array (uint8_t array[], uint16_t length)
{
  for (int16_t i = 0; i < length; i++)
    {
      array[i] = 0;
    }
  return length;
}

bool
DeviceManager::array_is_empty (uint8_t array[], uint16_t length)
{
  for (uint16_t i = 0; i < length; i++)
    {
      if (array[i] != 0)
	{
	  return false;
	}
    }
  return true;
}
