#include "interface_manager.h"
#include "serial.h"
#include <utility>

InterfaceManager::InterfaceManager() : m_protocol(new TLVEProtocol()){
  m_interfaces.insert(std::make_pair((char*) "SerialPort", new Serial(enum_to_string(Device::SERIAL), 38400)));

}

int InterfaceManager::get_data(){
  return 0;
}

int InterfaceManager::init_sensors(){
  return 0;
}

int InterfaceManager::read_spi(){
  return 0;
}

char* InterfaceManager::enum_to_string(Device e){
  switch(e){
    case Device::SERIAL: return "/dev/ttyUSB0";
    default: return "";
  }
}

InterfaceManager::~InterfaceManager(){
  m_data_map.clear();
  m_interfaces.clear();
}



