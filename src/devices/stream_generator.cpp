#include "stream_generator.h"
#include "stream_generator_thread_params.h"
#include <pthread.h>
// Intialize static member
uint16_t StreamGenerator::m_interrupt_counter = 0;
pthread_mutex_t StreamGenerator::m_region_mutex = PTHREAD_MUTEX_INITIALIZER;

// Private functions
void
StreamGenerator::timer_handler (int signo)
{
  m_interrupt_counter++;
}
// Public functions
StreamGenerator::StreamGenerator ()
{
  m_interrupt_counter = 0;
  m_min_period = 0;
  m_max_period = 0;
  m_timer = std::unique_ptr<Timer> (new Timer (0, timer_handler));
}

void
StreamGenerator::add_stream (std::shared_ptr<Device> device, uint16_t period)
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
      m_min_period = stream->get_period ();
    }
  else
    {
      set_min_period (Calculation::gcd_vector (m_periods, 0, m_periods.size ()));
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
  while (true)
    {
      pthread_mutex_lock (&StreamGenerator::m_region_mutex);
      std::vector<Stream*> streams = generator->get_streams ();
      pthread_mutex_unlock (&StreamGenerator::m_region_mutex);
      std::cout << "Got streams" << std::endl;
      std::cout << "Stream Size: " << streams.size () << std::endl;
      std::cout << "List of Devices in Stream Generator: " << std::endl;
      for (uint32_t i = 0; i < streams.size (); i++)
	{
	  std::cout << "Device Descriptor: \n" << "Class: "
	      << static_cast<int> (streams.at (i)->get_device ()->get_component_descriptor ()->get_component_class ())
	      << "\tAttribute: "
	      << static_cast<int> (streams.at (i)->get_device ()->get_component_descriptor ()->get_component_attribute ())
	      << "\tNumber: "
	      << static_cast<int> (streams.at (i)->get_device ()->get_component_descriptor ()->get_component_number ())
	      << "\tPeriod: " << streams.at (i)->get_period () << std::endl;
	}
      std::cout << "Min Period: " << generator->get_min_period ()
	  << "\tMax Period: " << generator->get_max_period ()
	  << "\tInterrupt Counter: " << generator->get_interrupt_counter ()
	  << std::endl;
    }
  return NULL;
}
StreamGenerator::~StreamGenerator ()
{
  m_streams.clear ();
  m_periods.clear ();

}
