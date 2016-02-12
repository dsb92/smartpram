/*************BESKRIVELSE AF KLASSE************/
/* Mobile klassen står den automatiske og manuelle styring af uro. 
 */

#ifndef MOBILE_H_
#define MOBILE_H_

#include "common.hpp" 

class Mobile : public osapi::ThreadFunctor
{

public:
  Mobile();

  enum
  {
    ID_START_MOBILE_AUTOMATIC,   // Besked som Mobile får, når den automatisk skal styre Uro.
    ID_START_MOBILE_MANUEL,      // Besked som Mobile får, når den manuelt skal styre Uro.
    ID_STOP_MOBILE,		 // Besked som Mobile får, når den skal stoppe enten automatisk eller manuel Uro.
    ID_UPDATE_SETTING,	         // Besked som Mobile får, når indstillinger er blevet ændret.
    ID_TIME_OUT		         // Besked som Mobile får, når vuggetiden er udløbet.
   };

  osapi::MsgQueue* getMsgQueue() { return &mq_; }

  void setMqs( osapi::MsgQueue* manualMq, osapi::MsgQueue* automaticMq, osapi::MsgQueue* zigbeeOutMq  );
private:
  osapi::MsgQueue mq_;
  static const int MAX_QUEUE_SIZE = 10;
  void handleMsg(osapi::Message* msg, unsigned long id);
  bool running_;
  bool mobileOn_;
  bool manuelControl_;
  bool automaticControl_;
  unsigned int mobileTime_;
  unsigned char mobileSpeed_;
  void run();
  
  // Timer pointer til klassen ITimerId klassen, som befinder sig i OSAPi'et.
  osapi::ITimerId*  timer_;
  osapi::MsgQueue* manualMq_;
  osapi::MsgQueue* zigbeeOutMq_;
  osapi::MsgQueue* automaticMq_;
};

#endif