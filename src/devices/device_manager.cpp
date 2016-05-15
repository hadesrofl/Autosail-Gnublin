#include "device_manager.h"

DeviceManager::DeviceManager () :
    m_protocol (new TLVEProtocol ())
{
  init_sensors ();
}

int
DeviceManager::get_data ()
{
  for (int i = static_cast<int> (Device_ID::ACCELEROMETER);
      i < static_cast<int> (Device_ID::NUM_DEVICES); i++)
    {
      Device* device;
      std::vector<Sensor_Value> device_values;
      device = get_sensor (static_cast<Device_ID> (i));
      if (device != NULL)
	{
	  Device_ID id = static_cast<Device_ID> (device->get_device_id ());
	  unsigned char* data;
	  switch (id)
	    {
	    case Device_ID::ACCELEROMETER:
	      {
		//TODO: Call Read Method of Accelerometer for Sensor Data
		data = device->read_data();

		break;
	      }
	    case Device_ID::COMPASS:
	      {
		data = NULL;
		break;
	      }
	    case Device_ID::GPS:
	      {
		data = NULL;
		break;
	      }
	    case Device_ID::GYROSCOPE:
	      {
		data = NULL;
		break;
	      }
	    case Device_ID::HYGROMETER:
	      {
		data = NULL;
		break;
	      }
	    case Device_ID::WIND_SENSOR:
	      {
		data = NULL;
		break;
	      }
	    case Device_ID::NUM_DEVICES:
	      {
		data = NULL;
		return -1;
	      }
#ifdef _TEST
	      case Device_ID::TEENSY_I2C:
		{
		  data = NULL;
		  break;}
#endif
	    default:
	      data = NULL;
	      return -1;
	    }
	}
    }
  return 0;
}

unsigned char*
DeviceManager::copy_data (unsigned char* src, int length)
{
  unsigned char* target = new unsigned char[length];
  for (int i = 0; i < length; i++)
    {
      target[i] = src[i];
    }
  delete[] src;
  return target;
}

int
DeviceManager::init_sensors ()
{
  m_devices.insert (
      std::make_pair (
	  Device_ID::ACCELEROMETER,
	  std::unique_ptr<Accelerometer> (
	      new Accelerometer (static_cast<int> (Sensor_Param::ACC_ADDR), Sensor_Param::ACC_RANGE_2G))));
  m_devices.insert (
      std::make_pair (
	  Device_ID::COMPASS,
	  std::unique_ptr<Compass> (
	      new Compass (static_cast<int> (Sensor_Param::COMPASS_ADDR)))));
  m_devices.insert (
      std::make_pair (
	  Device_ID::GPS,
	  std::unique_ptr<GPS> (
	      new GPS (static_cast<int> (Sensor_Param::GPS_BAUD)))));
  m_devices.insert (
      std::make_pair (
	  Device_ID::GYROSCOPE,
	  std::unique_ptr<Gyroscope> (
	      new Gyroscope (static_cast<int> (Sensor_Param::GYRO_ADDR)))));
  //m_devices.insert(std::make_pair(Sensor::HYGROMETER, std::unique_ptr<Hygrometer> (new Hygrometer(static_cast<int>(Sensor_Params::HYGRO_ADDR)))));
  //m_devices.insert(std::make_pair(Sensor::WIND_SENSOR, std::unique_ptr<WindSensor> (new WindSensor(static_cast<int>(Sensor_Params::WIND_SENSOR_ADDR)))));

  return 0;
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

int
DeviceManager::read_spi (unsigned char* buf, int length)
{
  return 0;
}

DeviceManager::~DeviceManager ()
{
  m_data_map.clear ();
  m_devices.clear ();
}

