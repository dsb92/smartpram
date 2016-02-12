#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <fcntl.h>
#include <string.h>

using namespace std;

/*
 * pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
 * pthread_mutex_lock( &count_mutex );
 * pthread_mutex_unlock( &count_mutex );
 * 
 * pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;
 * pthread_cond_wait( &condition_var, &count_mutex );
 * pthread_cond_signal( &condition_var );
 * 
 * pthread_t thread1;
 * pthread_create( &thread1, NULL, &functionCount1, NULL);
 * pthread_join( thread1, NULL);
 * 
 * void *functionCount1(void *)
 * {
 *   // do stuff
 *   return 0;
 * }
 */


// Constants
const char* RESET =			"echo 1 > /sys/class/zigbee_module/zigbee/zigbee_reset";
const char* SET_CH =			"echo 22 > /sys/class/zigbee_module/zigbee/zigbee_set_ch";
const char* SET_TXPOWER =		"echo 5 > /sys/class/zigbee_module/zigbee/zigbee_set_TXpower";
const char* SET_CCA =			"echo 1 14 96 > /sys/class/zigbee_module/zigbee/zigbee_set_CCA";
const char* SET_RSSI =			"echo 1 > /sys/class/zigbee_module/zigbee/zigbee_set_RSSI";
const char* SET_NONBEACON_MODE =	"echo 0 > /sys/class/zigbee_module/zigbee/zigbee_set_nonbeacon_mode";
const char* SET_RECEPTION_MODE =	"echo 2 > /sys/class/zigbee_module/zigbee/zigbee_set_reception_mode";
const char* INIT =			"echo 1 > /sys/class/zigbee_module/zigbee/zigbee_init";
const char* FLUSH =			"echo 1 > /sys/class/zigbee_module/zigbee/zigbee_flush_RXfifo";

const char* SOURCE_PANID =		"echo 17 34 > /sys/class/zigbee_module/zigbee/zigbee_source_PANid";
const char* SOURCE_SHORTADR =		"echo 51 68 > /sys/class/zigbee_module/zigbee/zigbee_source_shortadr";
const char* SOURCE_LONGADR =		"echo 1 2 3 4 5 6 7 8 > /sys/class/zigbee_module/zigbee/zigbee_source_longadr";
const char* DESTINATION_PANID =		"echo 102 119 > /sys/class/zigbee_module/zigbee/zigbee_destination_PANid";
const char* DESTINATION_SHORTADR =	"echo 136 153 > /sys/class/zigbee_module/zigbee/zigbee_destination_shortadr";
const char* DESTINATION_LONGADR =	"echo 1 2 3 4 5 6 7 8 > /sys/class/zigbee_module/zigbee/zigbee_destination_longadr";

const char* STAT_IRQ =			"cat /sys/class/zigbee_module/zigbee/zigbee_status_IRQ";
const char* STAT_TX =			"cat /sys/class/zigbee_module/zigbee/zigbee_status_TX";

const char* DEV_PATH = 			"/dev/zigbee";	// 
const int bufferlength = 		128;


// Global variables
int run = 				0;

// Prototype of funktions
void *zigbee_read(void *);
void *zigbee_write(void *);


// Main applikation
int main(void)
{
    char* tempstr;
    pthread_t thread1, thread2;
    
    cout << "Zigbee test program\n";
    
    system( RESET );
    system( INIT );
    system( SET_CH );
    system( SET_TXPOWER );
    system( SOURCE_PANID );
    system( SOURCE_SHORTADR );
    system( DESTINATION_PANID );
    system( DESTINATION_SHORTADR );
//    system( SET_RECEPTION_MODE );
    system( FLUSH );
    system( STAT_IRQ );
    
    run = 1;
    
    // Start threads
    pthread_create( &thread1, NULL, &zigbee_read, NULL);
    pthread_create( &thread2, NULL, &zigbee_write, NULL);
    
    // Rejoin threads
    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
    
    return 0;
}

// Threads

void *zigbee_read(void *)
{
    int fd = open( DEV_PATH, O_RDONLY );
    char buffer [bufferlength];
    do {
	read( fd, &buffer, bufferlength );
	cout << "Data recieved in buffer: ";
	cout << buffer << endl;
    }
    while( run != 0 );
    close( fd );
    return 0;
}

void *zigbee_write(void *)
{
    int fd = open( DEV_PATH, O_WRONLY );
    char buffer [bufferlength];
    int length;
    do {
	cin >> buffer;
	length = strlen(buffer);
	buffer[length] = '\0';		// add zero termination
	length++;
	cout << "Buffer contains:" << buffer << ", sizeof:" << length << ", transmitting data.\n";
	write( fd, &buffer, length );
    }
    while( strcmp (buffer, "q") != 0 );
    close( fd );
    run = 0;
    return 0;
}

// End of file