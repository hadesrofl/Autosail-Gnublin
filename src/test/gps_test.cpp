#ifdef _TEST
#include "gps_test.h"

GPSTest::GPSTest ()
{
}

bool
GPSTest::test_cases ()
{
  std::cout << "---------------------------------" << std::endl;
  std::cout << "Starting GPS Test" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  Loader* loader = new Loader ();
  GPS* gps = dynamic_cast<GPS*>(&(*(loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::GPS_POSITION))));
  std::vector<int8_t> data;
  uint8_t i = 0;
  if (gps->is_active () == true)
    {
      while (i != 5)
	{
	  std::cout << "\nTest: " << static_cast<int32_t> (i) << std::endl;
	  i++;
	  data = gps->read_data ();
	  int8_t fix = data[0];
	  int8_t* test_latitude = new int8_t[4];
	  test_latitude[0] = data[1];
	  test_latitude[1] = data[2];
	  test_latitude[2] = data[3];
	  test_latitude[3] = data[4];
	  int8_t* test_longitude = new int8_t[4];
	  test_longitude[0] = data[5];
	  test_longitude[1] = data[6];
	  test_longitude[2] = data[7];
	  test_longitude[3] = data[8];
	  int8_t* test_speed = new int8_t[2];
	  test_speed[0] = data[9];
	  test_speed[1] = data[10];
	  int8_t* test_direction = new int8_t[2];
	  test_direction[0] = data[11];
	  test_direction[1] = data[12];
	  int8_t* test_timestamp = new int8_t[4];
	  test_timestamp[0] = data[13];
	  test_timestamp[1] = data[14];
	  test_timestamp[2] = data[15];
	  test_timestamp[3] = data[16];
	  int32_t latitude = IntConverter::int8_to_int32 (test_latitude);
	  int32_t longitude = IntConverter::int8_to_int32 (test_longitude);
	  int16_t speed = IntConverter::int8_to_int16 (test_speed);
	  int16_t direction = IntConverter::int8_to_int16 (test_direction);
	  int32_t timestamp = IntConverter::int8_to_int32 (test_timestamp);
	  delete[] test_latitude;
	  delete[] test_longitude;
	  delete[] test_speed;
	  delete[] test_direction;
	  delete[] test_timestamp;
	  std::cout << "Fix: " << fix << std::endl;
	  std::cout << "Latitude data: " << latitude << std::endl;
	  std::cout << "Longitude data: " << longitude << std::endl;
	  std::cout << "Speed data: " << speed << std::endl;
	  std::cout << "Direction data: " << direction << std::endl;
	  std::cout << "Timestamp data: " << timestamp << std::endl;
	}
      return true;
    }
  else
    {
      return false;
    }
}

GPSTest::~GPSTest ()
{
}
#endif
