#ifndef DEVICES_DESCRIPTOR_H_
#define DEVICES_DESCRIPTOR_H_

/**
 * @file
 * @class Descriptor
 * @brief Enum of a descriptor of a Device.
 * @details
 * <ul>
 * <li> ACCELEROMETER ( = 0) - Descriptor of the accelerometer </li>
 * <li> COMPASS ( = 1) - Descriptor of the compass </li>
 * <li> GPS ( = 2) - Descriptor of the gps </li>
 * <li> GYROSCOPE ( = 3) - Descriptor of the gyroscope </li>
 * <li> HYGROMETER ( = 4) - Descriptor of the hygrometer </li>
 * <li> WIND_SENSOR ( = 5) - Descriptor of the windsensor  </li>
 * <li> SERIAL_LINK        - Descriptor of the Serial Link </li>
 * <li> SAIL		   - Descriptor of the Sail </li>
 * <li> RUDDER		   - Descriptor of the Rudder </li>
 * <li> NUM_DEVICES ( = 6) - Enum for the number of devices to iterate over it in loops </li>
 * </ul>
 * @author Rene Kremer
 * @version 0.3
 */
enum class Descriptor
{
  /**
   * Descriptor of the accelerometer ( = 0x)
   */
  ACCELEROMETER,
  /**
   * Descriptor of the anemomoeter ( = 0x)
   */
  ANEMOMETER,
  /**
   * Descriptor of the compass ( = 0x)
   */
  COMPASS,
  /**
   * Descriptor of the gps ( = 0x)
   */
  GPS,
  /**
   * Descriptor of the gyroscope ( = 0x)
   */
  GYROSCOPE,
  /**
   * Descriptor of the hygrometer ( = 0x)
   */
  HYGROMETER,
  /**
   * Descriptor of the weston anemometer ( = 0x)
   */
  WESTON_ANEMOMETER,
  /**
   * Descriptor of the wind vane ( = 0x)
   */
  WIND_VANE,
  /**
   * Descriptor of the Serial Link ( = 0x)
   */
  SERIAL_LINK,
  /**
   * Descriptor of the Sail ( = 0x)
   */
  SAIL,
  /**
   * Descriptor of the Rudder ( = 0x)
   */
  RUDDER,
#ifdef _TEST
  TEENSY_I2C,
#endif
  /**
   * Enum for the number of devices to iterate over it in loops ( = 6)
   */
  NUM_DEVICES
};



#endif /* DEVICES_DESCRIPTOR_H_ */
