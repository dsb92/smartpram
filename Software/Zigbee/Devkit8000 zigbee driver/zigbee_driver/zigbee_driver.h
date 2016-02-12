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

// File includes
#include "zigbee_SPI_Devkit8000.h"

// Constants
#define RXfifo_adr 0x300				// RX fifo, 0x300 - 0x38F, 144 bytes
#define TXfifo_adr 0x000				// TX normal data fifo, 0x000 - 0x07F, 128 bytes

// Zigbee configuration functions
void zigbee_reset(void);
void zigbee_set_ch(uint8 CH);
void zigbee_set_TXpower(uint8 power);
void zigbee_set_CCA(uint8 CCA_mode, uint8 CS, uint8 ED);
void zigbee_set_RSSI(uint8 RSSI_mode);
void zigbee_set_nonbeacon_mode(uint8 beacon_mode);
void zigbee_set_reception_mode(uint8 reception_mode);
void zigbee_init(void);

// Set the zigbee's source and destination PAN id, short and long addresses
void zigbee_source_PANid(uint8 * PANid);
void zigbee_source_shortadr(uint8 * shortadr);
void zigbee_source_longadr(uint8 * longadr);
void zigbee_destination_PANid(uint8 * PANid);
void zigbee_destination_shortadr(uint8 * shortadr);
void zigbee_destination_longadr(uint8 * longadr);

// RF Transmission recieve and send functions
void zigbee_flush_RXfifo(void);
void zigbee_transmit_TXfifo(void);
uint8 zigbee_read_raw_RXfifo(uint8 * RXfifo_ptr);
void zigbee_write_raw_TXfifo(const uint8 * TXfifo_ptr);
uint8 zigbee_read_payload_RXfifo(uint8 * RXfifo_ptr);
void zigbee_write_payload_TXfifo(const uint8 * TXfifo_ptr, uint8 length);

// Status registers, interrupt & transmit MAC
uint8 zigbee_status_IRQ(void);
uint8 zigbee_status_TX(void);

//******************************************************************************
// End of file
//******************************************************************************
