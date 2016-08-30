/**
 * Copyright 2016 Rene Kremer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
