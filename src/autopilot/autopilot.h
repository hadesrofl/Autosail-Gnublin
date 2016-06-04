#ifndef AUTOPILOT_AUTOPILOT_H_
#define AUTOPILOT_AUTOPILOT_H_

#include "sail_regulator.h"
#include "course_regulator.h"
#include <memory>

/**
 * @file
 * @class AutoPilot
 * @brief Class for the Autopilot. Shall be realized in an own thread. Furthermore
 * an AutoPilot contains a SailRegulator and CourseRegalutor each realized in an own
 * thread to regulate Sail and Course autonomously for setting and holding a course.
 *
 * @note Idea for AutoPilot mentioned in Bachelor Thesis "Entwurf, Implementierung
 * und Test eines Autopiloten für die Steuerung eines Modellsegelbootes
 * mit einem Android-Smartphone" by Hannes Range (October 2015)
 * @author Rene Kremer
 * @version 0.2
 */
class AutoPilot
{
  /**
   * @private
   */
private:
  /**
   * SailRegulator of this AutoPilot
   */
  std::unique_ptr<SailRegulator> sail_regulator;
  /**
   * CourseRegulator of this AutoPilot
   */
  std::unique_ptr<CourseRegulator> course_regulator;
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
  AutoPilot ();
  /**
   * Destructor
   */
  ~AutoPilot ();
};

#endif /* AUTOPILOT_AUTOPILOT_H_ */
