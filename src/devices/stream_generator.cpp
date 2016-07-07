#include "stream_generator.h"
// Intialize static member
uint32_t StreamGenerator::m_interrupt_counter = 0;

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
  m_period = 0;

  m_timer = std::unique_ptr<Timer> (new Timer (0, timer_handler));
}
StreamGenerator::~StreamGenerator ()
{

}
