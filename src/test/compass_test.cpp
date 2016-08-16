#ifdef _TEST
#include "compass_test.h"

CompassTest::CompassTest ()
{
}
void
CompassTest::eval ()
{
  Loader* loader = new Loader ();
  std::shared_ptr<Device> compass = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::COMPASS);
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
      data = compass->read_data ();
      gettimeofday (&end, 0);
      std::cout << (begin.tv_sec) << ";" << (begin.tv_usec) / 1000 << ";"
	  << (end.tv_sec) << ";" << (end.tv_usec) / 1000 << ";"
	  << (end.tv_sec - begin.tv_sec) * 1000
	      + (end.tv_usec - begin.tv_usec) / 1000 << ";" << std::endl;
    }
}
bool
CompassTest::test_cases ()
{
  std::cout << "---------------------------------" << std::endl;
  std::cout << "Starting Compass Test" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  Loader* loader = new Loader ();
  std::shared_ptr<Device> compass = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::COMPASS);
  std::vector<int8_t> data;
  uint8_t i = 0;
  while (i != 5)
    {
      std::cout << "\nTest: " << static_cast<int32_t>(i) << std::endl;
      i++;
      data = compass->read_data ();
      int8_t msb_x, lsb_x, msb_y, lsb_y, msb_z, lsb_z;
      int16_t x_gauss = (msb_x << 8) | lsb_x;
      int16_t y_gauss = (msb_y << 8) | lsb_y;
      int16_t z_gauss = (msb_z << 8) | lsb_z;
      float x_tesla = x_gauss / 10;
      float z_tesla = z_gauss / 10;
      float y_tesla = y_gauss / 10;
      std::cout << "X MSB: " << static_cast<int> (msb_x) << " " << std::endl;
      std::cout << "X LSB: " << static_cast<int> (lsb_x) << " " << std::endl;
      std::cout << "Y MSB: " << static_cast<int> (msb_y) << " " << std::endl;
      std::cout << "Y LSB: " << static_cast<int> (lsb_y) << " " << std::endl;
      std::cout << "Z MSB: " << static_cast<int> (msb_z) << " " << std::endl;
      std::cout << "Z LSB: " << static_cast<int> (lsb_z) << " " << std::endl;
      std::cout << "X mGauss in int16: " << x_gauss << std::endl;
      std::cout << "Y mGauss in int16: " << y_gauss << std::endl;
      std::cout << "Z mGauss in int16: " << z_gauss << std::endl;
      std::cout << "X uTesla: " << x_tesla << std::endl;
      std::cout << "Y uTesla: " << y_tesla << std::endl;
      std::cout << "Z uTesla: " << z_tesla << std::endl;
      msb_x = data.at (0);
      lsb_x = data.at (1);
      msb_y = data.at (2);
      lsb_y = data.at (3);
      msb_z = data.at (4);
      lsb_z = data.at (5);
    }
  return true;
}

CompassTest::~CompassTest ()
{
}
#endif
