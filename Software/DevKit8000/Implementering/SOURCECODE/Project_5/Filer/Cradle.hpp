/*************BESKRIVELSE AF KLASSE************/
/* Cradle klassen står den automatiske og manuelle styring af vugge. 
 */

#ifndef CRADLE_H_
#define CRADLE_H_

#include "common.hpp" 

class Cradle : public osapi::ThreadFunctor
{

public:
  Cradle();

  enum
  {
    ID_UPDATE_SETTING, 		// Besked som Cradle får, når indstillinger er blevet ændret.
    ID_START_CRADLE_MANUEL,	// Besked som Cradle får, når manuelt styring af vugge er blevet forspurgt.
    ID_START_CRADLE_AUTOMATIC,	// Besked som Cradle får, når automatisk styring af vugge er blevet forspurgt.
    ID_STOP_CRADLE,		// Besked som Cradle får, når den skal stoppe enten automatisk eller manuel Uro.
    ID_TIME_OUT			// Besked som Cradle får, når urotiden er udløbet.
  };

  osapi::MsgQueue* getMsgQueue() { return &mq_; }

  void setMqs( osapi::MsgQueue* manualMq, osapi::MsgQueue* automaticMq, osapi::MsgQueue* zigbeeOutMq  );
private:
  osapi::MsgQueue mq_;
  static const int MAX_QUEUE_SIZE = 10;
  void handleMsg(osapi::Message* msg, unsigned long id);
  bool running_;
  bool manuelControl_;
  bool automaticControl_;
  bool cradleOn_;
  unsigned int cradleTime_;
  unsigned char cradleSpeed_;
  void run();
 
  osapi::ITimerId*  timer_;
  osapi::MsgQueue* manualMq_;
  osapi::MsgQueue* zigbeeOutMq_;
  osapi::MsgQueue* automaticMq_;
};

#endif