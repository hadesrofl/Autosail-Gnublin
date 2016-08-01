#ifndef AUTOPILOT_SAIL_REGUALTOR_H_
#define AUTOPILOT_SAIL_REGUALTOR_H_
/**
 * @file
 * @class SailRegulator
 * @ingroup Autopilot
 * XXX NOT SUPPORTED YET
 * @brief Class for the SailRegulator. Regulates the Sail for setting and holding
 * course commands. It is realized in an own thread, so that it is possible to correct
 * the sail without interruptions except for scheduling interruptions based on the OS.
 *
 * @note Idea for AutoPilot mentioned in Bachelor Thesis "Entwurf, Implementierung
 * und Test eines Autopiloten für die Steuerung eines Modellsegelbootes
 * mit einem Android-Smartphone" by Hannes Range (October 2015)
 * @author Rene Kremer
 * @version 0.2
 */
class SailRegulator
{
  /**
   * @private
   */
private:
  /**
   * @protected
   */
protected:
  /**
   * @public
   */
public:
  /**
   * Constructor
   */
  SailRegulator ();
  /**
   * Destructor
   */
  ~SailRegulator ();
};

#endif /* AUTOPILOT_SAIL_REGUALTOR_H_ */
