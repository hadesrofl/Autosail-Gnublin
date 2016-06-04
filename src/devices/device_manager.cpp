#include "device_manager.h"

//Public Functions

DeviceManager::DeviceManager ()
{
  std::vector<Descriptor> descriptors;
  ConfReader* reader = new ConfReader (DEVICE_CONFIG);
  descriptors = reader->get_descriptors();
  if (descriptors.empty() == false)
    {
      init_sensors (descriptors);
    }
  delete reader;
  descriptors.clear();
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
DeviceManager::init_sensors (std::vector<Descriptor> descriptors)
{
  for (uint32_t i = 0; i < descriptors.size (); i++)
    {
      Descriptor id = descriptors.at (i);
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
