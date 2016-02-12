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

// include own header file
#include "zigbee_SPI_Devkit8000.h"

// Global varibles
static struct spi_device *zigbee_SPI_device = NULL;

//******************************************************************************
// Zigbee SPI register read and write functions
//******************************************************************************

// Read short register
uint8 zigbee_short_read(uint8 adr)
{
    struct spi_transfer t[2];
    struct spi_message m;
    uint8 dat = 0;
    // Check for valid spi device 
    if(!zigbee_SPI_device)
	return 0;				// Unable to return an error code
    // Init Message
    memset(t, 0, sizeof(t)); 
    spi_message_init(&m);
    m.spi = zigbee_SPI_device;
    // SPI address setup
    adr = adr << 1;				// Setup address for read
    // Configure TX/RX buffers
    t[0].tx_buf = &adr;
    t[0].rx_buf = NULL;
    t[0].len = 1; 				// Allocate 1 bytes in tx buffer
    spi_message_add_tail(&t[0], &m);
    t[1].tx_buf = NULL;
    t[1].rx_buf = &dat;
    t[1].len = 1; 				// Allocate 1 bytes in tx buffer
    spi_message_add_tail(&t[1], &m);
    // Transmit SPI Data (blocking)
    spi_sync(m.spi, &m);
    return dat;
}

// Read long register
uint8 zigbee_long_read(uint16 adr)
{
    struct spi_transfer t[3];
    struct spi_message m;
    uint8 adrMSB, adrLSB;
    uint8 dat = 0;
    // Check for valid spi device 
    if(!zigbee_SPI_device)
	return 0;				// Unable to return an error code
    // Init Message
    memset(t, 0, sizeof(t)); 
    spi_message_init(&m);
    m.spi = zigbee_SPI_device;
    // SPI address setup
    adr = (adr << 5) | (1 << 15);		// Setup address for read
    adrMSB = adr >> 8;				// Setup address MSB
    adrLSB = adr;				// Setup address LSB
    // Configure TX/RX buffers
    t[0].tx_buf = &adrMSB;
    t[0].rx_buf = NULL;
    t[0].len = 1; 				// Allocate 1 bytes in tx buffer
    spi_message_add_tail(&t[0], &m);
    t[1].tx_buf = &adrLSB;
    t[1].rx_buf = NULL;
    t[1].len = 1; 				// Allocate 1 bytes in tx buffer
    spi_message_add_tail(&t[1], &m);
    t[2].tx_buf = NULL;
    t[2].rx_buf = &dat;
    t[2].len = 1; 				// Allocate 1 bytes in tx buffer
    spi_message_add_tail(&t[2], &m);
    // Transmit SPI Data (blocking)
    spi_sync(m.spi, &m);
    return dat;
}

// Write short register
void zigbee_short_write(uint8 adr, uint8 dat)
{
    struct spi_transfer t[2];
    struct spi_message m;
    // Check for valid spi device 
    if(!zigbee_SPI_device)
	return;					// Unable to return an error code
    // Init Message
    memset(t, 0, sizeof(t)); 
    spi_message_init(&m);
    m.spi = zigbee_SPI_device;
    // SPI address setup
    adr = (adr << 1) | 1;			// Setup address for write
    // Configure TX/RX buffers
    t[0].tx_buf = &adr;
    t[0].rx_buf = NULL;
    t[0].len = 1; 				// Allocate 1 bytes in tx buffer
    spi_message_add_tail(&t[0], &m);
    t[1].tx_buf = &dat;
    t[1].rx_buf = NULL;
    t[1].len = 1; 				// Allocate 1 bytes in tx buffer
    spi_message_add_tail(&t[1], &m);
    // Transmit SPI Data (blocking)
    spi_sync(m.spi, &m);
    return;
}

// Write long register
void zigbee_long_write(uint16 adr, uint8 dat)
{
    struct spi_transfer t[3];
    struct spi_message m;
    uint8 adrMSB, adrLSB;
    // Check for valid spi device 
    if(!zigbee_SPI_device)
	return;					// Unable to return an error code
    // Init Message
    memset(t, 0, sizeof(t)); 
    spi_message_init(&m);
    m.spi = zigbee_SPI_device;
    // SPI address setup
    adr = (adr << 5) | (1 << 15) | (1 << 4);    // Setup address for write
    adrMSB = adr >> 8;				// Setup address MSB
    adrLSB = adr;				// Setup address LSB
    // Configure TX/RX buffers
    t[0].tx_buf = &adrMSB;
    t[0].rx_buf = NULL;
    t[0].len = 1; 				// Allocate 1 bytes in tx buffer
    spi_message_add_tail(&t[0], &m);
    t[1].tx_buf = &adrLSB;
    t[1].rx_buf = NULL;
    t[1].len = 1; 				// Allocate 1 bytes in tx buffer
    spi_message_add_tail(&t[1], &m);
    t[2].tx_buf = &dat;
    t[2].rx_buf = NULL;
    t[2].len = 1; 				// Allocate 1 bytes in tx buffer
    spi_message_add_tail(&t[2], &m);
    // Transmit SPI Data (blocking)
    spi_sync(m.spi, &m);
    return;
}

//******************************************************************************
// Zigbee hardware port functions and other platform specific funtions
//******************************************************************************

// Set the reset pin to high or low
void zigbee_set_resetpin(uint8 level)
{
    if( level == 0 )
	cpld_gpio_set_value(GPIO_nRESET, 0);
    else
	cpld_gpio_set_value(GPIO_nRESET, 1);
}

// Set the wake pin to high or low
void zigbee_set_wakepin(uint8 level)
{
    if( level == 0 )
	cpld_gpio_set_value(GPIO_WAKE, 0);
    else
	cpld_gpio_set_value(GPIO_WAKE, 1);
}

// Software delay in micro seconds
void zigbee_delay_us(uint16 us)
{
	udelay(us);
}

//******************************************************************************
// Initialize and exit functions
//******************************************************************************

// Prope funciton
static int __devinit zigbee_SPI_probe(struct spi_device *spi)
{
    int err=0;
    spi->bits_per_word = 8;  
    spi_setup(spi);
    zigbee_SPI_device = spi;  
    return err;
}

// Remove SPI device
static int __devexit zigbee_SPI_remove(struct spi_device *spi)
{
    printk(LOGLEVEL "Zigbee SPI driver has been removed while in use\n");
    zigbee_SPI_device = 0;
    return 0;
}

// SPI driver struct
static struct spi_driver zigbee_SPI_driver = {
    .driver = {
	.owner = THIS_MODULE,
	.name = "zigbee_module",
	.bus = &spi_bus_type,
    },
    .probe = zigbee_SPI_probe,
    .remove = __devexit_p(zigbee_SPI_remove),
};

// Initialize SPI port and CPLD_GPIO's
int zigbee_SPI_init(void)
{
    int err;
    // Initialize SPI port
    err = spi_register_driver(&zigbee_SPI_driver);
    if(err < 0)
    {
	printk(LOGLEVEL "Error %d registering the zigbee SPI driver\n", err);
	goto err_spi_register_fail;
    }
    if (zigbee_SPI_device == NULL)
    {
	spi_unregister_driver(&zigbee_SPI_driver); 
	err = -ENODEV;
	goto err_no_spi_device;
    }
    // Initialize CPLD_GPIO's
    err = cpld_gpio_request(GPIO_nRESET);
    if (err != 0)
    {
	printk(LOGLEVEL "cpld_gpio_request failed, GPIO_nRESET, errorcode: %d \n", err);
	goto err_gpio_req_GPIO_nRESET_fail;
    }
    err = cpld_gpio_request(GPIO_WAKE);
    if (err != 0)
    {
	printk(LOGLEVEL "cpld_gpio_request failed, GPIO_WAKE, errorcode: %d \n", err);
	goto err_gpio_req_GPIO_WAKE_fail;
    }
    err = cpld_gpio_direction_output(GPIO_nRESET, 0);
    if (err != 0)
    {
	printk(LOGLEVEL "cpld_gpio_direction_output failed, GPIO_nRESET, errorcode: %d \n", err);
	goto err_gpio_dir_fail;
    }
    err = cpld_gpio_direction_output(GPIO_WAKE, 0);
    if (err != 0)
    {
	printk(LOGLEVEL "cpld_gpio_direction_output failed, GPIO_WAKE, errorcode: %d \n", err);
	goto err_gpio_dir_fail;
    }
    cpld_gpio_set_value(GPIO_nRESET, 1);	// Default value doesn't allways stick
    cpld_gpio_set_value(GPIO_WAKE, 1);
    return 0;
    // Error handling
err_gpio_dir_fail:
    cpld_gpio_free(GPIO_WAKE);
err_gpio_req_GPIO_WAKE_fail:
    cpld_gpio_free(GPIO_nRESET);
err_gpio_req_GPIO_nRESET_fail:
    spi_unregister_driver(&zigbee_SPI_driver);
err_no_spi_device:
err_spi_register_fail:
    return err;
}

// Exit SPI port and CPLD_GPIO's
void zigbee_SPI_exit(void)
{
    cpld_gpio_free(GPIO_WAKE);
    cpld_gpio_free(GPIO_nRESET);
    spi_unregister_driver(&zigbee_SPI_driver);
}

//******************************************************************************
// End of file
//******************************************************************************
