#ifndef COMMON_H_
#define COMMON_H_


/*************INKLUDERER FILER FRA OSAPI *************/
#include <osapi/MsgQueue.hpp>
#include <osapi/Message.hpp>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/Utility.hpp>
#include <osapi/Thread.hpp>
#include <osapi/Timer.hpp>
#include <osapi/Log.hpp>
#include <unistd.h>

/*************INKLUDERER IOSTREAM OG STRING TIL AT SKRIVE UD PÅ SKÆRMEN*************/
#include <iostream>
#include <string>

/*************INKLUDERER DEVKITTETS INTERFACES*************/
#include "UIController.hpp"
#include "ManualController.hpp"
#include "AutomaticController.hpp"
#include "Cradle.hpp"
#include "Mobile.hpp"
#include "ZigBeeIF_out.hpp"
#include "ZigBeeIF_in.hpp"
#include "Settings.hpp"
#include "SettingsController.hpp"
#include "MeasurementsController.hpp"

///*************INKLUDERER NØDVENDIGE H-FILER TIL ZIGBEE*************/
#include <stdlib.h>
#include <fcntl.h>

///*************DEFINERER DEFINES - GENVEJE TIL ZIGBEE DRIVER VIA ECHO*************/
#define RESET				"echo 1 > /sys/class/zigbee_module/zigbee/zigbee_reset"
#define INIT				"echo 1 > /sys/class/zigbee_module/zigbee/zigbee_init"
#define SET_CH				"echo 22 > /sys/class/zigbee_module/zigbee/zigbee_set_ch"
#define SET_TXPOWER			"echo 31 > /sys/class/zigbee_module/zigbee/zigbee_set_TXpower"
#define SOURCE_PANID			"echo 17 34 > /sys/class/zigbee_module/zigbee/zigbee_source_PANid"
#define SOURCE_SHORTADR			"echo 51 68 > /sys/class/zigbee_module/zigbee/zigbee_source_shortadr"
#define DESTINATION_PANID		"echo 187 204 > /sys/class/zigbee_module/zigbee/zigbee_destination_PANid"
#define DESTINATION_SHORTADR		"echo 221 238 > /sys/class/zigbee_module/zigbee/zigbee_destination_shortadr"
#define FLUSH				"echo 1 > /sys/class/zigbee_module/zigbee/zigbee_flush_RXfifo"
#define STAT_IRQ			"cat /sys/class/zigbee_module/zigbee/zigbee_status_IRQ"
#define DEV_PATH			"/dev/zigbee"	// Path of the device
#define MAXLENGTH			118		// Max length of payload from zigbeee module


///*************BESKED NEDARVNING FRA OSAPI MESSAGE*************/

// Opret en tom besked der bruges som standard, hvis ingen information skal sendes.
struct MsgStandard : public osapi::Message
{};

// Opret besked der bruges, når en indstilling ændres.
struct MsgSettings : public osapi::Message
{
  signed char minTemperature;
  signed char maxTemperature;
  signed char maxSound;
  
  unsigned int cradleTime;
  unsigned char cradleSpeed;
  unsigned int mobileTime;
  unsigned char mobileSpeed; 
};

// Opret en besked der bruges til at sende en tid og hastighed til ZigBeeIF_out
struct MsgSendSetting : public osapi::Message
{
  unsigned int time;
  unsigned char speed;
};

// Opret en besked som SettingsController blandt andre bruger til at sende til MeasurementsController om at læse nye indstillinger fra Settings.
struct MsgSendMeasurementsSetting : public osapi::Message
{
  signed char minTemperature;
  signed char maxTemperature;
  signed char maxSound;
};

// Opret en besked som ZigBeeIF_in sender til MeasurementsController med nye målinger.
struct MsgMeasurements : public osapi::Message
{
  signed char temperature;
  signed char sound;
};

// Opret en besked som MeasurementsController bruger til at analysere målingerne fra ZigBeeIF_in.
struct MsgAnalysedMeasurements : public osapi::Message
{
  signed char temperature;
  signed char sound;
  
  bool temperatureLow;
  bool temperatureHigh;
  bool soundHigh;
  
};


#endif
