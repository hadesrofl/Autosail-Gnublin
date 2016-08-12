#ifdef _TEST
#include "windvane_test.h"

WindVaneTest::WindVaneTest ()
{
}

bool
WindVaneTest::test_cases ()
{
  std::cout << "---------------------------------" << std::endl;
  std::cout << "Starting WINDVANE Test" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  Loader* loader = new Loader ();
  std::shared_ptr<Device> windvane =
      loader->get_device_manager ()->get_device (
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
