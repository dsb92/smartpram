/* ========================================
 * PRJ3 - Gruppe 8
 * Authors: 
 *          - Jonas Ulleberg Jussila
 *          - Mads Gad Krogsgaard
 * ========================================
*/

/*******************************************************************************
* Includes and Defines
*******************************************************************************/
#include <device.h>
#include <math.h>
#include <stdio.h>
#include "zigbee_driver.h"
#include "Functions.h"
#define n 1
#define N_Sample 9
#define SOUND_SIZE 20
#define ZIG_ARR_SEND_SIZE 2
#define ZIG_ARR_RECEIVE_SIZE 2

/*******************************************************************************
* Global Variables
*******************************************************************************/

enum Inputs
{
	TEMPERATURE = 0,
	SOUND = 1
};

int16 	V_Sample[n];
int16 	V_Sample_MIN=0;
int16 	V_Sample_MAX=0;
float 	V_Sample_PP_float=0;
uint16 	i=0;

uint8 phase = 1;	// Contains the current phase of which the program is in
uint8 shutDownCounter = 0; 	// "Shuts down" Psoc if this reaches some value
uint8 cradleSpeed = 0;	// Container for speed to be sent to cradle motor
uint8 mobileSpeed = 0;	// Container for speed to be sent to mobile motor
float soundArray[ SOUND_SIZE ];	// Container for peak-to-peak samples to be analyzed
uint8 soundCounter = 0;		// Counter for work on the soundArray

int8 zigSendArr[ ZIG_ARR_SEND_SIZE ];	// Array to be sent to ZigBee
int8 soundResult; // Result of sound analysis, ready for sending to zigSendArr.
int8 tempResult = 66;	// Value from ADC is converted into a value in degrees celcius
int16 tempIn = 0;		// Temperature value read from ADC

//Zigbee settings
//Destination
uint8 PANID_A[2] = {0x11, 0x22}; //desination ID (DEVKIT I STEDER FOR A)
uint8 SHORTADR_A[2] = {0x33, 0x44};
//Source (itself)
uint8 PANID_B[2] = {0xBB, 0xCC}; //Zigbee ID (PSOC I STEDER FOR B)
uint8 SHORTADR_B[2] = {0xDD, 0xEE};

/*******************************************************************************
* Functions for DMA configuration
*******************************************************************************/

void DMA_1_Config()
{
	// Variable declarations for DMA_1 
	// Move these variable declarations to the top of the function 
	uint8 DMA_1_Chan;
	uint8 DMA_1_TD[1];

	// DMA Configuration for DMA_1
	#define DMA_1_BYTES_PER_BURST 2
	#define DMA_1_REQUEST_PER_BURST 1
	#define DMA_1_SRC_BASE (CYDEV_PERIPH_BASE)
	#define DMA_1_DST_BASE (CYDEV_PERIPH_BASE)
	DMA_1_Chan = DMA_1_DmaInitialize(DMA_1_BYTES_PER_BURST, DMA_1_REQUEST_PER_BURST, HI16(DMA_1_SRC_BASE), HI16(DMA_1_DST_BASE));
	DMA_1_TD[0] = CyDmaTdAllocate();
	CyDmaTdSetConfiguration(DMA_1_TD[0], 2, DMA_INVALID_TD, TD_INC_DST_ADR);
	CyDmaTdSetAddress(DMA_1_TD[0], LO16((uint32)ADC_DelSig_1_DEC_SAMP_PTR), LO16((uint32)Filter_1_STAGEAM_PTR));
	CyDmaChSetInitialTd(DMA_1_Chan, DMA_1_TD[0]);
	CyDmaChEnable(DMA_1_Chan, 1);
}

void DMA_2_Config()
{
	// Variable declarations for DMA_2
	// Move these variable declarations to the top of the function
	uint8 DMA_2_Chan;
	uint8 DMA_2_TD[1];

	// DMA Configuration for DMA_2
	#define DMA_2_BYTES_PER_BURST 2
	#define DMA_2_REQUEST_PER_BURST 1
	#define DMA_2_SRC_BASE (CYDEV_PERIPH_BASE)
	#define DMA_2_DST_BASE (CYDEV_SRAM_BASE)
	DMA_2_Chan = DMA_2_DmaInitialize(DMA_2_BYTES_PER_BURST, DMA_2_REQUEST_PER_BURST, HI16(DMA_2_SRC_BASE), HI16(DMA_2_DST_BASE));
	DMA_2_TD[0] = CyDmaTdAllocate();
	CyDmaTdSetConfiguration(DMA_2_TD[0], n*2, DMA_INVALID_TD, TD_SWAP_EN | DMA_2__TD_TERMOUT_EN | TD_INC_SRC_ADR | TD_INC_DST_ADR);
	CyDmaTdSetAddress(DMA_2_TD[0], LO16((uint32)Filter_1_HOLDAM_PTR), LO16((uint32)V_Sample));
	CyDmaChSetInitialTd(DMA_2_Chan, DMA_2_TD[0]);
	CyDmaChEnable(DMA_2_Chan, 1);
}

/*******************************************************************************
* Interrupt Service Routines
*******************************************************************************/

CY_ISR( DAC_int )
{
	VDAC8_1_Data = ((int8)(V_Sample[0] >> 8))+128; //128 = 0x80
}

CY_ISR( Sample_int )
{
	Control_Reg_1_Control=0;
	if(V_Sample[0]<V_Sample_MIN)V_Sample_MIN=V_Sample[0];
	if(V_Sample[0]>V_Sample_MAX)V_Sample_MAX=V_Sample[0];
}

CY_ISR( ISR_zigbee ){
	uint8 stat_IRQ;	// Container for the status of the IRQ
	uint8 dataReceived[ ZIG_ARR_RECEIVE_SIZE ];	// Container to store the received data
	uint8 lenghtOfData;	// Holds the lenght (in bytes) of the data received.
	
	stat_IRQ = zigbee_status_IRQ();	// Interrupt status
	
	if( (stat_IRQ & 0x08) > 0  ){ // If data received
		lenghtOfData = zigbee_read_payload_RXfifo( dataReceived );	
		
		mobileSpeed = dataReceived[0];	// Extract the PWM values from the received
		cradleSpeed = dataReceived[1];	// data and save in local variables
		PWM_1_WriteCompare1( cradleSpeed );	// Set new PWM value for cradle motor
		PWM_1_WriteCompare2( mobileSpeed );	// Set new PWM value for mobile motor
		
		shutDownCounter = 0;	// Reset counter for hibernation
	}
    IRQ_Zigbee_ClearInterrupt();	// Clears pins IRQ
}

/*******************************************************************************
* Function for starting ZigBee
*******************************************************************************/

void zigbee_start() //Zigbee init
{
	zigbee_reset();
	zigbee_init();
	zigbee_set_ch(22); // channels range from 11-26
 	zigbee_set_TXpower(31); //max 31
 	zigbee_source_PANid(PANID_B);
 	zigbee_source_shortadr(SHORTADR_B);
 	zigbee_destination_PANid(PANID_A);
 	zigbee_destination_shortadr(SHORTADR_A);
}


/*******************************************************************************
* Function for initialization
*******************************************************************************/

void Init()
{  
	// Component startups
	PWM_1_Start();
	AMux_1_Init();
	Opamp_1_Start();
	PGA_1_Start();
	ADC_DelSig_1_Start();
	ADC_DelSig_1_StartConvert();
	VDAC8_1_Start();
	SPI_Start();
	DMA_1_Config();
	DMA_2_Config();
	Filter_1_Start();
	Filter_1_SetCoherency(Filter_1_CHANNEL_A, Filter_1_KEY_HIGH);
	Control_Reg_1_Control=0;
	zigbee_start(); // Zigbee init
	
	// ISRs
	isr_Receive_Data_StartEx(ISR_zigbee);
	isr_1_StartEx(DAC_int);
	isr_2_StartEx(Sample_int);
	
	// Enable Global Interrupts
	CyGlobalIntEnable;
}


/*******************************************************************************
* Main Function
*******************************************************************************/

void main()
{
	Init();
	
	// Set default MUX input to microphone
	AMux_1_FastSelect( SOUND );
	
	// Initialize motors to 0 speed
	cradleSpeed = 0;
	mobileSpeed = 0;
	PWM_1_WriteCompare1( cradleSpeed );
	PWM_1_WriteCompare2( mobileSpeed );
	
    for(;;)
    {
		/***************************************************************************
		* PHASE 1:
		* Gathers peak-to-peak values from microphone for 5 seconds.
		* Represented by 20 measurements per second, so 100 total for the 5 seconds.
		* When 5 seconds are recorded in soundArray, move to phase 2.
		***************************************************************************/
		while( phase == 1 )
		{
			V_Sample_MIN= ((1<<15)-1) ; // int: ((1<<15)-1) uint: 0-1 
			V_Sample_MAX=1 << 15;       // int: 1<<15       uint: 0
			for(i=0;i<(1 << (N_Sample));i++)
			{
				Control_Reg_1_Control=1;
				while(Control_Reg_1_Control); 
			}
		
			// Calculate peak-to-peak value
			V_Sample_PP_float = ADC_DelSig_1_CountsTo_Volts((((int32)V_Sample_MAX)-((int32)V_Sample_MIN)));
			
			// Save value in array and increment counter
		 	soundArray[soundCounter] = V_Sample_PP_float;
			soundCounter++;
			
			// When array is full, move on to phase 2
			if( soundCounter >= SOUND_SIZE )
			{
				phase = 2;
				soundCounter = 0;	// Reset soundCounter for next 1 sec measurement
			}
		}

		/**********************************************************************
		* PHASE 2:
		* 
		* - Changes the MUX to the temperature channel, 
		* - Reads and saves data from ADC,
		* - Changes MUX back to the mic channel
		**********************************************************************/
		while( phase == 2 )
		{	
			AMux_1_FastSelect( TEMPERATURE );	// Change MUX channel to temperature
			
			// Delay, to make time for some measurement to be taken
			// before reading the value from the ADC
			CyDelay(5);
			
			// Read temperature and save in temperatureResult
			tempIn = ADC_DelSig_1_GetResult16();
			tempResult = analyzeTemp( tempIn ); // Convert to degrees celcius
					
			AMux_1_FastSelect( SOUND );	// Change MUX channel back to microphone	
			phase = 3;	// Move on to phase 3
		}

		/*********************************************************
		* PHASE 3:
		* - Analyze soundArray
		* - Send saved soundResult and temperatureResult to DevKit
		* - Go back to phase 1
		*********************************************************/
		while( phase == 3 )
		{			
			/**************************************
			* Analyze soundArray and (print result)
			**************************************/
			soundResult = analyzeSound( soundArray, SOUND_SIZE );

			
			/************************************************
			* Send values to DevKit through the ZigBee module
			************************************************/
			zigSendArr[ TEMPERATURE ] = tempResult;
			zigSendArr[ SOUND ] = soundResult;
			
			zigbee_write_payload_TXfifo( zigSendArr, ZIG_ARR_SEND_SIZE );
			zigbee_transmit_TXfifo();
			 
			shutDownCounter++;  // Add 1 sec (approximately) to counter
			phase = 1;	// Go back to phase one (will go to phase 4 instead, if shutDownCounter is too high)
		}
		
		/*******************************************************
		* PHASE 4:
		* - Turn off both motors
		* - Wait here until new signal is received from DevKit 
		*   (this is when shutDownCounter is reset in ZigBee ISR)
		********************************************************/
		
		// Phase 4 is determined by: 
		// - phase == 1 (meaning the previous round in the for(;;) is complete)
		// - combined with shutDownCounter getting too high (meaning we did not receive a signal
		//   from the DevKit for some ammount of time.)
		while( (phase == 1) && (shutDownCounter >= 10) )
		{
			// SHUT DOWN SYSTEMS
			cradleSpeed = 0;
			mobileSpeed = 0;
			PWM_1_WriteCompare1( cradleSpeed );
			PWM_1_WriteCompare2( mobileSpeed );
			
			// Maybe put PSOC in hibernation mode
			
			// Wait..
		} // End while

	} // End for(;;)
	
} // End main()


/* [] END OF FILE */
