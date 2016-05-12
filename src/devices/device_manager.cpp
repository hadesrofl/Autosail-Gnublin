#include <utility>
#include "device_manager.h"

DeviceManager::DeviceManager() : m_protocol(new TLVEProtocol()){
  init_sensors();
}

int DeviceManager::get_data(){
  //Device device;
  for(int i = static_cast<int>(Sensor::ACCELEROMETER); i < static_cast<int>(Sensor::NUM_DEVICES); i++){
      if(m_devices.count(static_cast<Sensor>(i)) > 0){
	  //device = m_devices.at(static_cast<Sensor>(i));
      }
     // if(device != NULL){
     //}

  }
  return 0;
}

int DeviceManager::init_sensors(){
  m_devices.insert(std::make_pair(Sensor::ACCELEROMETER, std::unique_ptr<Accelerometer> (new Accelerometer(static_cast<int>(Sensor_Params::ACC_ADDR)))));
  m_devices.insert(std::make_pair(Sensor::COMPASS, std::unique_ptr<Compass> (new Compass(static_cast<int>(Sensor_Params::COMPASS_ADDR)))));
  m_devices.insert(std::make_pair(Sensor::GPS, std::unique_ptr<GPS> (new GPS(static_cast<int>(Sensor_Params::GPS_BAUD)))));
  m_devices.insert(std::make_pair(Sensor::GYROSCOPE, std::unique_ptr<Gyroscope> (new Gyroscope(static_cast<int>(Sensor_Params::GYRO_ADDR)))));
  //m_devices.insert(std::make_pair(Sensor::HYGROMETER, std::unique_ptr<Hygrometer> (new Hygrometer(static_cast<int>(Sensor_Params::HYGRO_ADDR)))));
  //m_devices.insert(std::make_pair(Sensor::WIND_SENSOR, std::unique_ptr<WindSensor> (new WindSensor(static_cast<int>(Sensor_Params::WIND_SENSOR_ADDR)))));



  return 0;
}

Device* DeviceManager::get_sensor(Sensor s){
  Device* dptr = NULL;
  if(m_devices.count(s) > 0){
      dptr = &(*m_devices.at(s));
  }
 return dptr;
}

int DeviceManager::read_spi(){
  return 0;
}

DeviceManager::~DeviceManager(){
  m_data_map.clear();
  m_devices.clear();
}



