#ifndef DEVICES_GYROSCOPE_H_
#define DEVICES_GYROSCOPE_H_

#include "../interfaces/i2c.h"
#include "device.h"
#include "i2c_parameter.h"

/**
 * First Data Register
 */
#define GYRO_X_MSB_REGISTER 0x1D
/**
 * Register for DLPF Full Scale Config
 */
#define GYRO_DLPF_FS_REGISTER 0x16
/**
 * Value for FS_SEL = 3 (Range +-2000 deg/s), CFG = 3 (42Hz, 1kHz sample rate)
 *  CFG_0 = 1<<0;
 *  CFG_1 = 1<<1;
 *  FS_SEL_0 = 1<<3;
 *  FS_SEL_1 = 1<<4;
 */
#define GYRO_DLPF_FS_REGISTER_VALUE 0x1B
/**
 * Scaling factor to calculate LSB in degrees/second
 */
#define GYRO_SCALING_FACTOR 14.375

/**
 * @file
 * @class Gyroscope
 * @ingroup Devices
 * @brief Class for a Gyroscope Module . Uses a I2C Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.35
 */
class Gyroscope : virtual public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the gyroscope, setting the configuration for the device
   */
  int8_t
  init ();
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param interface_parameter are the parameters for the I2C Interface
   * @param descriptor is a pointer to the ComponentDescriptor of this device
   */
  Gyroscope (I2CParameter *interface_parameter, ComponentDescriptor* descriptor);
  /**
   * Reads the Data X, Y and Z Register of the Gyroscope and returns them as a
   * pointer with allocated memory.
   */
  std::vector<int8_t>
  read_data ();
  /**
   * Destructor
   */
  ~Gyroscope ();
};

#endif /* DEVICES_GYROSCOPE_H_ */
