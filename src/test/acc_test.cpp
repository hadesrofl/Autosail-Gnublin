#ifdef _TEST
#include "acc_test.h"

AccTest::AccTest ()
{
}
void
AccTest::eval ()
{
  Loader* loader = new Loader ();
  std::shared_ptr<Device> accelerometer = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::ACCELEROMETER);
  std::vector<int8_t> data;
  uint16_t i = 0;
  timeval begin, end;
  std::cout
      << "Start Read Seconds;Start Read Milliseconds;End Read Seconds;End Read Milliseconds;Difference;"
      << std::endl;
  while (i != 1000)
    {
      i++;
      gettimeofday (&begin, 0);
      data = accelerometer->read_data ();
      gettimeofday (&end, 0);
      std::cout << (begin.tv_sec) << ";" << (begin.tv_usec) / 1000 << ";"
	  << (end.tv_sec) << ";" << (end.tv_usec) / 1000 << ";"
	  << (end.tv_sec - begin.tv_sec) * 1000
	      + (end.tv_usec - begin.tv_usec) / 1000 << ";" << std::endl;
    }
}
bool
AccTest::test_cases ()
{
  std::cout << "---------------------------------" << std::endl;
  std::cout << "Starting Accelerometer Test" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  Loader* loader = new Loader ();
  std::shared_ptr<Device> accelerometer =
      loader->get_device_manager ()->get_device (
	  ComponentDescriptorEnum::ACCELEROMETER);
  std::vector<int8_t> data;
  uint8_t i = 0;
  while (i != 5)
    {
      std::cout << "\nTest: " << static_cast<int32_t>(i) << std::endl;
      i++;
      data = accelerometer->read_data ();
      int8_t msb_x, lsb_x, msb_y, lsb_y, msb_z, lsb_z;
      msb_x = data.at (0);
      lsb_x = data.at (1);
      msb_y = data.at (2);
      lsb_y = data.at (3);
      msb_z = data.at (4);
      lsb_z = data.at (5);
      // combine two unsigned chars into one int16_t
      int16_t tsb_x = (msb_x << 8) | lsb_x;
      int16_t tsb_y = (msb_y << 8) | lsb_y;
      int16_t tsb_z = (msb_z << 8) | lsb_z;
      // Calculate the speed of the axis with reference to G = 9.81 m / s^2
      float accel_meter_x = tsb_x * MG_SPEED;
      float accel_meter_y = tsb_y * MG_SPEED;
      float accel_meter_z = tsb_z * MG_SPEED;
      std::cout << "X-Axis in mG (MSB): " << static_cast<int32_t> (msb_x)
	  << std::endl;
      std::cout << "X-Axis in mG (LSB): " << static_cast<int32_t> (lsb_x)
	  << std::endl;
      std::cout << "Y-Axis in mG (MSB): " << static_cast<int32_t> (msb_y)
	  << std::endl;
      std::cout << "Y-Axis in mG (LSB): " << static_cast<int32_t> (lsb_y)
	  << std::endl;
      std::cout << "Z-Axis in mG (MSB): " << static_cast<int32_t> (msb_z)
	  << std::endl;
      std::cout << "Z-Axis in mG (LSB): " << static_cast<int32_t> (lsb_z)
	  << std::endl;
      std::cout << "X-Axis in mG as int16: " << static_cast<int16_t> (tsb_x)
	  << std::endl;
      std::cout << "Y-Axis in mG as int16: " << static_cast<int16_t> (tsb_y)
	  << std::endl;
      std::cout << "Z-Axis in mG as int16: " << static_cast<int16_t> (tsb_z)
	  << std::endl;
      std::cout << "X-Axis m/s^2: " << accel_meter_x << std::endl;
      std::cout << "Y-Axis m/s^2: " << accel_meter_y << std::endl;
      std::cout << "Z-Axis m/s^2: " << accel_meter_z << std::endl;
    }
  return true;
}

AccTest::~AccTest ()
{
}
#endif

