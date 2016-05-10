#include <utility>
#include "device_manager.h"

DeviceManager::DeviceManager() : m_protocol(new TLVEProtocol()){
  init_sensors();
}

int DeviceManager::get_data(){
  return 0;
}

int DeviceManager::init_sensors(){
  m_devices.insert(std::make_pair(Sensor::ACCELEROMETER, std::unique_ptr<Accelerometer> (new Accelerometer((int) Sensor_Addr::ACC_I2C))));
  return 0;
}

Device* DeviceManager::get_sensor(Sensor s){
  Device* dptr = NULL;
  if(m_devices.count(s)>0){
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



