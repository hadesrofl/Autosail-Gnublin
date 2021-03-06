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

#ifndef INTERFACES_S_P_I_MASTER_SELECT_H
#define INTERFACES_S_P_I_MASTER_SELECT_H

#include "../../gnublin_wo_smtp.h"
#include "interface.h"
#include <poll.h>
#include <pthread.h>

/**
 * Prefix of the Trigger File for the Master Select
 */
#define PIN_MS_PRE_TRIGGER_FILE "/sys/class/gpio/gpio"
/**
 * Suffix of the Trigger File for the Master Select
 */
#define PIN_MS_SUFF_TRIGGER_FILE "/edge"
/**
 * Prefix of the Value File for the Master Select
 */
#define PIN_MS_PRE_VALUE_FILE "/sys/class/gpio/gpio"
/**
 * Prefix of the Value File for the Master Select
 */
#define PIN_MS_SUFF_VALUE_FILE "/value"
/**
 * Trigger on falling edge
 */
#define TRIGGER_FALLING "falling"
/**
 * Trigger on rising edge
 */
#define TRIGGER_RISING "rising"
/**
 * Pin for Pin Change Interrupt
 */
#define PCI_PIN 11
/**
 * Length of Command to set output for gpio pin
 */
#define COMMAND_OUTPUT_PIN_LENGTH 24

/**
 * @file
 * @class SPIMasterSelect
 * @ingroup Interfaces
 * @brief Class for a SPI Interface. Implements the abstract Interface class and
 * adds some specific functions of a SPI Interface.
 * @author Rene Kremer
 * @version 0.35
 */
class SPIMasterSelect : public Interface
{
  /**
   * @private
   */
private:
  /**
   * Gnublin SPI Port
   */
  std::unique_ptr<gnublin_spi> m_spi_port;
  /**
   * Region Mutex for multithreaded access
   */
  static pthread_mutex_t m_region_mutex;
  /**
   * Number of the Master Select GPIO Pin
   */
  uint8_t m_pin_ms;
  /**
   * Trigger Action (TRIGGER_FALLING or TRIGGER_RISING)
   */
  char* m_trigger_action;

  /**
   * Sets the trigger type for an interrupt to the gpio pin
   * @param pin_no is the number of the gpio pin to trigger
   * @param trigger is either falling or rising for the trigger action
   * @return on success 1, otherwise -1 as error
   */
  int8_t
  set_trigger_type (uint8_t pin_no, char* trigger);
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param device_file is the name of the file of the device
   * @param spi_speed is the speed of the spi bus
   * @param pin_no number of the pin for the master select. If no pin is
   * needed for master select just set pin_no to 0
   */
  SPIMasterSelect (char* device_file, uint16_t spi_speed, uint8_t pin_no);
  /**
   * Receives data from the SPI Port and writes it into the buffer
   * Length indicates the amount of bytes to read
   * @param buf is the buffer to write the received data into
   * @param length is the amount of bytes to read
   * @return the length on success, otherwise -1 as error
   */
  int16_t
  receive (uint8_t* buf, int16_t length);
  /**
   * Sends data via the SPI Port
   * @param buf is the buffer containing the bytes to send
   * @param length is the length of bytes to send
   * @return the length on success, otherwise -1 as error
   */
  int16_t
  send (uint8_t* buf, int16_t length);
  /**
   * Transfers data in half duplex mode via the SPI.
   * @param write is the buffer to write data from
   * @param write_length is the length of data to write
   * @param read is the buffer to read data into
   * @param read_length is the length of byte to read
   * @return 1 on success, otherwise -1
   */
  int8_t
  transfer (uint8_t* write, int16_t write_length, uint8_t* read,
	    int16_t read_length);

  /**
   * Pin Change Interrupt for Master Select Pin.
   * Uses Systemcall Poll to check a file descriptor for some event.
   * Needs to be static because pthread needs a pointer-to-function
   * not pointer-to-member-function.
   * @param spi is a SPIThreadParam cointaning the device to soften the static
   * modifier.
   */
  static void *
  pin_change_interrupt (void* spi);

  /**
   * Inline Function to set a new SPI mode
   * @param mode is the new mode
   * @return mode on success, otherwise -1 as error
   */
  inline int8_t
  set_mode (uint8_t mode)
  {
    return 0;
  }

  /**
   * Inline Function to get the current SPI mode
   * @return the current SPI mode
   */
  inline uint8_t
  get_mode () const
  {
    return 0;
  }

  /**
   * Inline Function to set the LSB (least significant bit)
   * @param lsb is the least significant bit
   * @return the LSB on success, otherwise -1 as error
   */
  inline int8_t
  set_lsb (uint8_t lsb)
  {
    return 0;
  }

  /**
   * Inline Function to get the current LSB (least significant bit)
   * @return the LSB on success, otherwise -1 as error
   */
  inline uint8_t
  get_lsb () const
  {
    return 0;
  }

  /**
   * Sets the length of bits per word
   * @param bits is the amount of bits per word
   * @return the new bits per word on success, otherwise -1 as error
   */
  inline int8_t
  set_length (uint8_t bits)
  {
    return 0;
  }

  /**
   * Inline Function to get the length of bits per word
   * @return the amount of bits per word
   */
  inline uint16_t
  get_length () const
  {
    return 0;
  }

  /**
   * Inline Function to set the speed of the SPI
   * @param speed is the new speed of the SPI
   * @return speed on success, otherwise -1 as error
   */
  inline int8_t
  set_speed (uint16_t speed)
  {
    return 0;
  }

  /**
   * Inline Function to get the current speed of the SPI Interface
   * @return the current speed
   */
  inline uint16_t
  get_speed () const
  {
    return 0;
  }

  /**
   * Inline Function to set the chip select
   * @param cs is the new chip select
   * @return chip select on success, otherwise -1 as error
   */
  inline int8_t
  set_cs (uint8_t cs)
  {
    return 0;
  }

  /**
   * Gets the current trigger action
   * @return trigger action set to spi bus
   */
  inline char*
  get_trigger_action () const
  {
    return m_trigger_action;
  }
  /**
   * Sets a new trigger action. Could be TRIGGER_FALLING or TRIGGER_RISING (check
   * defines of this header for Trigger Actions)
   * @param trigger is the new trigger action to set
   */
  inline void
  set_trigger_action (char* trigger)
  {
    m_trigger_action = trigger;
    set_trigger_type (m_pin_ms, m_trigger_action);
  }
  /**
   * Getter for the pin of the master select
   * @return the number of the pin of the master select
   */
  inline uint8_t
  get_pin_ms () const
  {
    return m_pin_ms;
  }
  /**
   * Destructor
   */
  ~SPIMasterSelect ();

};
#endif
