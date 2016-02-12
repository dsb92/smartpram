/*************BESKRIVELSE AF KLASSE************/
/* ZigBeeIF_out er en boundry klasse, som hvert 2. sekund sender start og stoppe kommandoer til vugge og uro aktuatorerne på den anden side, dvs. til PSOC's ZigBee.
 * ZigBeeIF_out modtager desuden besked fra Cradle og Mobile, der hele tiden har opdateret vugge/urotider og hastigheder.
 */

#ifndef ZIGBEE_IF_OUT_H_
#define ZIGBEE_IF_OUT_H_

#include "common.hpp"


class ZigBeeIF_out : public osapi::ThreadFunctor
{

public:
  ZigBeeIF_out();

  enum
  {
    ID_CRADLE_START,	// Besked som ZigBeeIF_out får, når den skal sende en start vugge kommando.
    ID_CRADLE_STOP,	// Besked som ZigBeeIF_out får, når den skal sende en stop vugge kommando.
    ID_MOBILE_START,	// Besked som ZigBeeIF_out får, når den skal sende en start uro kommando.
    ID_MOBILE_STOP,	// Besked som ZigBeeIF_out får, når den skal sende en stop uro kommando.
    ID_TIME_OUT		// Besked som ZigBeeIF_out får, når udløbstiden for sendetiden udløber.
  };
  
  // Sætter vuggehastighed med den besked vuggehastighed, som den modtager som argument.
  void setCradleSpeed( unsigned char cradleSpeed );
  // Sætter urohastighed med den besked urohastighed, som den modtager som argument.
  void setMobileSpeed( unsigned char mobileSpeed );
  // Sætter data'erne videre.
  void sendData();
  // Starter sendingen med en timer initialiation - som desuden vil køre så længe sendingen er i gang eller at stopSend() funktionen bliver kaldt.
  void startSend();
  // Stopper sendingen og timeren med det samme.
  void stopSend();

  osapi::MsgQueue* getMsgQueue() { return &mq_; }

private:
  osapi::MsgQueue mq_;
  
  static const int MAX_QUEUE_SIZE = 10;
  // Den mængde der sendes er på 2 bytes. 1 byte til cradleSpeed og 1 byte til mobileSpeed
  // Bruger har dog ikke mulighed for at indstille hastighed, dvs. vi sender enten en hastighed på 0 steps eller på 255 steps.
  // Men i et fremtidigt arbejde kan dette nemt ændres nu, hvor vi får sendt dette.
  static const int BUFFERSIZE_OUT = 2;
  // Bruges som et pladsindeks til et bufferout array. Plads 0 er cradle og plads 1 er mobile.
  static const int CRADLE_OUT_POSITION = 0;
  static const int MOBILE_OUT_POSITION = 1;
  
  void handleMsg(osapi::Message* msg, unsigned long id);
  bool running_;
  void run();
  
  // Bool til at indikere status på sendingen.
  bool sendOn_;
  
  // Sendefrekvensen, dvs. der sendes hvert. 2. sekund.
  static const unsigned long SENDFREQ_SEC = 2;
  // Opret timerpointer til et timer objekt fra OSAPi'et.
  osapi::ITimerId*  timer_;

  // Selve buffer arrayet som skal sendes med en størrelse på 2 bytes.
  unsigned char bufferOut_[BUFFERSIZE_OUT];

};

#endif