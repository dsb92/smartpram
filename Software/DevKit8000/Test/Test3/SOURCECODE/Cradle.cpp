#include "Cradle.hpp"

// Constructor initialisering - her sættes manuel, automatisk og cradle kontrol til false. 
Cradle::Cradle() : mq_(MAX_QUEUE_SIZE)
{
  cradleOn_ = false;
  manuelControl_ = false;
  automaticControl_ = false;
  running_ = true;
}

void Cradle::handleMsg(osapi::Message* msg, unsigned long id)
{
  switch (id)
  {
    case ID_START_CRADLE_MANUEL:
    {
      MsgSendSetting* msgSend = new MsgSendSetting;
      
      manuelControl_ = true;
      
      std::cout << std::endl;
      std::cout << "Cradle: Receiving 'start cradle manual' message from ManualController" << std::endl;
      std::cout << "Cradle: Sending 'start cradle' message to ZigBeeIF_out with cradle speed: " << (unsigned int)cradleSpeed_ << std::endl;

      std::cout << "Cradle: Starting timer: " << (unsigned int)cradleTime_ << std::endl;
      std::cout << std::endl << std::endl;;
      
      msgSend-> speed = cradleSpeed_;
      msgSend-> time = cradleTime_;
      
      // Send besked om at starte vugge.
      zigbeeOutMq_->send(ZigBeeIF_out::ID_CRADLE_START, msgSend);
      cradleOn_ = true;
      // Sæt timer svarende til urotid.
      timer_->arm(cradleTime_*1000);	
      
      break;
    }
    
    case ID_START_CRADLE_AUTOMATIC:
    {
      MsgSendSetting* msgSend = new MsgSendSetting;
      
      automaticControl_ = true;
      
      std::cout << "Cradle: Receiving 'start cradle automatic' message from AutomaticController" << std::endl;
      std::cout << "Cradle: Sending 'start cradle' message to ZigBeeIF_out with cradle speed: " << (unsigned int)cradleSpeed_ << std::endl;

      std::cout << "Cradle: Starting timer: " << (unsigned int)cradleTime_ << std::endl;
      
      msgSend-> speed = cradleSpeed_;
      msgSend-> time = cradleTime_;
      
      zigbeeOutMq_->send(ZigBeeIF_out::ID_CRADLE_START, msgSend);
      cradleOn_ = true;
      timer_->arm(cradleTime_*1000);
      
      break;
    }
    
    
    case ID_STOP_CRADLE:
    {
      // Hvis vugge er startet
      if ( cradleOn_ == true )
      {
	// Stop timer.
	timer_->disArm();
	cradleOn_ = false;
	
	MsgStandard* msgStd1 = new MsgStandard;
	
	std::cout << std::endl;
	std::cout << "Cradle: Sending 'stop cradle' message to ZigBeeIF_out" << std::endl;
	
	// Send besked til ZigBeeIF_out om at stoppe vugge.
	zigbeeOutMq_->send(ZigBeeIF_out::ID_CRADLE_STOP, msgStd1);
	
	// Hvis manuel kontrol er startet og automatisk kontrol ikke er startet.
	if ( manuelControl_ & !automaticControl_ )
	{	  
	  MsgStandard* msgStd2 = new MsgStandard;
	  
	  std::cout << "Cradle: Sending 'stopped cradle' message to ManualController" << std::endl << std::endl;
	  
	  // Send besked til ManualController om at vugge er stoppet.
	  manualMq_->send(ManualController::ID_CRADLE_STOPPED, msgStd2);
	}
	// Hvis automatisk kontrol er startet og hvis manuel kontrol ikke allerede kører.
	else if ( automaticControl_ & !manuelControl_)
	{ 
	  MsgStandard* msgStd2 = new MsgStandard;
	  
	  std::cout << "Cradle: Sending 'stopped cradle' message to AutomaticController" << std::endl << std::endl;
	  
	  // Send besked til AutomaticController om at vugge er stoppet.
	  automaticMq_->send(AutomaticController::ID_CRADLE_STOPPED, msgStd2);
	}
	
	automaticControl_ = false;
	manuelControl_ = false;
	
      }
      
      
      break;
    }
    
    case ID_UPDATE_SETTING:
    {
      MsgSendSetting* msgSet = static_cast<MsgSendSetting*>(msg);
      
      cradleTime_ = msgSet-> time;
      cradleSpeed_ = msgSet-> speed;
      
      break;
    }
    
    
  }
}

void Cradle::setMqs( osapi::MsgQueue* manualMq, osapi::MsgQueue* automaticMq, osapi::MsgQueue* zigbeeOutMq  )
{
  manualMq_ = manualMq;
  zigbeeOutMq_ = zigbeeOutMq;
  automaticMq_ = automaticMq;
}


void Cradle::run()
{
  timer_ = osapi::createNewTimer(&mq_, ID_STOP_CRADLE);	//create timer object
  
  while(running_)
  {
    unsigned long id;
    osapi::Message* msg = mq_.receive(id);
    handleMsg(msg,id);
    delete msg;
  }
  
  timer_->disArm();	//stop timer
  
}
