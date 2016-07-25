#ifndef AUTOPILOT_AUTOPILOT_H_
#define AUTOPILOT_AUTOPILOT_H_

#include "sail_regulator.h"
#include "course_regulator.h"
#include <memory>

/**
 * @file
 * @class AutoPilot
 * @ingroup Autopilot
 * @brief Class for the Autopilot. Shall be realized in an own thread. Furthermore
 * an AutoPilot contains a SailRegulator and CourseRegulator each realized in an own
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
   * Is the autopilot on or off? Default is false on construction
   */
  bool m_on;
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
  /**
   * Sets AutoPilot on or off
   * @param on is a boolean defining if the AutoPilot is on or off
   */
  inline void autopilot_on(bool on){
    m_on = on;
  }
  /**
   * Checks if the AutoPilot is on or off
   * @return true if the autopilot is on, otherwise false
   */
  inline bool is_autopilot_on() const{
    return m_on;
  }
};

#endif /* AUTOPILOT_AUTOPILOT_H_ */
