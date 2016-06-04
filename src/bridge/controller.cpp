#include "controller.h"

Controller::Controller ()
{
  m_stream_generator = std::unique_ptr<StreamGenerator>(new StreamGenerator());
  m_protocol_engine = std::unique_ptr<ProtocolEngine> (new TLVEEngine());
  m_autopilot = std::unique_ptr<AutoPilot> (new AutoPilot());
}
Controller::~Controller ()
{

}
