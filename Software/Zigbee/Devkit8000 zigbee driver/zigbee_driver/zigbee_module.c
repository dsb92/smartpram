/* ============================================================================
 *
 * Project: Smart Pram
 * Zigbee kernel module driver for the Devkit8000.
 *
 * Author: Kjeld Laursen
 * November 2013
 *
 * ============================================================================
 */

// File includes
#include <linux/cpld-gpio.h> 
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/module.h>
#include <asm/errno.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include "zigbee_driver.h"

// Constants
#define LOGLEVEL	KERN_NOTICE	// Sets the log level for printk()
#define TX_LENGTH	128		// TX-fifo legth
#define RX_LENGTH	144		// RX-fifo legth
#define PAYlOAD_MAX	118		// Payload max length
#define DRIVER_MINOR	0		// Only minor nr. used in dynamic allocation.
#define DRIVER_COUNT	1		// Only one zigbee module should be present
#define DRIVER_NAME	"Zigbee_driver" // Driver name.
#define GPIO_INT	131		// Zigbee interrupt out pin
#define GPIO_INT_NAME	"GPIO_INT"	// Port name.
#define CLASS_NAME	"zigbee_module"	// The SysFS class name
#define DEVICE_NAME	"zigbee"	// The SysFS device name

// Prototypes
int driver_open(struct inode *inode, struct file *filep);
int driver_release(struct inode *inode, struct file *filep);
ssize_t driver_read(struct file *filep, char __user *buf, size_t count, loff_t *f_pos);
ssize_t driver_write(struct file *filep, const char __user *buf, size_t count, loff_t *f_pos);
static irqreturn_t driver_hard_irq_handler(int irq, void *dev_id);
static irqreturn_t driver_soft_irq_handler(int irq, void *dev_id);

// Global varibles
static dev_t devno;			// Variable to hold device numbers.
static struct cdev driver_cdev;		// Represents the char device
static signed int driver_irq_line;	// Number given to the IRQ, error if negative
static DECLARE_WAIT_QUEUE_HEAD( wq_rd );// Wait queue for the IRQ controlled read
static int flag_rd = 0;			// Flag associated with IRQ controlled read

struct file_operations driver_fops = {	// Drivers available fileoperations.
  .owner   		= THIS_MODULE,
  .read    		= driver_read,
  .write   		= driver_write,
  .open    		= driver_open,
  .release 		= driver_release };

static struct class *zigbee_class;	// SysFS class
static struct device *zigbee_device;	// SysFS device

//******************************************************************************
// SysFS - Zigbee configuration functions
//******************************************************************************

// Zigbee reset
static ssize_t zigbee_reset_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int data;
    sscanf(buf,"%i", &data);				// Convert string to integer
    if( data > 0 )					// Resets if data > 0
    {
	printk(LOGLEVEL "Zigbee module reset, passed data: %i\n", data);
	zigbee_reset();					// Reset the zigbee module
    }
    else
    {
	printk(LOGLEVEL "Zigbee module not reset, valid range > 0\n" );
	return -EINVAL;
    }
    return count;
}
// Zigbee attribute
static struct device_attribute zigbee_reset_attr =
    __ATTR(zigbee_reset, 0200, NULL, zigbee_reset_store);

// Zigbee set channel
static ssize_t zigbee_set_ch_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int data;
    sscanf(buf,"%i", &data);				// Convert string to integer
    if( (data >= 11) && (data <= 26) )
    {
	printk(LOGLEVEL "Zigbee module channel set to: %i\n", data);
	zigbee_set_ch((u8)data);
    }
    else
    {
	printk(LOGLEVEL "Zigbee module channel not set, valid range 11 - 26\n" );
	return -EINVAL;
    }
    return count;
}
// Zigbee attribute
static struct device_attribute zigbee_set_ch_attr =
    __ATTR(zigbee_set_ch, 0200, NULL, zigbee_set_ch_store);

// Zigbee set TX-power
static ssize_t zigbee_set_TXpower_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int data;
    sscanf(buf,"%i", &data);				// Convert string to integer
    if( (data >= 0) && (data <= 31) )
    {
	printk(LOGLEVEL "Zigbee module TX-power set to: %i\n", data);
	zigbee_set_TXpower((u8)data);
    }
    else
    {
	printk(LOGLEVEL "Zigbee module TX-power not set, valid range 0 - 31\n" );
	return -EINVAL;
    }
    return count;
}
// Zigbee attribute
static struct device_attribute zigbee_set_TXpower_attr =
    __ATTR(zigbee_set_TXpower, 0200, NULL, zigbee_set_TXpower_store);

// Zigbee set CCA mode, Carrier Sense, Energy Detection
static ssize_t zigbee_set_CCA_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int data[3];
    sscanf(buf,"%i %i %i", &data[0], &data[1], &data[2]);// Convert string to integers
    if( (data[0] >= 1) && (data[0] <= 3) &&
	(data[1] >= 0) && (data[1] <= 15) )
    {
	printk(LOGLEVEL "Zigbee module CCA mode set: %i, CS: %i, ED: %i\n", data[0], data[1], data[2]);
	zigbee_set_CCA((u8)data[0], (u8)data[1], (u8)data[2]);
    }
    else
    {
	printk(LOGLEVEL "Zigbee module CCA mode not set, valid ranges: CCAmode: 1 - 3, CS: 0 - 15, ED: 0 - 255\n" );
	return -EINVAL;
    }
    return count;
}
// Zigbee attribute
static struct device_attribute zigbee_set_CCA_attr =
    __ATTR(zigbee_set_CCA, 0200, NULL, zigbee_set_CCA_store);

// Zigbee set RSSI mode
static ssize_t zigbee_set_RSSI_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int data;
    sscanf(buf,"%i", &data);				// Convert string to integer
    if( (data >= 0) && (data <= 1) )
    {
	printk(LOGLEVEL "Zigbee module set RSSI-mode: %i\n", data);
	zigbee_set_RSSI((u8)data);
    }
    else
    {
	printk(LOGLEVEL "Zigbee module RSSI-mode not set, valid range: 0 - 1\n" );
	return -EINVAL;
    }
    return count;
}
// Zigbee attribute
static struct device_attribute zigbee_set_RSSI_attr =
    __ATTR(zigbee_set_RSSI, 0200, NULL, zigbee_set_RSSI_store);

// Zigbee set non-beacon mode
static ssize_t zigbee_set_nonbeacon_mode_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int data;
    sscanf(buf,"%i", &data);				// Convert string to integer
    if( (data >= 0) && (data <= 1) )
    {
	printk(LOGLEVEL "Zigbee module non-beacon mode set: %i\n", data);
	zigbee_set_nonbeacon_mode((u8)data);
    }
    else
    {
	printk(LOGLEVEL "Zigbee module non-beacon mode not set, valid range: 0 - 1\n" );
	return -EINVAL;
    }
    return count;
}
// Zigbee attribute
static struct device_attribute zigbee_set_nonbeacon_mode_attr =
    __ATTR(zigbee_set_nonbeacon_mode, 0200, NULL, zigbee_set_nonbeacon_mode_store);

// Zigbee set reception mode
static ssize_t zigbee_set_reception_mode_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int data;
    sscanf(buf,"%i", &data);				// Convert string to integer
    if( (data >= 0) && (data <= 2) )
    {
	printk(LOGLEVEL "Zigbee module reception mode set: %i\n", data);
	zigbee_set_reception_mode((u8)data);
    }
    else
    {
	printk(LOGLEVEL "Zigbee module reception mode not set, valid range: 0 - 2\n" );
	return -EINVAL;
    }
    return count;
}
// Zigbee attribute
static struct device_attribute zigbee_set_reception_mode_attr =
    __ATTR(zigbee_set_reception_mode, 0200, NULL, zigbee_set_reception_mode_store);

// Zigbee init
static ssize_t zigbee_init_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int data;
    sscanf(buf,"%i", &data);				// Convert string to integer
    if( data > 0)
    {
	printk(LOGLEVEL "Zigbee module initialized, passed data: %i\n", data);
	zigbee_init();
    }
    else
    {
	printk(LOGLEVEL "Zigbee module not initialized, valid range > 0\n" );
	return -EINVAL;
    }
    return count;
}
// Zigbee attribute
static struct device_attribute zigbee_init_attr =
    __ATTR(zigbee_init, 0200, NULL, zigbee_init_store);

// Zigbee flush RX-fifo
static ssize_t zigbee_flush_RXfifo_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int data;
    sscanf(buf,"%i", &data);				// Convert string to integer
    if( data > 0)
    {
	printk(LOGLEVEL "Zigbee module RX-fifo flushed, passed data: %i\n", data);
	zigbee_flush_RXfifo();
    }
    else
    {
	printk(LOGLEVEL "Zigbee module RX-fifo not flushed, valid range > 0\n" );
	return -EINVAL;
    }
    return count;
}
// Zigbee attribute
static struct device_attribute zigbee_flush_RXfifo_attr =
    __ATTR(zigbee_flush_RXfifo, 0200, NULL, zigbee_flush_RXfifo_store);

// Zigbee source PAN-id
static ssize_t zigbee_source_PANid_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int i;
    int datain[2];
    u8 dataout[2];
    sscanf(buf,"%i %i", &datain[0], &datain[1]);		// Convert string to integer
    for( i = 0; i < 2; i++ )
	dataout[i] = (u8)datain[i];				// Convert from int to u8
    printk(LOGLEVEL "Zigbee module source PAN-id set: %i %i\n", dataout[0], dataout[1]);
    zigbee_source_PANid(dataout);
    return count;
}
// Zigbee attribute
static struct device_attribute zigbee_source_PANid_attr =
    __ATTR(zigbee_source_PANid, 0200, NULL, zigbee_source_PANid_store);

// Zigbee source short address
static ssize_t zigbee_source_shortadr_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int i;
    int datain[2];
    u8 dataout[2];
    sscanf(buf,"%i %i", &datain[0], &datain[1]);		// Convert string to integer
    for( i = 0; i < 2; i++ )
	dataout[i] = (u8)datain[i];				// Convert from int to u8
    printk(LOGLEVEL "Zigbee module source short address set: %i %i\n", dataout[0], dataout[1]);
    zigbee_source_shortadr(dataout);
    return count;
}
// Zigbee attribute
static struct device_attribute zigbee_source_shortadr_attr =
    __ATTR(zigbee_source_shortadr, 0200, NULL, zigbee_source_shortadr_store);

// Zigbee source long address
static ssize_t zigbee_source_longadr_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int i;
    int datain[8];
    u8 dataout[8];
    sscanf(buf,"%i %i %i %i %i %i %i %i", &datain[0], &datain[1], &datain[2], &datain[3],
	    &datain[4], &datain[5], &datain[6], &datain[7] );	// Convert string to integer
    for( i = 0; i < 8; i++ )
	dataout[i] = (u8)datain[i];				// Convert from int to u8
    printk(LOGLEVEL "Zigbee module source long address set: %i %i %i %i %i %i %i %i\n",
	    dataout[0], dataout[1], dataout[2], dataout[3], dataout[4], dataout[5], dataout[6], dataout[7] );
    zigbee_source_longadr(dataout);
    return count;
}
// Zigbee attribute
static struct device_attribute zigbee_source_longadr_attr =
    __ATTR(zigbee_source_longadr, 0200, NULL, zigbee_source_longadr_store);

// Zigbee destination PAN-id
static ssize_t zigbee_destination_PANid_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int i;
    int datain[2];
    u8 dataout[2];
    sscanf(buf,"%i %i", &datain[0], &datain[1]);		// Convert string to integer
    for( i = 0; i < 2; i++ )
	dataout[i] = (u8)datain[i];				// Convert from int to u8
    printk(LOGLEVEL "Zigbee module destination PAN-id set: %i %i\n", dataout[0], dataout[1]);
    zigbee_destination_PANid(dataout);
    return count;
}
// Zigbee attribute
static struct device_attribute zigbee_destination_PANidattr =
    __ATTR(zigbee_destination_PANid, 0200, NULL, zigbee_destination_PANid_store);

// Zigbee destination short address
static ssize_t zigbee_destination_shortadr_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int i;
    int datain[2];
    u8 dataout[2];
    sscanf(buf,"%i %i", &datain[0], &datain[1]);		// Convert string to integer
    for( i = 0; i < 2; i++ )
	dataout[i] = (u8)datain[i];				// Convert from int to u8
    printk(LOGLEVEL "Zigbee module destination short address set: %i %i\n", dataout[0], dataout[1]);
    zigbee_destination_shortadr(dataout);
    return count;
}
// Zigbee attribute
static struct device_attribute zigbee_destination_shortadr_attr =
    __ATTR(zigbee_destination_shortadr, 0200, NULL, zigbee_destination_shortadr_store);

// Zigbee destination long address
static ssize_t zigbee_destination_longadr_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int i;
    int datain[8];
    u8 dataout[8];
    sscanf(buf,"%i %i %i %i %i %i %i %i", &datain[0], &datain[1], &datain[2], &datain[3],
	    &datain[4], &datain[5], &datain[6], &datain[7] );	// Convert string to integer
    for( i = 0; i < 8; i++ )
	dataout[i] = (u8)datain[i];				// Convert from int to u8
    printk(LOGLEVEL "Zigbee module destination long address set: %i %i %i %i %i %i %i %i\n",
	    dataout[0], dataout[1], dataout[2], dataout[3], dataout[4], dataout[5], dataout[6], dataout[7] );
    zigbee_destination_longadr(dataout);
    return count;
}
// Zigbee attribute
static struct device_attribute zigbee_destination_longadr_attr =
    __ATTR(zigbee_destination_longadr, 0200, NULL, zigbee_destination_longadr_store);
    
// Zigbee status IRQ
static ssize_t zigbee_status_IRQ_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    int stat_IRQ;
    stat_IRQ = zigbee_status_IRQ();
    return scnprintf(buf, PAGE_SIZE, "%i\n", stat_IRQ);
}
// Zigbee attribute
static struct device_attribute zigbee_status_IRQ_attr =
    __ATTR(zigbee_status_IRQ, 0444, zigbee_status_IRQ_show, NULL);

// Zigbee status TX
static ssize_t zigbee_status_TX_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    int stat_TX;
    stat_TX = zigbee_status_TX();
    return scnprintf(buf, PAGE_SIZE, "%i\n", stat_TX);
}
// Zigbee attribute
static struct device_attribute zigbee_status_TX_attr =
    __ATTR(zigbee_status_TX, 0444, zigbee_status_TX_show, NULL);

//******************************************************************************
// Initialize and exit
//******************************************************************************
static int __zigbee_init(void)
{
    int err, temp;
    // Initialize zigbee SPI port and associated ports
    err = zigbee_SPI_init();
    if(err != 0)
    {
	printk(LOGLEVEL "Error %d initializing the zigbee SPI driver\n", err);
	goto err_zigbee_init_fail;
    }
    // Initialize CPLD_GPIO's
    // Request GPIO
    err = cpld_gpio_request(GPIO_INT);
    if (err != 0)
    {
	printk(LOGLEVEL "cpld_gpio_request failed: %s, errorcode: %d\n", GPIO_INT_NAME, err);
	goto err_gpio_req_fail;
    }
    // Set GPIO direction (in)
    err = cpld_gpio_direction_input(GPIO_INT);
    if (err != 0)
    {
	printk(LOGLEVEL "cpld_gpio_direction_output failed: %s, errorcode: %d\n", GPIO_INT_NAME, err);
	goto err_gpio_dir_fail;
    }
    // map GPIO numbers to IRQ numbers
    driver_irq_line = cpld_gpio_to_irq(GPIO_INT);
    if (driver_irq_line < 0)
    {
	err = driver_irq_line;
	printk(LOGLEVEL "cpld_gpio_to_irq failed: %s, errorcode: %d\n", GPIO_INT_NAME, err);
	goto err_gpio_to_irq_fail;
    }
    // Request threaded IRQ
    err = request_threaded_irq(driver_irq_line, driver_hard_irq_handler, driver_soft_irq_handler, IRQF_TRIGGER_FALLING, DRIVER_NAME, &devno);
    if (err != 0)
    {
	printk(LOGLEVEL "request_irq failed: %s, errorcode: %d \n", GPIO_INT_NAME, err);
	goto err_gpio_req_irq_fail;
    }
    // Dynamic allocation of major number.
    err = alloc_chrdev_region(&devno, DRIVER_MINOR, DRIVER_COUNT, DRIVER_NAME);
    if (err != 0)
    {
	printk(LOGLEVEL "alloc_chrdev_region failed, errorcode: %d\n", err);
	goto err_alloc_chrdev_fail;
    }
    // Cdev Init
    cdev_init(&driver_cdev, &driver_fops);
    // Add Cdev
    err = cdev_add(&driver_cdev, devno, DRIVER_COUNT);
    if (err != 0)
    {
	printk(LOGLEVEL "cdev_add failed, errorcode: %d\n", err);
	goto err_cdev_add_fail;
    }
    // SysFS
    // Create class
    zigbee_class = class_create(THIS_MODULE, CLASS_NAME);
    err = IS_ERR(zigbee_class);
    if(err != 0)
    {
	printk(LOGLEVEL "class_create failed: %s, errorcode: %d \n", CLASS_NAME, err);
	goto err_class_create_fail;
    }
    // Create device
    zigbee_device = device_create(zigbee_class, NULL, devno, NULL, DEVICE_NAME);
    err = IS_ERR(zigbee_device);
    if(err != 0)
    {
	printk(LOGLEVEL "device_create failed: %s, errorcode: %d \n", DEVICE_NAME, err);
	goto err_device_create_fail;
    }
    // Create file - return not defined, so just dump in temp
    temp = device_create_file(zigbee_device, &zigbee_reset_attr);
    temp = device_create_file(zigbee_device, &zigbee_set_ch_attr);
    temp = device_create_file(zigbee_device, &zigbee_set_TXpower_attr);
    temp = device_create_file(zigbee_device, &zigbee_set_CCA_attr);
    temp = device_create_file(zigbee_device, &zigbee_set_RSSI_attr);
    temp = device_create_file(zigbee_device, &zigbee_set_nonbeacon_mode_attr);
    temp = device_create_file(zigbee_device, &zigbee_set_reception_mode_attr);
    temp = device_create_file(zigbee_device, &zigbee_init_attr);
    temp = device_create_file(zigbee_device, &zigbee_flush_RXfifo_attr);
    temp = device_create_file(zigbee_device, &zigbee_source_PANid_attr);
    temp = device_create_file(zigbee_device, &zigbee_source_shortadr_attr);
    temp = device_create_file(zigbee_device, &zigbee_source_longadr_attr);
    temp = device_create_file(zigbee_device, &zigbee_destination_PANidattr);
    temp = device_create_file(zigbee_device, &zigbee_destination_shortadr_attr);
    temp = device_create_file(zigbee_device, &zigbee_destination_longadr_attr);
    temp = device_create_file(zigbee_device, &zigbee_status_IRQ_attr);
    temp = device_create_file(zigbee_device, &zigbee_status_TX_attr);
    // Startup the zigbee module with default settings
    zigbee_reset();		// Hardware reset of the zigbee module
    zigbee_init();		// Initializes the zigbee module with defualt settings
    zigbee_status_IRQ();	// To clear any pending IRQ
    // Driver initialized succesfully.
    printk(LOGLEVEL "%s started succesfully. MAJOR: %d  MINOR: %d  IRQ: %d\n", DRIVER_NAME, MAJOR(devno), MINOR(devno), driver_irq_line);
    return 0;
    
    // Error handling, cleanup routines.
err_device_create_fail:
    class_destroy(zigbee_class);
err_class_create_fail:
    cdev_del(&driver_cdev);
err_cdev_add_fail:
    unregister_chrdev_region(devno, DRIVER_COUNT);
err_alloc_chrdev_fail:
    free_irq(driver_irq_line, &devno);
err_gpio_req_irq_fail:
err_gpio_to_irq_fail:  
err_gpio_dir_fail:
    cpld_gpio_free(GPIO_INT);
err_gpio_req_fail:
    zigbee_SPI_exit();
err_zigbee_init_fail:
    printk(LOGLEVEL "%s failed to start. Cleanup done, exiting.\n", DRIVER_NAME);  
    return err;
}

static void __zigbee_exit(void)
{
    device_remove_file(zigbee_device, &zigbee_reset_attr);
    device_remove_file(zigbee_device, &zigbee_set_ch_attr);
    device_remove_file(zigbee_device, &zigbee_set_TXpower_attr);
    device_remove_file(zigbee_device, &zigbee_set_CCA_attr);
    device_remove_file(zigbee_device, &zigbee_set_RSSI_attr);
    device_remove_file(zigbee_device, &zigbee_set_nonbeacon_mode_attr);
    device_remove_file(zigbee_device, &zigbee_set_reception_mode_attr);
    device_remove_file(zigbee_device, &zigbee_init_attr);
    device_remove_file(zigbee_device, &zigbee_flush_RXfifo_attr);
    device_remove_file(zigbee_device, &zigbee_source_PANid_attr);
    device_remove_file(zigbee_device, &zigbee_source_shortadr_attr);
    device_remove_file(zigbee_device, &zigbee_source_longadr_attr);
    device_remove_file(zigbee_device, &zigbee_destination_PANidattr);
    device_remove_file(zigbee_device, &zigbee_destination_shortadr_attr);
    device_remove_file(zigbee_device, &zigbee_destination_longadr_attr);
    device_remove_file(zigbee_device, &zigbee_destination_longadr_attr);
    device_remove_file(zigbee_device, &zigbee_status_IRQ_attr);
    device_remove_file(zigbee_device, &zigbee_status_TX_attr);
    
    device_destroy(zigbee_class, devno);		// Remove SysFS device
    class_destroy(zigbee_class);			// Remove SysFS class
    cdev_del(&driver_cdev);				// Delete Cdev
    unregister_chrdev_region(devno, DRIVER_COUNT);	// Unregister Device
    free_irq(driver_irq_line, &devno);			// Free IRQ
    cpld_gpio_free(GPIO_INT);				// Free CPLD GPIO
    zigbee_SPI_exit();					// Free SPI
}

//******************************************************************************
// Open and release
//******************************************************************************
int driver_open(struct inode *inode, struct file *filep)
{
    return 0;			// Nothing to do
}

int driver_release(struct inode *inode, struct file *filep)
{
    return 0;			// Nothing to do
}

//******************************************************************************
// Read and write
//******************************************************************************
ssize_t driver_read(struct file *filep, char __user *buf, size_t count, loff_t *f_pos)
{
    char Kbuffer[RX_LENGTH];			// data buffer i kernel
    int Kbuffer_len;				// length of data in buffer
    // Wait for IRQ_handler to be triggered
    wait_event_interruptible(wq_rd, flag_rd != 0);
    flag_rd = 0;				// Reset flag_rd
    // Read the RX-fifo
    Kbuffer_len = zigbee_read_payload_RXfifo(Kbuffer);
    // Get data length, and limit if needed
    Kbuffer_len = count < Kbuffer_len ? count : Kbuffer_len;
    // Copy from kernel to userspace
    if (copy_to_user(buf, Kbuffer, Kbuffer_len) != 0)
    {
	printk(LOGLEVEL "%s read failed.\n", DRIVER_NAME);
	return -1;
    }
    *f_pos += Kbuffer_len;
    return Kbuffer_len;				// Returns the number of transfered chars
}

ssize_t driver_write(struct file *filep, const char __user *buf, size_t count, loff_t *f_pos)
{
    char Kbuffer[TX_LENGTH];			// data buffer i kernel
    int Kbuffer_len = 0;			// length of data in buffer
    // Get data length, and limit if needed
    Kbuffer_len = count < PAYlOAD_MAX ? count : PAYlOAD_MAX;
    // Copy from userspace to kernel
    if ( copy_from_user(Kbuffer, buf, Kbuffer_len) != 0)
    {
      printk(LOGLEVEL "%s write failed.\n", DRIVER_NAME);
      return -1;
    }
    // Send payload to zigbee TX-fifo
    zigbee_write_payload_TXfifo(Kbuffer, (u8)Kbuffer_len);
    zigbee_transmit_TXfifo();
    *f_pos += Kbuffer_len;
    return Kbuffer_len;				// Returns the number of transfered chars
}

//******************************************************************************
// Interrupt
//******************************************************************************
static irqreturn_t driver_hard_irq_handler(int irq, void *dev_id)
{
    return IRQ_WAKE_THREAD;
}

static irqreturn_t driver_soft_irq_handler(int irq, void *dev_id)
{
    int stat_IRQ;
    stat_IRQ = zigbee_status_IRQ();
    if( (stat_IRQ & 0x08) > 0)		// RX-fifo, new data in RX-fifo
    {
	flag_rd = 1;
	wake_up_interruptible(&wq_rd);
    }  
    return IRQ_HANDLED;
}

//******************************************************************************
// Macros
//******************************************************************************

MODULE_AUTHOR("Kjeld Laursen");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Zigbee kernel module driver");

module_init(__zigbee_init);
module_exit(__zigbee_exit);

//******************************************************************************
// End of file
//******************************************************************************
