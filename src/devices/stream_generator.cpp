#include "stream_generator.h"
#include "stream_generator_thread_params.h"
#include <pthread.h>

// Intialize static member
uint32_t StreamGenerator::m_interrupt_counter = 0;
pthread_mutex_t StreamGenerator::m_region_mutex = PTHREAD_MUTEX_INITIALIZER;
uint32_t StreamGenerator::m_min_period = 0;

// Private functions
void
StreamGenerator::timer_handler (int signo)
{
  m_interrupt_counter = m_interrupt_counter + m_min_period;
}

Stream*
StreamGenerator::lookup_device (std::shared_ptr<Device> device)
{
  for (uint8_t i = 0; i < m_streams.size (); i++)
    {
      if (m_streams.at (i)->get_device ()->equals (device) == true)
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
  m_max_period = 0;
  m_descriptor = descriptor;
  m_communication_number = communication_number;
  m_timer = std::unique_ptr<Timer> (new Timer (10000, timer_handler));
}

int8_t
StreamGenerator::add_stream (std::shared_ptr<Device> device, uint32_t period)
{
  Stream* stream = lookup_device (device);
  pthread_mutex_lock (&StreamGenerator::m_region_mutex);
  if (stream != NULL)
    {
      stream->set_period (period);
    }
  else
    {
      stream = new Stream (device, period);
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
  set_max_period (stream->get_period ());
  pthread_mutex_unlock (&StreamGenerator::m_region_mutex);
  return 1;
}

int8_t
StreamGenerator::disable_stream (std::shared_ptr<Device> device)
{
  Stream* stream = lookup_device (device);
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
	      std::vector<uint32_t>::iterator it = m_periods.begin ();
	      std::advance (it, j);
	      m_periods.erase (it);
#ifdef _DEBUG
	      std::cout << "Periods size: " << m_periods.size () << std::endl;
#endif
	    }
	}
      stream->set_active (false);
      uint32_t new_min = Calculation::gcd_vector (m_periods, 0,
						  m_periods.size ());
#ifdef _DEBUG
      std::cout << "New Min Period: " << new_min << std::endl;
#endif
      set_min_period (new_min);
      check_max_period (stream->get_period ());
      return 1;
    }
  else
    {
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
  uint32_t last_interrupt = 0;
#endif
  while (true)
    {
#ifdef _DEBUG
      std::cout << "Min Period: " << m_min_period << std::endl;
#endif
      pthread_mutex_lock (&StreamGenerator::m_region_mutex);
      std::vector<Stream*> streams = generator->get_streams ();
      pthread_mutex_unlock (&StreamGenerator::m_region_mutex);
      //If there is no stream and there fore no min period just sleep for 500ms
      if (m_min_period == 0)
	{
	  ts.tv_sec = 0;
	  ts.tv_nsec = 500000000;
	}
      /* Else set min period as sleep as there is only need to check every min period
       for new data
       */
      else
	{
	  ts.tv_sec = m_min_period / 1000;
	  ts.tv_nsec = (m_min_period % 1000) * 1000000;
	}
      for (uint32_t i = 0; i < streams.size (); i++)
	{
	  if (m_interrupt_counter % streams.at (i)->get_period () == 0
	      && m_min_period != 0 && streams.at (i)->is_active () == true)
	    {
	      //TODO: Call Create Frame
#ifdef _DEBUG
	      std::cout << "Device Descriptor: \n" << "Class: "
	      << static_cast<int> (streams.at (i)->get_device ()->get_component_descriptor ()->get_component_class ())
	      << "\tAttribute: "
	      << static_cast<int> (streams.at (i)->get_device ()->get_component_descriptor ()->get_component_attribute ())
	      << "\tNumber: "
	      << static_cast<int> (streams.at (i)->get_device ()->get_component_descriptor ()->get_component_number ())
	      << "\tPeriod: " << streams.at (i)->get_period () << std::endl;
	      std::cout << "Stream triggered!" << std::endl;
#endif
	      std::vector<int8_t> data;
	      data = streams.at (i)->get_device ()->read_data ();
	      if (data.size () != 0)
		{
		  for (uint16_t j = 0; j < data.size (); j++)
		    {
		      std::cout << "Data: " << data[j] << std::endl;
		    }
		  generator->m_protocol_engine->send_stream (
		      streams.at (i)->get_device (), data);
		  data.clear ();
		}
	    }
	}
#ifdef _DEBUG
      if (m_interrupt_counter != last_interrupt)
	{
	  last_interrupt = m_interrupt_counter;
	  std::cout << "Interrupt Counter: " << m_interrupt_counter
	  << std::endl;
	}
#endif
      if (m_interrupt_counter >= generator->get_max_period ())
	{
	  m_interrupt_counter = 0;
	}
      nanosleep (&ts, NULL);
    }
  return NULL;
}
StreamGenerator::~StreamGenerator ()
{
  m_streams.clear ();
  m_periods.clear ();

}
