#include "Mobile.hpp"

// Initialiser Constructor med bool variabler sat til false.
Mobile::Mobile() : mq_(MAX_QUEUE_SIZE)
{
  mobileOn_ = false;
  automaticControl_ = false;
  manuelControl_ = false;
  running_ = true;
}

void Mobile::handleMsg(osapi::Message* msg, unsigned long id)
{

  switch (id)
  {
    case ID_START_MOBILE_MANUEL:
    {
      MsgSendSetting* msgSend = new MsgSendSetting;
      
      manuelControl_ = true;
      
      // Udskriv til terminalen med hvilken urohastighed og urotid, som klassen sender til ZigBeeIF_out.
      std::cout << "Mobile: Receiving 'start mobile' message from ManualController" << std::endl;
      std::cout << "Mobile: Sending 'start mobile' message to ZigBeeIF_out with mobile speed: " << (unsigned int)mobileSpeed_ << std::endl;

      std::cout << "Mobile: Starting timer: " << (unsigned int)mobileTime_ << std::endl;
      
      // Læs Mobile's private urohastighed og tid og assign til besked.
      msgSend-> speed = mobileSpeed_;
      msgSend-> time = mobileTime_;
      
      // Send besked til ZigBeeIF_out om at starte uro manuelt.
      zigbeeOutMq_->send(ZigBeeIF_out::ID_MOBILE_START, msgSend);
      // Indiker at Uro nu kører.
      mobileOn_ = true;
      // Start timer med 1 sekunds præcision og svarende til urotiden.
      timer_->arm(mobileTime_*1000);

      break;
    }
    
    case ID_START_MOBILE_AUTOMATIC:
    {
      MsgSendSetting* msgSend = new MsgSendSetting;
      
      automaticControl_ = true;
      
      std::cout << "Mobile: Receiving 'start mobile automatic' message from AutomaticController" << std::endl;
      std::cout << "Mobile: Sending 'start mobile' message to ZigBeeIF_out with mobile speed: " << mobileSpeed_ << std::endl;

      std::cout << "Mobile: Starting timer: " << (unsigned int)mobileTime_ << std::endl;
      
      msgSend-> speed = mobileSpeed_;
      msgSend-> time = mobileTime_;
      
      zigbeeOutMq_->send(ZigBeeIF_out::ID_MOBILE_START, msgSend);
      mobileOn_ = true;
      timer_->arm(mobileTime_*1000);
      
      break;
    }
    
    
    case ID_STOP_MOBILE:
    {
      // Deaktiverer timer.
      timer_->disArm();
      mobileOn_ = false;
      
      MsgStandard* msgStopMobile = new MsgStandard;
      
      std::cout << std::endl << std::endl;
      std::cout << "Mobile: Sending 'stop mobile' message to ZigBeeIF_out" << std::endl;
      
      // Send besked til ZigBeeIF_out om at stoppe Uro.
      zigbeeOutMq_->send(ZigBeeIF_out::ID_MOBILE_STOP, msgStopMobile);
    
      // Hvis manuel styring kører og automatisk ikke kører.
      if ( manuelControl_ & !automaticControl_ )
      {
	MsgStandard* msgMobileManStopped = new MsgStandard;
	
	std::cout << "Mobile: Receiving 'stop mobile' message from ManualController" << std::endl << std::endl;
	
	// Send stopbesked til ManualController om, at uro er stoppet.
	manualMq_->send(ManualController::ID_MOBILE_STOPPED, msgMobileManStopped);
      }
      
      // Hvis manuel styring ikke kører og automatisk kører.
      if ( automaticControl_ &!manuelControl_ )
      {	
	MsgStandard* msgMobileAutoStopped = new MsgStandard;
	
	std::cout << "Mobile: Receiving 'stop mobile' message from AutomaticController" << std::endl << std::endl;
	
	// Send stopbesked til AutomaticController om, at uro er stoppet.
	automaticMq_->send(AutomaticController::ID_MOBILE_STOPPED, msgMobileAutoStopped);
      }
      
      automaticControl_ = false;
      manuelControl_ = false;
      
      break;
    }
     
    case ID_UPDATE_SETTING:
    {
      // Opret ny beskedpointer som sættes lig med den besked, den netop har modtaget fra SettingsController.
      MsgSendSetting* msgSet = static_cast<MsgSendSetting*>(msg);
      
      // Læs beskedens tid og hastighed og sæt lige med Mobile's.
      mobileTime_ = msgSet-> time;
      mobileSpeed_ = msgSet-> speed;
      
      break;
    }
  }
}

void Mobile::setMqs( osapi::MsgQueue* manualMq, osapi::MsgQueue* automaticMq, osapi::MsgQueue* zigbeeOutMq  )
{
  manualMq_ = manualMq;
  zigbeeOutMq_ = zigbeeOutMq;
  automaticMq_ = automaticMq;
}

void Mobile::run()
{
  
  // Opret timer objekt.
  timer_ = osapi::createNewTimer(&mq_, ID_STOP_MOBILE);
  
  while(running_)
  {
    unsigned long id;
    osapi::Message* msg = mq_.receive(id);
    handleMsg(msg,id);
    delete msg;
  }
  
  timer_->disArm();
}
