#ifndef DEVICES_DEVICE_MANAGER_H_
#define DEVICES_DEVICE_MANAGER_H_
#include <map>
#include <vector>
#include "../communication/protocol_engine.h"
#include "../interfaces/interface.h"
#include "device.h"
#include "accelerometer.h"
#include "anemometer.h"
#include "compass.h"
#include "gps.h"
#include "gyroscope.h"
#include "hygrometer.h"
#include "serial_link.h"
#include "servo_motor.h"
#include "weston_anemometer.h"
#include "wind_vane.h"
#include <iostream>
#include <fstream>

/**
 * @file
 * @class DeviceManager
 * @brief Class for the Device Manager. Administrates all devices and returns devices for special usage.
 * @author Rene Kremer
 * @version 0.3
 */
class DeviceManager
{
  /**
   * @private
   */
private:
  /**
   * Vector of Devices
   */
  std::vector<std::shared_ptr<Device>> m_devices;
  /**
   * Inits the Sensors
   * @param protocol_engine is the ProtocolEngine for the communication
   * @param devices is a vector of ComponentDescriptor
   * @return on succes 1, otherwise -1
   */
  int8_t
  init_sensors (ProtocolEngine* protocol_engine, std::vector<uint8_t> devices);
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param protocol_engine is the ProtocolEngine for the communication
   * @param descriptor_bytes is a vector of multiple 3 byte uint8_t values
   * These 3 values together are one ComponentDescriptor in it's raw form
   */
  DeviceManager (ProtocolEngine* protocol_engine,
		 std::vector<uint8_t> descriptor_bytes);
  /**
   * Gets a single device
   * @param descriptor is a enum of a ComponentDescriptor to get the right device.
   * @return a pointer to the device
   */
  std::shared_ptr<Device>
  get_device (ComponentDescriptorEnum descriptor);
  /**
   * Destructor
   */
  ~DeviceManager ();
};

#endif /* DEVICES_DEVICE_MANAGER_H_ */
