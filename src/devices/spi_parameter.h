#ifndef DEVICES_SPI_PARAMETER_H_
#define DEVICES_SPI_PARAMETER_H_

#include "device_config.h"

/**
 * Default SPI Device of the Gnublin
 */
#define GNUBLIN_DEFAULT_SPI "/dev/spidev0.0"

/**
 * @file
 * @class SPIParameter
 * @ingroup Devices
 * @brief Class for Parameters of SPI Devices. Contains the SPI Mode, Speed and LSB for the SPIMasterSelect Interface.
 * @version 0.35
 */
class SPIParameter : virtual public InterfaceParameter
{
  /**
   * @private
   */
private:
  /**
   * Mode of the SPI Interface
   */
  uint8_t m_mode;
  /**
   * Speed of the serial interface (in Hertz)
   */
  uint32_t m_speed;
  /**
   * Boolean to determine if the interface is set to LSB or MSB
   */
  bool m_lsb;
  /**
   * Distinguishes between different DeviceConfigs. Sets 1Mhz on default, if the
   * config does not apply to one SPI_SPEED specified in DeviceConfig
   * @param config is a DeviceConfig Enum.
   * @return the speed for the spi
   */
  uint32_t
  distinguish_speed (DeviceConfig config)
  {
    switch (config)
      {
      case DeviceConfig::SPI_SPEED_1MHZ:
	return 1000 * 1000;
	break;
      default:
	return 1000 * 1000;
      }
  }
  /**
   * @protected
   */
protected:
  /**
   * @public
   */
public:
  /**
   * Constructor for a SPI Parameter
   * @param device_file is the file of the device in linux
   * @param mode is the mode of the SPI Interface
   * @param speed is the speed of the SPI Interface as DeviceConfig Enum
   * @param lsb to determine if the SPI Interface is set to LSB or MSB
   */
  SPIParameter (char* device_file, uint8_t mode, DeviceConfig speed, bool lsb)
  {
    m_device_file = device_file;
    m_mode = mode;
    m_speed = distinguish_speed (speed);
    m_lsb = lsb;
  }
  /**
   * Constructor for a SPI Parameter (called with default device file of gnublin)
   * @param mode is the mode of the SPI Interface
   * @param speed is the speed of the SPI Interface as DeviceConfig Enum
   * @param lsb to determine if the SPI Interface is set to LSB or MSB
   */
  SPIParameter (uint8_t mode, DeviceConfig speed, bool lsb)
  {
    m_device_file = (char*) GNUBLIN_DEFAULT_SPI;
    m_mode = mode;
    m_speed = distinguish_speed (speed);
    m_lsb = lsb;
  }
  /**
   * Getter for the mode of the SPI Interface
   * @return the mode of the SPI Interface
   */
  inline uint8_t
  get_mode () const
  {
    return m_mode;
  }
  /**
   * Getter for the speed of the SPI Interface
   * @return the speed of the SPI Interface
   */
  inline uint16_t
  get_speed () const
  {
    return m_speed;
  }
  /**
   * Getter for the lsb of the SPI Interface
   * @return the lsb of the SPI Interface
   */
  inline bool
  get_lsb () const
  {
    return m_lsb;
  }
};

#endif /* DEVICES_SPI_PARAMETER_H_ */
