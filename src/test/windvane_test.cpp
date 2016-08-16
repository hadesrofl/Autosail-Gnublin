#ifdef _TEST
#include "windvane_test.h"

WindVaneTest::WindVaneTest ()
{
}
void
WindVaneTest::eval ()
{
  Loader* loader = new Loader ();
  std::shared_ptr<Device> windvane = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::WIND_VANE);
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
      data = windvane->read_data ();
      gettimeofday (&end, 0);
      std::cout << (begin.tv_sec) << ";" << (begin.tv_usec) / 1000 << ";"
	  << (end.tv_sec) << ";" << (end.tv_usec) / 1000 << ";"
	  << (end.tv_sec - begin.tv_sec) * 1000
	      + (end.tv_usec - begin.tv_usec) / 1000 << ";" << std::endl;
    }
}
bool
WindVaneTest::test_cases ()
{
  std::cout << "---------------------------------" << std::endl;
  std::cout << "Starting WINDVANE Test" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  Loader* loader = new Loader ();
  std::shared_ptr<Device> windvane = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::WIND_VANE);
  std::vector<int8_t> data;
  uint8_t i = 0;
  while (i != 5)
    {
      std::cout << "\nTest: " << static_cast<int32_t> (i) << std::endl;
      i++;
      data = windvane->read_data ();
      // Get Axis Value therefore shift MSB and OR MSB with LSB
      int16_t raw_x = (data.at (0) << 8) | data.at (1);
      std::cout << "Raw Data: " << static_cast<int> (data.at (1)) << " and "
	  << static_cast<int> (data.at (0)) << std::endl;
      std::cout << "Raw int16: " << raw_x << std::endl;
    }
  return true;
}

WindVaneTest::~WindVaneTest ()
{
}
#endif
