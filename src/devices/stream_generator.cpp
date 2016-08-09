#include "stream_generator.h"
#include "stream_generator_thread_params.h"
#include <pthread.h>

// Intialize static member
uint16_t StreamGenerator::m_interrupt_counter = 0;
pthread_mutex_t StreamGenerator::m_region_mutex;
uint16_t StreamGenerator::m_min_period = 0;
pthread_mutex_t StreamGenerator::m_active_mutex;
pthread_cond_t StreamGenerator::m_wakeup_cond;
bool StreamGenerator::m_active = false;

// Private functions
void
StreamGenerator::timer_handler (int signo)
{
  pthread_mutex_lock (&m_active_mutex);
  m_active = true;
  pthread_cond_signal (&m_wakeup_cond);
  pthread_mutex_unlock (&m_active_mutex);
  m_interrupt_counter = m_interrupt_counter + m_min_period;
}

Stream*
StreamGenerator::lookup_device (uint8_t comm_number)
{
  for (uint8_t i = 0; i < m_streams.size (); i++)
    {
      if (m_streams.at (i)->get_communication_number () == comm_number)
	{
	  return m_streams.at (i);
	}
    }
  return NULL;
}

// Public functions
StreamGenerator::StreamGenerator (
    std::shared_ptr<ComponentDescriptor> descriptor,
    uint8_t communication_number)
{
  pthread_mutex_init (&StreamGenerator::m_region_mutex, NULL);
  pthread_mutex_init (&StreamGenerator::m_active_mutex, NULL);
  pthread_cond_init (&StreamGenerator::m_wakeup_cond, NULL);

  m_max_period = 0;
  m_descriptor = descriptor;
  m_communication_number = communication_number;
  m_timer = std::unique_ptr<Timer> (new Timer (10000, timer_handler));
}

int8_t
StreamGenerator::add_stream (std::shared_ptr<Device> device,
			     uint8_t communication_number, uint16_t period)
{
  Stream* stream = lookup_device (communication_number);
  pthread_mutex_lock (&StreamGenerator::m_region_mutex);
  if (stream != NULL)
    {
      stream->set_period (period);
    }
  else
    {
      stream = new Stream (device, communication_number, period);
#ifdef _DEBUG
      std::cout << "Device: " << "Class: "
      << static_cast<int> (stream->get_device ()->get_component_descriptor ()->get_component_class ())
      << " Attribute: "
      << static_cast<int> (stream->get_device ()->get_component_descriptor ()->get_component_attribute ())
      << " Number: "
      << static_cast<int> (stream->get_device ()->get_component_descriptor ()->get_component_number ())
      << std::endl;
      std::cout << "Period: " << stream->get_period () << std::endl;
#endif
      m_streams.push_back (stream);
    }
  m_periods.push_back (stream->get_period ());
  if (m_min_period == 0)
    {
      set_min_period (stream->get_period ());
    }
  else
    {
      set_min_period (
	  Calculation::gcd_vector (m_periods, 0, m_periods.size ()));
    }
#ifdef _DEBUG
  std::cout << "Min Period: " << get_min_period () << std::endl;
#endif
  stream->set_active (true);
  set_max_period (stream->get_period ());
  pthread_mutex_unlock (&StreamGenerator::m_region_mutex);
  return 1;
}

int8_t
StreamGenerator::disable_stream (uint8_t comm_number)
{
  pthread_mutex_lock (&StreamGenerator::m_region_mutex);
  Stream* stream = lookup_device (comm_number);
  if (stream != NULL)
    {
#ifdef _DEBUG
      std::cout << "Period of disabled Stream: " << stream->get_period ()
      << std::endl;
#endif
      for (uint8_t j = 0; j < m_periods.size (); j++)
	{
	  if (m_periods.at (j) == stream->get_period ())
	    {
#ifdef _DEBUG
	      std::cout << "Periods size: " << m_periods.size () << std::endl;
	      std::cout << "Deactive: " << m_periods.at (j) << std::endl;
#endif
	      std::vector<uint16_t>::iterator it = m_periods.begin ();
	      std::advance (it, j);
	      m_periods.erase (it);
#ifdef _DEBUG
	      std::cout << "Periods size: " << m_periods.size () << std::endl;
#endif
	    }
	}
      stream->set_period (0);
      stream->set_active (false);
      uint16_t new_min = Calculation::gcd_vector (m_periods, 0,
						  m_periods.size ());
#ifdef _DEBUG
      std::cout << "New Min Period: " << new_min << std::endl;
#endif
      set_min_period (new_min);
      check_max_period (stream->get_period ());
      pthread_mutex_lock (&StreamGenerator::m_active_mutex);
      if (m_periods.size () == 0)
	{
	  m_active = false;
	  m_interrupt_counter = 0;
	}
      pthread_mutex_unlock (&StreamGenerator::m_active_mutex);
      pthread_mutex_unlock (&StreamGenerator::m_region_mutex);
      return 1;
    }
  else
    {
      pthread_mutex_lock (&StreamGenerator::m_active_mutex);
      if (m_periods.size () == 0)
	{
	  m_active = false;
	  m_interrupt_counter = 0;
	}
      pthread_mutex_unlock (&StreamGenerator::m_active_mutex);
      pthread_mutex_unlock (&StreamGenerator::m_region_mutex);
      return -1;
    }
}

void *
StreamGenerator::run_generator (void* params)
{
  pthread_mutex_lock (&StreamGenerator::m_region_mutex);
  struct stream_generator_thread_param_t* generator_param =
      (struct stream_generator_thread_param_t*) params;
  std::shared_ptr<StreamGenerator> generator = generator_param->generator_ptr;
  pthread_mutex_unlock (&StreamGenerator::m_region_mutex);
  struct timespec ts;
#ifdef _DEBUG
  uint16_t last_interrupt = 0;
#endif
  while (true)
    {
      if (m_active == false)
	{
	  //If there is no stream and there fore no min period just sleep for 500ms
	  pthread_mutex_lock (&m_active_mutex);
#ifdef _DEBUG
	  std::cout << "\nWaiting for signal...\n" << std::endl;
#endif
	  pthread_cond_wait (&m_wakeup_cond, &m_active_mutex);
	  m_active = true;
#ifdef _DEBUG
	  std::cout << "Generator is active again!" << std::endl;
#endif
	}
      else
	{
#ifdef _DEBUG
	  std::cout << "Min Period: " << m_min_period << std::endl;
#endif
	  pthread_mutex_lock (&StreamGenerator::m_region_mutex);
	  std::vector<Stream*> streams = generator->get_streams ();
	  pthread_mutex_unlock (&StreamGenerator::m_region_mutex);

	  pthread_mutex_unlock (&m_active_mutex);

	  /* Set min period as sleep as there is only need to check every min period
	   for new data
	   */
	  ts.tv_sec = m_min_period / 1000;
	  ts.tv_nsec = (m_min_period % 1000) * 1000000;
#ifdef _DEBUG
	  if (m_interrupt_counter != last_interrupt)
	    {
	      last_interrupt = m_interrupt_counter;
	      std::cout << "Interrupt Counter: " << m_interrupt_counter
	      << std::endl;
	    }
#endif
	  for (uint32_t i = 0; i < streams.size (); i++)
	    {
	      if (streams.at (i)->is_active () == true
		  && m_interrupt_counter % streams.at (i)->get_period () == 0
		  && m_min_period != 0)
		{
#ifdef _DEBUG
		  std::cout << "Device Descriptor: \n" << "Class: "
		  << static_cast<int> (streams.at (i)->get_device ()->get_component_descriptor ()->get_component_class ())
		  << "\tAttribute: "
		  << static_cast<int> (streams.at (i)->get_device ()->get_component_descriptor ()->get_component_attribute ())
		  << "\tNumber: "
		  << static_cast<int> (streams.at (i)->get_device ()->get_component_descriptor ()->get_component_number ())
		  << "\nCommunication Number: "
		  << static_cast<int> (streams.at (i)->get_communication_number ())
		  << "\tPeriod: " << streams.at (i)->get_period () << std::endl;
		  std::cout << "Stream triggered!" << std::endl;
#endif
		  std::vector<int8_t> data;
		  data = streams.at (i)->get_device ()->read_data ();
		  if (data.size () != 0)
		    {
#ifdef _DEBUG
		      for (uint16_t j = 0; j < data.size (); j++)
			{
			  std::cout << "Data: " << static_cast<int> (data[j])
			  << std::endl;
			}
#endif
		      if (GPS* v =
			  dynamic_cast<GPS*> (&(*(streams.at (i)->get_device ()))))
			{
			  // old was safely casted to NewType
			  gps_data_t* gps_data = v->get_last_data ();
			  uint8_t comm_number =
			      generator->m_protocol_engine->get_communication_number (
				  v->get_component_descriptor ());
			  data.clear ();
			  //GPS position
			  if (streams.at (i)->get_communication_number ()
			      == comm_number)
			    {
			      int8_t* longitude = IntConverter::int32_to_int8 (
				  gps_data->longitude);
			      int8_t* latitude = IntConverter::int32_to_int8 (
				  gps_data->latitude);
			      data.push_back (latitude[0]);
			      data.push_back (latitude[1]);
			      data.push_back (latitude[2]);
			      data.push_back (latitude[3]);
			      data.push_back (longitude[0]);
			      data.push_back (longitude[1]);
			      data.push_back (longitude[2]);
			      data.push_back (longitude[3]);
			      delete[] longitude;
			      delete[] latitude;
			    }
			  // GPS Validity
			  else if (streams.at (i)->get_communication_number ()
			      == comm_number + 1)
			    {
			      data.push_back (gps_data->fix_mode);
			    }
			  // GPS Velocity
			  else if (streams.at (i)->get_communication_number ()
			      == comm_number + 2)
			    {
			      int8_t* speed = IntConverter::int16_to_int8 (
				  gps_data->speed);
			      int8_t* direction = IntConverter::int16_to_int8 (
				  gps_data->direction);
			      data.push_back (speed[0]);
			      data.push_back (speed[1]);
			      data.push_back (direction[0]);
			      data.push_back (direction[1]);
			      delete[] speed;
			      delete[] direction;
			    }
			}
		      generator->m_protocol_engine->send_stream (streams.at (i),
								 data);
		      data.clear ();
		    }
		}
	    }
	  if (m_interrupt_counter >= generator->get_max_period ())
	    {
	      m_interrupt_counter = 0;
	    }
	  nanosleep (&ts, NULL);
	}
    }
  return NULL;
}
StreamGenerator::~StreamGenerator ()
{
  m_streams.clear ();
  m_periods.clear ();

}
