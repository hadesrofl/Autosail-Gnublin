#include "conf_reader.h"

// Private functions
int8_t
ConfReader::store_line (uint8_t* value, uint16_t value_length)
{
  uint8_t* stored_value = new uint8_t[value_length];
  for (uint16_t i = 0; i < value_length; i++)
    {
      stored_value[i] = value[i];
    }
  m_config_values.push_back (stored_value);
  return 1;
}

int8_t
ConfReader::read_config ()
{
  std::ifstream input;
  uint8_t length = 50;
  uint16_t value_length = 0;
  bool equals_seen = false;
  uint8_t* value = new uint8_t[length];
  char temp_c;

  input.open (m_file);
  if (input.is_open () == true)
    {
      while (input.eof () == false)
	{
	  input.get (temp_c);
	  if (temp_c == '\n')
	    {
	      if (array_is_empty (value, value_length) == false)
		{
		  store_line (value, value_length);
		  clear_array (value, value_length);
		  value_length = 0;
		}
	      equals_seen = false;
	    }
	  if (!(isspace (temp_c)) && temp_c != 0)
	    {
	      if (equals_seen == false)
		{
		  if (temp_c == '=')
		    {
		      equals_seen = true;
		    }
		}
	      else
		{
		  value[value_length] = temp_c;
		  value_length++;
		}
	    }
	}
      equals_seen = false;
      input.close ();
    }
  else
    {
      std::cout << "Error while opening file!" << std::endl;
      delete[] value;
      return -1;
    }
  delete[] value;
  return 1;
}

uint16_t
ConfReader::clear_array (uint8_t array[], uint16_t length)
{
  for (int16_t i = 0; i < length; i++)
    {
      array[i] = 0;
    }
  return length;
}

bool
ConfReader::array_is_empty (uint8_t array[], uint16_t length)
{
  for (uint16_t i = 0; i < length; i++)
    {
      if (array[i] != 0)
	{
	  return false;
	}
    }
  return true;
}

// Public functions
ConfReader::ConfReader (const char* file)
{
  m_file = file;
}
std::vector<Descriptor>
ConfReader::get_descriptors ()
{
  uint16_t tmp, j;
  std::vector<Descriptor> descriptors;
  if (read_config () > 0)
    {
      // i = i + 2 to skip the name of the device and go to the id
      for (uint32_t i = 0; i < m_config_values.size (); i = i + 2)
	{
	  tmp = 0;
	  j = 0;
	  while (m_config_values[i + 1][j] != '\0')
	    {
	      tmp = (tmp * DECIMAL_SHIFT)
		  + static_cast<int16_t> (m_config_values[i + 1][j]
		      - ASCII_SHIFT);
	      descriptors.push_back (static_cast<Descriptor> (tmp));
	      j++;
	    }
	}
    }
  return descriptors;
}

ConfReader::~ConfReader ()
{

}
