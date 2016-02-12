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

// include own header file
#include <zigbee_SPI_PSoC3.h>

//******************************************************************************
// Zigbee SPI register read and write functions
//******************************************************************************

// Read short register
uint8 zigbee_short_read(uint8 adr)
{
    adr = adr << 1;								// Setup address for read
    SPI_WriteTxData(adr);						// Send SPI address
    SPI_WriteTxData(0x00);                      // Send dummy byte for read
    while( !(SPI_ReadTxStatus() & 0x01));       // while not: SPI-done, wait
    return SPI_ReadRxData();					// Read SPI data
}

// Read long register
uint8 zigbee_long_read(uint16 adr)
{
    uint8 adrMSB, adrLSB;
    adr = (adr << 5) | (1 << 15);				// Setup address for read
    adrMSB = adr >> 8;							// Setup address MSB
    adrLSB = adr;								// Setup address LSB
    SPI_WriteTxData(adrMSB);					// Send SPI address MSB
    SPI_WriteTxData(adrLSB);					// Send SPI address LSB
    SPI_WriteTxData(0x00);                      // Send dummy byte for read
    while( !(SPI_ReadTxStatus() & 0x01));       // while not: SPI-done, wait
    return SPI_ReadRxData();					// Read SPI data
}

// Write short register
void zigbee_short_write(uint8 adr, uint8 dat)
{
    adr = (adr << 1) | 1;						// Setup address for write
    SPI_WriteTxData(adr);						// Send SPI address
    SPI_WriteTxData(dat);						// Send SPI data
    while( !(SPI_ReadTxStatus() & 0x01));       // while not: SPI-done, wait
}

// Write long register
void zigbee_long_write(uint16 adr, uint8 dat)
{
    uint8 adrMSB, adrLSB;
    adr = (adr << 5) | (1 << 15) | (1 << 4);    // Setup address for write
    adrMSB = adr >> 8;							// Setup address MSB
    adrLSB = adr;								// Setup address LSB
    SPI_WriteTxData(adrMSB);					// Send SPI address MSB
    SPI_WriteTxData(adrLSB);					// Send SPI address LSB
    SPI_WriteTxData(dat);						// Send SPI data
    while( !(SPI_ReadTxStatus() & 0x01));       // while not: SPI-done, wait
}

//******************************************************************************
// Zigbee hardware port functions and other platform specific funtions
//******************************************************************************

// Set the reset pin to high or low
void zigbee_set_resetpin(uint8 level)
{
	if( level == 0 )
		nRESET_Write(0);
	else
		nRESET_Write(1);
}

// Set the wake pin to high or low
void zigbee_set_wakepin(uint8 level)
{
	if( level == 0 )
		WAKE_Write(0);
	else
		WAKE_Write(1);
}

// Software delay in micro seconds
void zigbee_delay_us(uint16 us)
{
	CyDelayUs(us);
}

//******************************************************************************
// End of file
//******************************************************************************
