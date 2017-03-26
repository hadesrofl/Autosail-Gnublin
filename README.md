 # Port of the firmware from a microprocessor to the [gnublin](http://en.gnublin.org/index.php/Main_Page) platform for an autonomous sailboat
 
 Implementation of a prototype for the firmware of the autonomous sailboat of
 the Fachhochschule Luebeck - University of Applied Science.
 
 This portation of the firmware was subject of the Bachelor Thesis by Rene Kremer.
 
 For running the software a config file is needed in a *config* directory where the firmware is started.
 The software creates a ramdisk in */media/ramdisk* to save a tmp file for the gps data there.
 This file will be read by the firmware because the gps uses a sub program as client for *gpsd*
 to read the gps data.