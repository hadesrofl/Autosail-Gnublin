#include "autopilot.h"

AutoPilot::AutoPilot (std::shared_ptr<ComponentDescriptor> descriptor,
		      uint8_t communication_number)
{
  m_status = 0;
  m_descriptor = descriptor;
  m_communication_number = communication_number;
  m_direction = 0;
}
int8_t
AutoPilot::set_course (int16_t direction)
{
  m_direction = direction;
  std::cout << "Direction changed to: " << m_direction << std::endl;
  set_status (STATUS_HOLD_COURSE);
  return 1;
}
int8_t
AutoPilot::hold_course ()
{
  std::cout << "Holding course to: " << m_direction << std::endl;
  set_status (STATUS_HOLD_COURSE);
  return 1;
}
int8_t
AutoPilot::set_active (bool active)
{
  if (active == false)
    {
      set_status (STATUS_OFF);
    }
  return 1;
}

AutoPilot::~AutoPilot ()
{

}

