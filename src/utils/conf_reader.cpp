#include "conf_reader.h"

// Private functions
int8_t
ConfReader::store_line (uint8_t* value, uint16_t value_length)
{
  uint8_t* stored_value = new uint8_t[value_length + 1];
  for (uint16_t i = 0; i < value_length; i++)
    {
      stored_value[i] = value[i];
    }
  stored_value[value_length] = '\0';
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
#ifdef _DEBUG
		  std::cout << "Value: " << value << std::endl;
#endif
		  store_line (value, value_length);
		  clear_array (value, length);
		  value_length = 0;
		}
	      equals_seen = false;
	    }
	  if (!(isspace (temp_c)))
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
#ifdef _DEBUG
      std::cout << "Error while opening file!" << std::endl;
#endif
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
std::vector<uint8_t>
ConfReader::get_descriptors ()
{
  std::vector<uint8_t> descriptors;
  if (read_config () > 0)
    {
      // i = i + 2 to skip the name of the device and go to the id
      for (uint32_t i = 0;
	  i < m_config_values.size () / DATA_ENTRIES_PER_COMPONENT; i++)
	{
#ifdef _DEBUG
	  std::cout << "Integer I: " << i << std::endl;
#endif
	  if (i == 0)
	    {
	      for (uint32_t j = 1; j < DATA_ENTRIES_PER_COMPONENT; j++)
		{
		  read_line (&descriptors, j);
		}
	    }
	  else
	    {
	      for (uint32_t j = i * DATA_ENTRIES_PER_COMPONENT + 1;
		  j
		      < i * DATA_ENTRIES_PER_COMPONENT
			  + DATA_ENTRIES_PER_COMPONENT; j++)
		{
#ifdef _DEBUG
		  std::cout << "Integer J: " << j << std::endl;
		  std::cout << "Max J : "
		      << (i * DATA_ENTRIES_PER_COMPONENT
			  + DATA_ENTRIES_PER_COMPONENT) << std::endl;
#endif
		  read_line (&descriptors, j);
		}
	    }
	}
    }
  return descriptors;
}
void
ConfReader::read_line (std::vector<uint8_t> *values, uint32_t index)
{
  uint16_t j = 0;
  uint8_t first_value = 0;
  bool pushed = false;
  while (m_config_values[index][j + 1] != '\0')
    {
      if (m_config_values[index][j] == '0'
	  && m_config_values[index][j + 1] == 'x')
	{
	  j = j + 2;
	}
      first_value = m_config_values[index][j] * 16
	  + m_config_values[index][j + 1] - ASCII_SHIFT;
      values->push_back (first_value);
      pushed = true;
      j++;
    }
  if (pushed == false && m_config_values[index][j + 1] == '\0')
    {
      first_value = static_cast<uint8_t> (m_config_values[index][j]);
      values->push_back (first_value);
    }
}

ConfReader::~ConfReader ()
{

}
