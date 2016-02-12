#include "AutomaticController.hpp"

AutomaticController::AutomaticController() : mq_(MAX_QUEUE_SIZE)
{
  running_ = true;
  stopAutomatic_ = false;
}

void AutomaticController::handleMsg(osapi::Message* msg, unsigned long id)
{
  switch(id)
  {
    case ID_CHECK_SOUND:
    {
      std::cout << std::endl;
      std::cout << "AutomaticController: Receiving 'start automatic cradle' message from UIController" << std::endl;
      
      MsgStandard* msgCheckSound = new MsgStandard;
      
      std::cout << "AutomaticController: Sending 'check sound' message to MeasurementsController" << std::endl << std::endl;
      
      // Send besked til MeasurementsController om at tjekke status på lyd.
      meaCtrlMq_->send(MeasurementsController::ID_CHECK_SOUND, msgCheckSound);
      
      break;
    }
    
    case ID_START_CRADLE:
    {
      std::cout << std::endl;
      std::cout << "AutomaticController: Receving 'sound is to high message from MeasurementsController" << std::endl;
      std::cout << "AutomaticController: Sending 'start cradle automatic' message to Cradle" << std::endl << std::endl;
	    
      MsgStandard* msgStartAutoCradle = new MsgStandard;
      
      // Send besked til Cradle om at starte automatisk vugge.
      cradleMq_->send(Cradle::ID_START_CRADLE_AUTOMATIC, msgStartAutoCradle);

      break;
    }
    
    case ID_START_MOBILE:
    {
      std::cout << std::endl;
      std::cout << "AutomaticController: Receiving 'sound is too high' message from AutomaticController" << std::endl;

      MsgStandard* msgStartAutoMobile = new MsgStandard;
      std::cout << "AutomaticController: Sending 'start mobile automatic' message to Mobile" << std::endl << std::endl;
      
      // Send besked til Mobile om at starte automatisk uro.
      mobileMq_->send(Mobile::ID_START_MOBILE_AUTOMATIC, msgStartAutoMobile);
  
      break;
    }
    
    case ID_STOP_AUTOMATIC:
    {
      
      std::cout << std::endl;
      std::cout << "AutomaticController: Sending 'stop automatic' message to Cradle and Mobile" << std::endl << std::endl;
      
      stopAutomatic_ = true;
      
      // Her sendes en stop cradle, stop mobile og stopped automatic besked. Der oprettes en ny besked for hver gang, da beskederne bliver slettet efter at de er blevet sendt.
      MsgStandard* msgStopCradle = new MsgStandard;
      
      cradleMq_->send(Cradle::ID_STOP_CRADLE, msgStopCradle);
      
      MsgStandard* msgStopMobile = new MsgStandard;
      
      mobileMq_->send(Mobile::ID_STOP_MOBILE, msgStopMobile);
      
      MsgStandard* msgAutoStopped = new MsgStandard;
      
      mobileMq_->send(MeasurementsController::ID_AUTOMATIC_STOPPED, msgAutoStopped);

      break;
    }
    
    case ID_CRADLE_STOPPED:
    {
      std::cout << std::endl;
      std::cout << "AutomaticController: Receiving 'stopped cradle' message from Cradle" << std::endl;
      std::cout << "AutomaticController: Sending 'stopped cradle' message to UIController" << std::endl << std::endl;
      
      MsgStandard* msgCradleStopped = new MsgStandard;
      
      // Send besked til UIController om, at vugge er stoppet.
      UIMq_->send(UIController::ID_CRADLE_STOPPED, msgCradleStopped);
      
      // Hvis der er ikke trykket på "Automatisk" knappen undervejs.
      if ( !stopAutomatic_ )
      {
	MsgStandard* msgCheckSoundAgain = new MsgStandard;
	
	std::cout << std::endl;
	std::cout << "AutomaticController: Sending 'check sound again' message to MeaurementsController" << std::endl << std::endl;
	
	// Send besked til MeasurementsController om at tjekke status på lyd igen.
	meaCtrlMq_->send(MeasurementsController::ID_CHECK_SOUND_AGAIN, msgCheckSoundAgain);
      }
      
      break;
    }
    
    case ID_MOBILE_STOPPED:
    {
      MsgStandard* msgMobileStopped = new MsgStandard;
      
      std::cout << std::endl;
      std::cout << "AutomaticController: Receiving 'stopped mobile' message from Mobile" << std::endl;
      std::cout << "AutomaticController: Sending 'stopped mobile' message to UIController" << std::endl << std::endl;
      
      // Send besked til UIControlelr om at uro er stoppet.
      UIMq_->send(UIController::ID_MOBILE_STOPPED, msgMobileStopped);
      
      if ( !stopAutomatic_ )
      {
	MsgStandard* msgCheckSoundAgain = new MsgStandard;
	
	std::cout << std::endl;
	std::cout << "AutomaticController: Sending 'check sound' message to MeaurementsController" << std::endl << std::endl;
	
	// Send besked til MeasurementsController om at tjekke status på lyd igen.
	meaCtrlMq_->send(MeasurementsController::ID_CHECK_SOUND_AGAIN, msgCheckSoundAgain);
      }
      
      break;
    }
  }
}

void AutomaticController::setMqs( osapi::MsgQueue* cradleMq, osapi::MsgQueue* mobileMq, osapi::MsgQueue* UIMq, osapi::MsgQueue* meaCtrlMq  )
{
	cradleMq_ = cradleMq;
	mobileMq_ = mobileMq;
	UIMq_ = UIMq;
	meaCtrlMq_ = meaCtrlMq;
}

void AutomaticController::run()
{
	while(running_)
	{
		unsigned long id;
		osapi::Message* msg = mq_.receive(id);
		handleMsg(msg,id);
		delete msg;
	}
}