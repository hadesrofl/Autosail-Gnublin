#ifndef AUTOPILOT_COURSE_REGULATOR_H_
#define AUTOPILOT_COURSE_REGULATOR_H_
/**
 * @file
 * @class CourseRegulator
 * @brief Class for the CourseRegulator. Regulates the Course for setting and holding
 * course commands. It is realized in an own thread, so that it is possible to correct
 * the rudder without interruptions except for scheduling interruptions based on the OS.
 *
 * @note Idea for AutoPilot mentioned in Bachelor Thesis "Entwurf, Implementierung
 * und Test eines Autopiloten für die Steuerung eines Modellsegelbootes
 * mit einem Android-Smartphone" by Hannes Range (October 2015)
 * @author Rene Kremer
 * @version 0.2
 */
class CourseRegulator
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
  CourseRegulator ();
  /**
   * Destructor
   */
  ~CourseRegulator ();
};

#endif /* AUTOPILOT_COURSE_REGULATOR_H_ */
