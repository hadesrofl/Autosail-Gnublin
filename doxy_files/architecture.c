/**
 * @page Architecture Architecture
 * @tableofcontents
 * This Page is a short overview over the Architecture used for the firmware
 *
 * @section sec1 Modules
 * In the following you'll find the class diagram as an overview, but also
 * some shorter class diagrams to show some specific behaviour and connections
 * of the classes. This is due the fact that the class diagram is too large
 * to show in detail.
 *
 * @subsection ssec11 Interfaces
 * There are the following Interfaces: SPIMasterSelect, Serial and I2C
 *
 * These Interfaces are used by devices. SPIMasterSelect is a FHL (Fachhochschule Luebeck) own version of SPI
 * and has an additional pin, so that a slave can select a master and signals that
 * the slave wants to send data.
 *
 * @subsection ssec12 Devices
 * The following devices are implemented:
 *
 * <ul>
 * 	<li>Accelerometer</li>
 * 	<li>Anemometer (sure?)</li>
 * 	<li>Compass</li>
 * 	<li>GPS</li>
 * 	<li>Gyroscope</li>
 * 	<li>Hygrometer (sure?)</li>
 * 	<li>SerialLink</li>
 * 	<li>ServoMotor</li>
 * 	<li>WestonAnemometer (sure?)</li>
 * 	<li>WindVane (sure?)</li>
 * </ul>
 * @subsection ssec13 Bridge
 * Ugly Hacks / Black Magic with Timer
 * @subsection ssec14 Communication
 * ProtocolEngine for flexibility, yeah <3
 * @subsection ssec15 Autopilot
 * Well might... drop because of a too big workload
 * @subsection ssec16 Utils
 * Filter for the future use and maybe a ConfReader
 *
 */

