/* ============================================================================
 *
 * Project: Smart Pram
 * Hotplug SPI driver for the zigbee, for the Devkit8000.
 *
 * Author: Kjeld Laursen
 * November 2013
 *
 * ============================================================================
 */

// File includes
#include <linux/init.h>
#include <linux/module.h>
#include <linux/spi/spi.h>
#include <plat/mcspi.h>
#include <asm/uaccess.h>

// Constants
#define LOGLEVEL KERN_NOTICE		// Sets the log level for printk()

// Global varibles
static struct spi_device *slave_spi_device;

// OMAP CPU SPI controller config
static struct omap2_mcspi_device_config mcspi_config = {
  .turbo_mode	    = 0,
  .single_channel   = 1,  /* 0: slave, 1: master */
};

// Slave Device Config
struct spi_board_info slave_spi_board_info = {
  .modalias	    = "zigbee_module",	// chip type
  .bus_num	    = 1,
  .chip_select	    = 3,		// Chip select
  .max_speed_hz	    = 5000000,		// Theoretical max 10MHz
  .controller_data  = &mcspi_config,
  .mode             = SPI_MODE_0, 	// Clock mode
};

//******************************************************************************
// Init and exit functions
//******************************************************************************

// Initialize hotplug driver
static int __spi_device_init(void)
{
  int bus_num;
  struct spi_master *slaves_spi_master;

  printk(LOGLEVEL "Adding SPI Device: %s, bus: %i, chip-sel: %i\n", 
	 slave_spi_board_info.modalias, slave_spi_board_info.bus_num, slave_spi_board_info.chip_select);
  
  /* Add the slave SPI device to the SPI bus
   *
   * These methods are used to hot-plug spi devices.
   * SPI devices are by nature NOT hot-pluggable, as
   * they cannot be probed for functionality etc. SPI
   * devices are normally cold-plugged during boot, that
   * is, they are added in the board description file:
   * /arch/arm/march-omap2/devkit8000-board.c
   * Using this method we actually doing "hot" cold-plugging
   * adding devices using a kernel module.
   * Note that it is crusial that driver and device uses
   * the same name alias. If not, the device and driver
   * will not be paired and the probe method in the driver
   * not be called.
   */ 
  bus_num = slave_spi_board_info.bus_num;
  slaves_spi_master = spi_busnum_to_master(bus_num);
  slave_spi_device = spi_new_device(slaves_spi_master,
				    &slave_spi_board_info);
  if(slave_spi_device < 0) {
    printk(LOGLEVEL "Unsuccesful creating a new device\n");
    return -1;
  }
  
  return 0;
}

// Exit hotplug driver
static void __spi_device_exit(void)
{
  printk(LOGLEVEL "Removing SPI Device: %s, bus: %i, chip-sel: %i\n", 
	 slave_spi_board_info.modalias, slave_spi_board_info.bus_num, slave_spi_board_info.chip_select);
  spi_unregister_device(slave_spi_device);
}

//******************************************************************************
// Macros
//******************************************************************************

MODULE_AUTHOR("Kjeld Laursen");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Hotplug SPI driver for the zigbee module");

module_init(__spi_device_init);
module_exit(__spi_device_exit);

//******************************************************************************
// End of file
//******************************************************************************
