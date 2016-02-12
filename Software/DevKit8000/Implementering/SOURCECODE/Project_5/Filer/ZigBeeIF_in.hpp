/*************BESKRIVELSE AF KLASSE************/
/* ZigBeeIF_in er en boundry klasse, som hvert sekund modtager målinger fra PSOC's ZigBee.
 * ZigBeeIF_in sender besked til MeasurementsController til behandling af målingerne.
 */

#ifndef ZIGBEE_IF_IN_H_
#define ZIGBEE_IF_IN_H_

#include "common.hpp"


class ZigBeeIF_in : public osapi::ThreadFunctor
{

public:
  ZigBeeIF_in();

  // Modtager data'er fra PSOC ZigBee.
  void receiveData();
  // Modtager temperatur.
  signed char getTemperature();
  // Modtager lyd.
  signed char getSound();
  // Debug funktion.
  void setTest(signed char sound, signed char temperature);
  // Henter datapakke fra ZigBee.
  void getDatapackage();
  
  void setMqs( osapi::MsgQueue* measurementsMq );

private:
  bool running_;
  void run();
  
  // Mængden af bytes der modtages. 1 byte af temperator og 1 byte af lyd.
  static const int BUFFERSIZE_IN = 2;
  // Temperatur bufferindeks. Temperatur ligger altså på plads 0 i bufferIn_ arrayet.
  static const int TEMPERATURE_IN_POSITION = 0;
  // Lyd bufferindeks. Lyd ligger altså på plads 1 i bufferIn_ arrayet.
  static const int SOUND_IN_POSITION = 1;
  
  osapi::MsgQueue* measurementsMq_;
  
  // Bufferarray som modtages fra ZigBee.
  signed char bufferIn_[BUFFERSIZE_IN];
    
};

#endif