/* ============================================================================
 *
 * Project: Smart Pram
 * Zigbee SPI driver for the Devkit8000
 *
 * Author: Kjeld Laursen
 * November 2013
 *
 * ============================================================================
 */

// File includes
#include <linux/spi/spi.h>
#include <linux/err.h>
#include <plat/mcspi.h>
#include <linux/cpld-gpio.h>
#include <linux/delay.h>
#include <linux/module.h>

// Constants
#define LOGLEVEL 	KERN_NOTICE	// Sets the log level for printk()
#define GPIO_nRESET 	135		// Zigbee reset pin
#define GPIO_WAKE 	133		// Zigbee wakeup pin

// Compiler doesn't know uint8, uint16. so typedef.
typedef u8 uint8;
typedef u16 uint16;

// Zigbee SPI register read and write functions
uint8 zigbee_short_read(uint8 adr);
uint8 zigbee_long_read(uint16 adr);
void zigbee_short_write(uint8 adr, uint8 dat);
void zigbee_long_write(uint16 adr, uint8 dat);

// Zigbee hardware port functions and other platform specific funtions
void zigbee_set_resetpin(uint8 level);
void zigbee_set_wakepin(uint8 level);
void zigbee_delay_us(uint16 us);

// Initialize and exit functions
int zigbee_SPI_init(void);
void zigbee_SPI_exit(void);

//******************************************************************************
// End of file
//******************************************************************************
