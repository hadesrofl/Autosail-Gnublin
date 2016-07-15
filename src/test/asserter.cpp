#ifdef _TEST
#include "asserter.h"
#include <iostream>

bool
Asserter::assert (unsigned char* send_data, unsigned char* received_data, int length)
{
	bool assert = true;
	for (int i = 0; i < length; i++)
	{
		if (send_data[i] != received_data[i])
		{
			assert = false;
		}
	}
	return assert;
}
bool
Asserter::assert (uint8_t result, uint8_t expected)
{
	if(result == expected)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool
Asserter::assert (uint16_t result, uint16_t expected)
{
	if(result == expected)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool
Asserter::assert (uint32_t result, uint32_t expected)
{
	if(result == expected)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool
Asserter::assert (std::shared_ptr<Device> result, std::shared_ptr<Device> expected)
{
	if(result->get_component_descriptor()->get_component_class() == expected->get_component_descriptor()->get_component_class() &&
			result->get_component_descriptor()->get_component_attribute() == expected->get_component_descriptor()->get_component_attribute() &&
			result->get_component_descriptor()->get_component_number() == expected->get_component_descriptor()->get_component_number())
	{
		return true;
	}
	return false;
}

bool
Asserter::check_asserts (std::vector<bool> asserts, int n_tests)
{
	int passed_asserts = 0;
	for (int i = 0; i < n_tests; i++)
	{
		if (asserts[i] == false)
		{
			std::cout << "Assert " << i << " failed!" << std::endl;
		}
		else
		{
			passed_asserts++;
		}
	}
	if (passed_asserts == n_tests)
	{
		std::cout << "All asserts passed!" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}
#endif
