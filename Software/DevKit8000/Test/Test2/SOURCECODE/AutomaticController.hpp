/*************BESKRIVELSE AF KLASSE************/
/* AutomaticController er en kontrolklasse, der står for den automatiske styring af Vugge og Uro.
 * Denne klasse skal forespørge om lydstatus og afhængig af hvad lydniveauet er, skal den starte Vugge og Uro, som kravspecifikationen beskriver det.
 */

#ifndef AUTOMATIC_CONTROLLER_H_
#define AUTOMATIC_CONTROLLER_H_

#include "common.hpp"

class AutomaticController : public osapi::ThreadFunctor
{
public:
  AutomaticController();
  
  enum
  {
    ID_CHECK_SOUND,		// Besked som AutomaticController får, når den skal forespørge om at tjekke lyd fra MeasurementsController.
    ID_START_CRADLE,		// Besked som AutomaticController får, når den skal forespørge om at starte vugge.
    ID_CHECK_SOUND_AGAIN,	// Besked som AutomaticController får, når den skal forespørge om at tjekke lyd igen fra MeasurementsController.
    ID_START_MOBILE,		// Besked som AutomaticController får, når den skal forespørge om at starte uro.
    ID_STOP_AUTOMATIC,		// Besked som AutomaticController får, når den skal stoppe automatisk styring.
    ID_CRADLE_STOPPED,		// Besked som AutomaticController får, når vugge er blevet stoppet.
    ID_MOBILE_STOPPED		// Besked som AutomaticController får, når uro er blevet stoppet.
  };

  osapi::MsgQueue* getMsgQueue() { return &mq_; }

  void setMqs( osapi::MsgQueue* cradleMq, osapi::MsgQueue* mobileMq, osapi::MsgQueue* UIMq, osapi::MsgQueue* meaCtrlMq  );
private:
  osapi::MsgQueue mq_;
  static const int MAX_QUEUE_SIZE = 10;
  void handleMsg(osapi::Message* msg, unsigned long id);
  bool running_;
  // Bool til at tjekke om at automatisk styring er stoppet eller stadig kører.
  bool stopAutomatic_;
  void run();

  osapi::MsgQueue* cradleMq_;
  osapi::MsgQueue* mobileMq_;
  osapi::MsgQueue* meaCtrlMq_;
  osapi::MsgQueue* UIMq_;
};

#endif