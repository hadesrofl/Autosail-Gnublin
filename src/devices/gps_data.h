#ifndef GPS_DATA_H_
#define GPS_DATA_H_

#include <stdint.h>

/**
 * GPS has no fix
 */
#define GPS_NO_FIX 0x00
/**
 * GPS has 2D fix
 */
#define GPS_2D_FIX 0x01
/**
 * GPS has 3D fix
 */
#define GPS_3D_FIX 0x02

/**
 * @file
 * @class gps_data_t
 * @ingroup Devices
 * @brief Struct for a GPS data. Stores data from a gps update such as latitude, longitude,
 * speed and a timestamp. The timestamp is the systemtime of linux when the update
 * arrived.
 * @author Rene Kremer
 * @version 0.2
 */
struct gps_data_t
{
  /**
   * Mode of the fix (No Fix = 0x00, 2D = 0x01, 3D = 0x02)
   */
  int8_t fix_mode;
  /**
   * latitude of the position
   */
  int32_t latitude;
  /**
   * longitude of the position
   */
  int32_t longitude;
  /**
   * speed gained from the GPS device (5cm/s)
   */
  int16_t speed;
  /**
   * direction gained from the gps device
   */
  int16_t direction;
  /**
   * the time when the
   */
  uint32_t timestamp;
};

#endif /* GPS_DATA_H_ */
