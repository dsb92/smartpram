/* ============================================================================
 *
 * Project: Smart Pram
 * Zigbee SPI driver for the PSoC3
 *
 * Author: Kjeld Laursen
 * October 2013
 *
 * ============================================================================
 */

// File includes
#include <project.h>

// Zigbee SPI register read and write functions
uint8 zigbee_short_read(uint8);
uint8 zigbee_long_read(uint16);
void zigbee_short_write(uint8, uint8);
void zigbee_long_write(uint16, uint8);

// Zigbee hardware port functions and other platform specific funtions
void zigbee_set_resetpin(uint8);
void zigbee_set_wakepin(uint8);
void zigbee_delay_us(uint16);

//******************************************************************************
// End of file
//******************************************************************************
