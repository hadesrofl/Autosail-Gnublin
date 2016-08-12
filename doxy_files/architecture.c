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
 * 	<li>Anemometer</li>
 * 	<li>Battery</li>
 * 	<li>Compass</li>
 * 	<li>GPS</li>
 * 	<li>Gyroscope</li>
 * 	<li>SerialLink</li>
 * 	<li>ServoMotor</li>
 * 	<li>WindVane</li>
 * </ul>
 *
 */

