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
// Public functions
StreamGenerator::StreamGenerator ()
{
  m_max_period = 0;
  m_timer = std::unique_ptr<Timer> (new Timer (10000, timer_handler));
}

void
StreamGenerator::add_stream (std::shared_ptr<Device> device, uint32_t period)
{
  Stream* stream = new Stream (device, period);
  std::cout << "Device: " << "Class: "
      << static_cast<int> (stream->get_device ()->get_component_descriptor ()->get_component_class ())
      << " Attribute: "
      << static_cast<int> (stream->get_device ()->get_component_descriptor ()->get_component_attribute ())
      << " Number: "
      << static_cast<int> (stream->get_device ()->get_component_descriptor ()->get_component_number ())
      << std::endl;
  std::cout << "Period: " << stream->get_period () << std::endl;
  pthread_mutex_lock (&StreamGenerator::m_region_mutex);
  m_streams.push_back (stream);
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
  std::cout << "Min Period: " << get_min_period () << std::endl;
  set_max_period (stream->get_period ());
  pthread_mutex_unlock (&StreamGenerator::m_region_mutex);
}

void *
StreamGenerator::run_generator (void* params)
{
  pthread_mutex_lock (&StreamGenerator::m_region_mutex);
  struct stream_generator_thread_param_t* generator_param =
      (struct stream_generator_thread_param_t*) params;
  StreamGenerator* generator = generator_param->generator_ptr;
  pthread_mutex_unlock (&StreamGenerator::m_region_mutex);
  struct timespec ts;
  uint32_t last_interrupt = 0;
  while (true)
    {
      pthread_mutex_lock (&StreamGenerator::m_region_mutex);
      std::vector<Stream*> streams = generator->get_streams ();
      pthread_mutex_unlock (&StreamGenerator::m_region_mutex);
      ts.tv_sec = m_min_period / 1000;
      ts.tv_nsec = (m_min_period % 1000) * 1000000;
      for (uint32_t i = 0; i < streams.size (); i++)
	{
	  if (m_interrupt_counter % streams.at (i)->get_period () == 0 && m_min_period != 0)
	    {
	      std::cout << "Device Descriptor: \n" << "Class: "
		  << static_cast<int> (streams.at (i)->get_device ()->get_component_descriptor ()->get_component_class ())
		  << "\tAttribute: "
		  << static_cast<int> (streams.at (i)->get_device ()->get_component_descriptor ()->get_component_attribute ())
		  << "\tNumber: "
		  << static_cast<int> (streams.at (i)->get_device ()->get_component_descriptor ()->get_component_number ())
		  << "\tPeriod: " << streams.at (i)->get_period () << std::endl;
	      /*int8_t* data = new int8_t[6];
	       data = streams.at (i)->get_device ()->read_data ();
	       for (int32_t i = 0; i < 6; i++)
	       {
	       std::cout << "Data: " << data[i] << std::endl;
	       }
	       delete[] data;
	       */
	      std::cout << "Stream triggered!" << std::endl;
	    }
	  if (m_interrupt_counter != last_interrupt)
	    {
	      last_interrupt = m_interrupt_counter;
	      std::cout << "Interrupt Counter: " << m_interrupt_counter
		  << std::endl;
	    }
	  if (m_interrupt_counter >= generator->get_max_period())
	    {
	      m_interrupt_counter = 0;
	    }
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
