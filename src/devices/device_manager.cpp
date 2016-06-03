#include "device_manager.h"

//Public Functions

DeviceManager::DeviceManager ()
{
  Descriptor devices[static_cast<int> (Descriptor::NUM_DEVICES)];
  if ((read_config (DEVICE_CONFIG, devices)) > 0)
    {
      init_sensors (devices);
    }
}

Device*
DeviceManager::get_sensor (Descriptor id)
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
DeviceManager::init_sensors (Descriptor devices[])
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
      Descriptor id = static_cast<Descriptor> (tmp);
      switch (id)
	{
	case Descriptor::ACCELEROMETER:
	  m_devices.insert (
	      std::make_pair (
		  Descriptor::ACCELEROMETER,
		  std::unique_ptr<Accelerometer> (
		      new Accelerometer (
			  new I2CParameter (
			      static_cast<uint8_t> (Device_Config::ACC_ADDR)),
			  Device_Config::ACC_RANGE_2G))));

	  std::cout << "Accelerometer DONE!" << std::endl;
	  break;
	case Descriptor::ANEMOMETER:
	  // TODO: Create Object
	  break;
	case Descriptor::COMPASS:
	  m_devices.insert (
	      std::make_pair (
		  Descriptor::COMPASS,
		  std::unique_ptr<Compass> (
		      new Compass (
			  new I2CParameter (
			      static_cast<int> (Device_Config::COMPASS_ADDR)),
			  Device_Config::COMPASS_GAIN_DEFAULT))));

	  std::cout << "Compass DONE!" << std::endl;
	  break;
	case Descriptor::GPS:
	  m_devices.insert (
	      std::make_pair (
		  Descriptor::GPS,
		  std::unique_ptr<GPS> (
		      new GPS (
			  new SerialParameter (
			      static_cast<int> (Device_Config::GPS_BAUD))))));
	  std::cout << "GPS DONE!" << std::endl;
	  break;
	case Descriptor::GYROSCOPE:
	  m_devices.insert (
	      std::make_pair (
		  Descriptor::GYROSCOPE,
		  std::unique_ptr<Gyroscope> (
		      new Gyroscope (
			  new I2CParameter (
			      static_cast<int> (Device_Config::GYRO_ADDR))))));
	  std::cout << "Gyroscope DONE!" << std::endl;
	  break;
	case Descriptor::HYGROMETER:
	  // TODO: Create Object
	  //m_devices.insert(std::make_pair(Sensor::HYGROMETER, std::unique_ptr<Hygrometer> (new Hygrometer(static_cast<int>(Sensor_Params::HYGRO_ADDR)))));
	  break;
	case Descriptor::WESTON_ANEMOMETER:
	  // TODO: Create Object
	  //m_devices.insert(std::make_pair(Sensor::WIND_SENSOR, std::unique_ptr<WindSensor> (new WindSensor(static_cast<int>(Sensor_Params::WIND_SENSOR_ADDR)))));
	  break;
	case Descriptor::WIND_VANE:
	  // TODO: Create Object
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
DeviceManager::read_config (const char* file, Descriptor devices[])
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
