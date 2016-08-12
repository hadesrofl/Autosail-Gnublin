/**
    @defgroup Enums Enumeration types
    @defgroup Autopilot Autopilot classes
    @defgroup Communication Communication classes
    @defgroup Devices Device classes
    @defgroup Interfaces Interface classes
    @defgroup Utils Utilitiy classes
*/

/**
 * @mainpage Autosail API Embedded Linux
 *
 * <h3>Port of the firmware from a microprocessor to the gnublin platform for an autonomous sailboat</h3>
 *
 * <h4>Table of Contents</h4>
 * <ol>
 * 	<li><a href = "./Architecture.html">Architecture</a></li>
 * 	<li><a href = "./Software-Interrupt.html">Software Interrupt in Linux</a></li>
 * </ol>
 *
 * <h4>22.08.2016</h4>
 *
 * First implementation of a prototype for the firmware of the autonomous sailboat of
 * the Fachhochschule Luebeck - University of Applied Science.
 *
 * This portation of the firmware was subject of the Bachelor Thesis by Rene Kremer.
 *
 * For running the software a config file is needed in a <i>config</i> directory where the firmware is started.
 * The software creates a ramdisk in <i>/media/ramdisk</i> to save a tmp file for the gps data there.
 * This file will be read by the firmware because the gps uses a sub program as client for <i>gpsd</i>
 * to read the gps data.
 *
 * <br>
 * <br>
 * <img src="images/wiki_logo_135p.png"  alt="Autosail Wiki Logo" align="middle"/>
 *
 */
