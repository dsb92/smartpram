/* ============================================================================
 *
 * Project: Smart Pram
 * Zigbee functionality driver
 *
 * Author: Kjeld Laursen
 * October 2013
 *
 * ============================================================================
 */

// include own header file
#include "zigbee_driver.h"

// Global varibles
static uint8 RSSI_status = 0;			// Indicates if RSSI is appended to RX-fifo
static uint8 sequence_number = 0;		// Increases with every payload transmission

// Addresses and the default value, (long address not used but included for future update of driver)
static uint8 source_PANID[2] = { 0x00, 0x00 };
static uint8 source_SHORTADR[2] = { 0x00, 0x00 };
static uint8 source_LONGADR[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static uint8 destination_PANID[2] = { 0x00, 0x00 };
static uint8 destination_SHORTADR[2] = { 0x00, 0x00 };
static uint8 destination_LONGADR[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	

//******************************************************************************
// Zigbee configuration functions
//******************************************************************************

// Hardware reset of the zigbee 
void zigbee_reset()
{
    zigbee_set_resetpin(0);				// reset zigbee(s)
    zigbee_set_wakepin(0);				// set low, not really used here
    zigbee_delay_us(250);				// wait 0,25ms
    zigbee_set_resetpin(1);				// release reset, zigbee(s) boot
    zigbee_delay_us(2250);				// wait 2,25ms, ensures proper bootup
}

// Select wireless channel, valid range is 11 - 26
// Channel 11 - 26
void zigbee_set_ch(uint8 CH)
{
	uint8 temp;
	if ( (CH < 11) || (CH > 26) )		// Check for invalid value
		CH = 11;						// Default channel set to 11
	CH = ((CH - 11) << 4) | 0x03;		// Prepare data for register
	zigbee_long_write(0x200, CH);		// RFCON0
	temp = zigbee_short_read(0x36);		// RFCTL - save old value
	temp = (temp & 0xF8) | 0x04;		// updated value, RF-state = reset
	zigbee_short_write(0x36, temp);		// RFCTL - write updated value
	temp = temp & 0xF8;					// updated value, RF-state = normal
	zigbee_short_write(0x36, temp);		// RFCTL - write updated value
	zigbee_delay_us(200);						// Wait minimum 192us
}

// Set transmit power, valid range is 0 - 31
// TX-power 0 - 31
void zigbee_set_TXpower(uint8 power)
{
	if ( power > 31 )					// Check for invalid value
		power = 31;						// Default Transmit power set to 31
	power = (!power) << 3;				// Prepare data for register
	zigbee_long_write(0x203, power);	// RFCON3 - write new value
}

// Set Clear Channel Assessment
// CCA-mode 1 - 3, Carrier Sense 0 - 15, Energy Detection 0 - 255
void zigbee_set_CCA(uint8 CCAmode, uint8 CS, uint8 ED)
{
	uint8 temp;
	if ( (CCAmode > 3) || (CCAmode < 1) )	// Check for invalid value
		CCAmode = 1;						// Default CCA-mode set to mode 1 (2)
	if ( CS > 0x0F )						// Check for invalid value
		CS = 0x0E;							// Default carrier sense set to 14
	
	switch( CCAmode ){
		case 1:								// CCA-mode 1, Energy threshold only
			temp = 0x80 | (0x0E << 2);		// update value
			zigbee_short_write(0x3A, temp);	// BBREG2 - CCA-mode and default carrier sense 
			zigbee_short_write(0x3F, ED);	// CCAEDTH - energy threshold
			break;
		case 2:								// CCA-mode 2, Carrier sense only
			temp = 0x40 | (CS << 2);		// update value
			zigbee_short_write(0x3A, temp);	// BBREG2 - CCA-mode and carrier sense
			zigbee_short_write(0x3F, 0x60);	// CCAEDTH - default energy threshold
			break;
		case 3:								// CCA-mode 3, Carrier sense with energy threshold
			temp = 0xC0 | (CS << 2);		// update value
			zigbee_short_write(0x3A, temp);	// BBREG2 - CCA-mode and carrier sense
			zigbee_short_write(0x3F, ED);	// CCAEDTH - energy threshold
			break;
	}
}
	
// Set RSSI automatic mode
// 0 = RSSI OFF, 1 = RSSI ON
void zigbee_set_RSSI(uint8 RSSImode)
{
	if ( RSSImode > 1 )						// Check for invalid value
		RSSImode = 1;						// Default RSSI-mode, append on
	
	switch( RSSImode ){
		case 0:								// Automatically append RSSI RX-fifo: OFF
			zigbee_short_write(0x3E, 0x00);	// BBREG6 - RSSIMODE2 = 0
			RSSI_status = 0;				// Reset gloabal variable
			break;
		case 1:								// Automatically append RSSI RX-fifo: ON
			zigbee_short_write(0x3E, 0x40);	// BBREG6 - RSSIMODE2 = 1
			RSSI_status = 1;				// Set gloabal variable
			break;
	}
}

// Set non-beacon mode, device or PAN coordinator
// 0 = device, 1 = PAN coordinator
void zigbee_set_nonbeacon_mode(uint8 beacon_mode)
{
	uint8 temp;
	if ( beacon_mode > 1 )					// Check for invalid value
		beacon_mode = 0;					// Default non-beacon mode
	
	temp = zigbee_short_read(0x00);			// RXMCR - save old value
	switch( beacon_mode ){
		case 0:								// Non-beacon device
			temp = (temp & 0x03) | 0x00;	// update value
			zigbee_short_write(0x00, temp);	// RXMCR - new updated value
			zigbee_short_write(0x11, 0x1C);	// TXMCR - set unslotted mode
			break;
		case 1:								// Non-beacon PAN coordinator
			temp = (temp & 0x03) | 0x80;	// update value
			zigbee_short_write(0x00, temp);	// RXMCR - new updated value
			zigbee_short_write(0x11, 0x1C);	// TXMCR - set unslotted mode
			zigbee_short_write(0x10, 0xFF);	// ORDOR - BO = 0xF and SO =0xF
			break;
	}
}

// Set Recption mode, CRC and MAC address error checking
// 0 = Normal, 1 = Promiscuous, 2 = Error
void zigbee_set_reception_mode(uint8 reception_mode)
{
	uint8 temp;
	if ( reception_mode > 2 )				// Check for invalid value
		reception_mode = 0;					// Default normal, full check
	
	temp = zigbee_short_read(0x00);			// RXMCR - save old value
	switch( reception_mode ){
		case 0:								// Normal, Full check of CRC and address
			temp = (temp & 0xFC) | 0x00;	// update value
			zigbee_short_write(0x00, temp);	// RXMCR - new updated value
			break;
		case 1:								// Promiscuous, accepts all packets with good CRC
			temp = (temp & 0xFC) | 0x01;	// update value
			zigbee_short_write(0x00, temp);	// RXMCR - new updated value
			break;
		case 2:								// Error, accepts packets with good of bad CRC
			temp = (temp & 0xFC) | 0x02;	// update value
			zigbee_short_write(0x00, temp);	// RXMCR - new updated value
			break;
	}
}

// Initialise the zigbee module
void zigbee_init()
{
	zigbee_short_write(0x2A, 0x07);		// SOFTRST - Perform software reset
	zigbee_short_write(0x18, 0x98);		// PACON2 - Initialize FIFOEN = 1 and TXONTS = 0x6
	zigbee_short_write(0x2E, 0x93);		// TXSTBL – Initialize RFSTBL = 0x9 ans MSIFS = 0x3
	zigbee_short_write(0x21, 0x7C);		// TXPEND - Initialize MLIFS = 0x1F
	zigbee_short_write(0x27, 0x38);		// TXTIME - Initialize TURNTIME = 0x3
	
	zigbee_long_write(0x200, 0x03);		// RFCON0 - Initialize RFOPT = 0x3, CHANNEL = 0x0
	zigbee_long_write(0x201, 0x02);		// RFCON1 - Initialize VCOOPT = 0x02
	zigbee_long_write(0x202, 0x80);		// RFCON2 - Enable PLL (PLLEN = 1)
	zigbee_long_write(0x206, 0x90);		// RFCON6 – Initialize TXFIL = 1 and 20MRECVR = 1
	zigbee_long_write(0x207, 0x80);		// RFCON7 – Initialize SLPCLKSEL = 0x2 (100 kHz Internal oscillator)
	zigbee_long_write(0x208, 0x10);		// RFCON8 – Initialize RFVCO = 1
	zigbee_long_write(0x220, 0x21);		// SLPCON1 – Initialize CLKOUTEN = 1 and SLPCLKDIV = 0x01
	
	zigbee_set_nonbeacon_mode(0);		// 0 = device, 1 = PAN coordinator
	zigbee_set_CCA(1, 0x0E, 0x60);		// CCA-mode 1 - 3, Carrier Sense 0 - 15, Energy Detection 0 - 255
	zigbee_set_RSSI(1);					// 0 = RSSI OFF, 1 = RSSI ON
	
	zigbee_short_write(0x32, 0xF6);		// INTCON - Interrupts RXIE, TXNIE enabled
	zigbee_long_write(0x211, 0x00);		// SLPCON0 - Interrupt edge = falling, sleep clock on
	
	zigbee_set_TXpower(31);				// TX-power 0 - 31
	zigbee_set_ch(11);					// Channel 11 - 26
	zigbee_set_reception_mode(0);		// 0 = Normal, 1 = Promiscuous, 2 = Error
	zigbee_source_PANid(source_PANID);			// Set PAN-id
	zigbee_source_shortadr(source_SHORTADR);	// Set short address
	zigbee_source_longadr(source_LONGADR);		// Set long address
	zigbee_short_write(0x0D, 0x01);		// RXFLUSH - Reset RX-fifo pointer and all valid frames are recieved
}

//******************************************************************************
// Set the zigbee's source and destination PAN id, short and long addresses
//******************************************************************************

// 2 byte PAN id, source
void zigbee_source_PANid(uint8 * PANid)
{
	zigbee_short_write(0x01, PANid[0]);				// PANIDL
	zigbee_short_write(0x02, PANid[1]);				// PANIDH
	source_PANID[0] = PANid[0];						// Save to local variable
	source_PANID[1] = PANid[1];						// Save to local variable
}

// 2 byte short address, source
void zigbee_source_shortadr(uint8 * shortadr)
{
	zigbee_short_write(0x03, shortadr[0]);			// SADRL
	zigbee_short_write(0x04, shortadr[1]);			// SADRH
	source_SHORTADR[0] = shortadr[0];				// Save to local variable
	source_SHORTADR[1] = shortadr[1];				// Save to local variable
}

// 8 byte long address, source
void zigbee_source_longadr(uint8 * longadr)
{
	uint8 i;
	for( i = 0; i < 8; i++)
	{
		zigbee_short_write(0x05 + i, longadr[i]);	// EADR0 - EADR7
		source_LONGADR[i] = longadr[i];				// Save to local variable
	}
}

// 2 byte PAN id, destination
void zigbee_destination_PANid(uint8 * PANid)
{
	destination_PANID[0] = PANid[0];				// Save to local variable
	destination_PANID[1] = PANid[1];				// Save to local variable
}

// 2 byte short address, destination
void zigbee_destination_shortadr(uint8 * shortadr)
{
	destination_SHORTADR[0] = shortadr[0];			// Save to local variable
	destination_SHORTADR[1] = shortadr[1];			// Save to local variable
}

// 8 byte long address, destination
void zigbee_destination_longadr(uint8 * longadr)
{
	uint8 i;
	for( i = 0; i < 8; i++)
	{
		destination_LONGADR[i] = longadr[i];		// Save to local variable
	}
}

//******************************************************************************
// RF Transmission recieve and send functions
//******************************************************************************

// Reset RX-fifo pointer
void zigbee_flush_RXfifo(void)
{
	uint8 temp;
	temp = zigbee_short_read(0x0D);			// RXFLUSH - save old value
	temp = temp | 0x01;						// update value
	zigbee_short_write(0x0D, temp);			// RXFLUSH - write new value
}

// Transmit data in TX-fifo
void zigbee_transmit_TXfifo(void)
{
	uint8 temp;
	temp = zigbee_short_read(0x1B);			// TXNCON - save old value
	temp = temp | 0x01;						// update value
	zigbee_short_write(0x1B, temp);			// TXNCON - write new value
}

// Read the raw data directly from the RX-fifo
uint8 zigbee_read_raw_RXfifo(uint8 * RXfifo_ptr)
{
	uint8 i;
	zigbee_short_write(0x39, 0x04);			// BBREG1 - disable receiving packets
	RXfifo_ptr[0] = zigbee_long_read(RXfifo_adr); // RX-fifo - get data packet frame length
	for( i = 0; i < (RXfifo_ptr[0] + 1 + RSSI_status); i++ ) // Runs through the rest of the array
	{
		RXfifo_ptr[i + 1] = zigbee_long_read(RXfifo_adr + i + 1); // RX-fifo - read rest + 2 bytes, LQI & RSSI
	}
	zigbee_short_write(0x39, 0x00);			// BBREG1 - enable receiving packets
	return RXfifo_ptr[0];
}

// Write the raw data directly to the TX-fifo, max 127 bytes
void zigbee_write_raw_TXfifo(const uint8 * TXfifo_ptr)
{
	uint8 i;
	for( i = 0; i < (TXfifo_ptr[1] + 2); i++ )	// Runs through the entire array
	{
		zigbee_long_write(TXfifo_adr + i,TXfifo_ptr[i]); // Write data to the TX-fifo
	}
}

// Read out the payload from the RX-fifo, and returns the length of payload
// The setup of this function matches the setup of zigbee_write_payload_TXfifo() below
uint8 zigbee_read_payload_RXfifo(uint8 * RXfifo_ptr)
{
	uint8 length, i;
	zigbee_short_write(0x39, 0x04);			// BBREG1 - disable receiving packets
	length = zigbee_long_read(RXfifo_adr); 	// RX-fifo - get data packet frame length
	length = length - 9;					// Only length of payload needed
	for( i = 0; i < length; i++ ) // Runs through the payload part of the RF-fifo
	{
		RXfifo_ptr[i] = zigbee_long_read(RXfifo_adr + 8 + i); // RX-fifo - reads only payload
	}
	zigbee_short_write(0x39, 0x00);			// BBREG1 - enable receiving packets
	return length;
}

// Write the payload, max 118 bytes, to TX-fifo, rest is appended automatically
// The setup of this function matches the setup of zigbee_read_payload_RXfifo() above
void zigbee_write_payload_TXfifo(const uint8 * TXfifo_ptr, uint8 length)
{
	uint8 i;
	// Write data to the TX-fifo
	zigbee_long_write(TXfifo_adr + 0, 0x07); 					// Header length
	zigbee_long_write(TXfifo_adr + 1, length + 0x07); 			// Frame length (header length + payload length)
	// Header:
	zigbee_long_write(TXfifo_adr + 2, 0x01); 					// Frame control field, bit 7 - 0
	zigbee_long_write(TXfifo_adr + 3, 0x08); 					// Frame control field, bit 15 - 8
	zigbee_long_write(TXfifo_adr + 4, sequence_number); 		// Sequence number, a counter
	zigbee_long_write(TXfifo_adr + 5, destination_PANID[0]); 	// Destination PAN id MSB
	zigbee_long_write(TXfifo_adr + 6, destination_PANID[1]); 	// Destination PAN id LSB
	zigbee_long_write(TXfifo_adr + 7, destination_SHORTADR[0]); // Destination short address MSB
	zigbee_long_write(TXfifo_adr + 8, destination_SHORTADR[1]); // Destination short address LSB
	// Frame payload, max 118 bytes with current setup
	for( i = 0; i < length ; i++ )								// Runs through the entire array of the payload
	{
		zigbee_long_write(TXfifo_adr + 9 + i,TXfifo_ptr[i]);	// Write payload to the TX-fifo
	}
	sequence_number++;
}

//******************************************************************************
// Status registers, interrupt & transmit MAC
//******************************************************************************

// Interrupt status
uint8 zigbee_status_IRQ(void)
{
	return zigbee_short_read(0x31);			// INTSTAT - read interrupt status register
}

// Transmit status
uint8 zigbee_status_TX(void)
{
	return zigbee_short_read(0x24);			// TXSTAT - read transmit status register
}

//******************************************************************************
// End of file
//******************************************************************************
