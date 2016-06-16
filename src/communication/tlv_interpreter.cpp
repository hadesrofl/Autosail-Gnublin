#include "tlv_interpreter.h"

TLVInterpreter::TLVInterpreter ()
{

}
Frame*
TLVInterpreter::interpret_frame (Device* device, TLVFrame* frame)
{
  uint8_t data_structure_id = frame->get_attribute () >> 5;
  ComponentDescriptor descriptor = device->get_component_descriptor ();
  ComponentDescriptorEnum descriptor_enum =
      static_cast<ComponentDescriptorEnum> (descriptor.get_component_class ()
	  + descriptor.get_component_attribute ());

  switch (frame->get_tag ())
    {
    //TODO: Add other Commands
    case 0x11:
      switch (descriptor_enum)
	{
	case ComponentDescriptorEnum::ACCELEROMETER:
	 dynamic_cast<Accelerometer*> (device);
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::ANEMOMETER:
	  dynamic_cast<Anemometer*> (device);
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::COMPASS:
	  dynamic_cast<Compass*> (device);
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::GPS:
	  dynamic_cast<GPS*> (device);
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::HYGROMETER:
	  dynamic_cast<Hygrometer*> (device);
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::SERIAL_LINK:
	  dynamic_cast<SerialLink*> (device);
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::SERVO_MOTOR:
	  dynamic_cast<ServoMotor*> (device);
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::STREAM_GENERATOR:
	  //TODO: Get some other fancy idea for getting Stream Generator
	  //maybe add StreamGenerator to Interpreter? & BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::WESTON_ANEMOMETER:
	  dynamic_cast<WestonAnemometer*> (device);
	  //TODO: BlackMagic Commands
	  break;
	case ComponentDescriptorEnum::WIND_VANE:
	  dynamic_cast<WindVane*> (device);
	  //TODO: BlackMagic Commands
	  break;
	}
      break;
    }
  return NULL;
}
TLVInterpreter::~TLVInterpreter ()
{

}
