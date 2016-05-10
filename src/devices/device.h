#ifndef DEVICES_DEVICE_H_
#define DEVICES_DEVICE_H_

#include "../interfaces/interface.h"

class Device{
protected:
  std::unique_ptr<Interface> m_interface_port;
};



#endif /* DEVICES_DEVICE_H_ */
