#include "ManualController.hpp"

ManualController::ManualController() : mq_(MAX_QUEUE_SIZE)
{
  running_ = true;
}

void ManualController::handleMsg(osapi::Message* msg, unsigned long id)
{

  switch (id)
  {
    case ID_START_CRADLE:
    {
      MsgStandard* msgStartManCradle = new MsgStandard;
      
      std::cout << std::endl;
      std::cout << "ManualController: Receiving 'start cradle manual' message from UIController" << std::endl;
      std::cout << "ManuelController: Sending 'start cradle manuel' message to Cradle" << std::endl << std::endl;
      
      // Sender besked til Cradle om at starte vugge.
      cradleMq_->send(Cradle::ID_START_CRADLE_MANUEL, msgStartManCradle);
      
      break;
    }
    
    case ID_CRADLE_STOPPED:
    {
      MsgStandard* msgCradleStopped= new MsgStandard;
      
      std::cout << std::endl;
      std::cout << "ManualController: Receiving 'stopped cradle' message from Cradle" << std::endl;
      std::cout << "ManuelController: Sending 'stopped cradle' message to UIController" << std::endl << std::endl;
      
      // Sender besked til UIController om at vugge er stoppet.
      UIMq_->send(UIController::ID_CRADLE_STOPPED, msgCradleStopped);

      break;
    }
    
    case ID_STOP_CRADLE:
    {
      MsgStandard* msgStopCradle = new MsgStandard;
      
      std::cout << std::endl;
      std::cout << "ManualController: Receiving 'stop cradle' message from UIController" << std::endl;
      std::cout << "ManuelController: Sending 'stop cradle' message to Cradle" << std::endl << std::endl;
      
      // Sender besked til Cradle om at stoppe vugge.
      cradleMq_->send(Cradle::ID_STOP_CRADLE, msgStopCradle);
      
      break;
    }
    
    case ID_START_MOBILE:
    {
      MsgStandard* msgStartManMobile = new MsgStandard;
      
      std::cout << std::endl;
      std::cout << "ManualController: Receiving 'start mobile' message from UIController" << std::endl;
      std::cout << "ManuelController: Sending 'start mobile' message to Mobile" << std::endl << std::endl;
      
      // Sender besked til Mobile om at starte uro.
      mobileMq_->send(Mobile::ID_START_MOBILE_MANUEL, msgStartManMobile);
      
      break;
    }
    
    case ID_MOBILE_STOPPED:
    {
      MsgStandard* msgMobileStopped = new MsgStandard;
      
      std::cout << std::endl;
      std::cout << "ManualController: Receiving 'stopped mobile' message from Mobile" << std::endl;
      std::cout << "ManuelController: Sending 'stopped mobile' message to UIController" << std::endl << std::endl;
      
      // Sender besked til UIController om at uro er stoppet.
      UIMq_->send(UIController::ID_MOBILE_STOPPED, msgMobileStopped);
      
      break;
    }
    
    case ID_STOP_MOBILE:
    {
      MsgStandard* msgStopMobile = new MsgStandard;
      
      std::cout << std::endl;
      std::cout << "ManualController: Receiving 'stop mobile' message from UIController" << std::endl;
      std::cout << "ManuelController: Sending 'stop mobile' message to Mobile" << std::endl << std::endl;
      
      // Sender besked til Mobile om at stoppe uro.
      mobileMq_->send(Mobile::ID_STOP_MOBILE, msgStopMobile);
      
      break;
    }
  }
}

void ManualController::setMqs( osapi::MsgQueue* cradleMq, osapi::MsgQueue* mobileMq, osapi::MsgQueue* UIMq )
{
	cradleMq_ = cradleMq;
	mobileMq_ = mobileMq;
	UIMq_ = UIMq;
}


void ManualController::run()
{
	while(running_)
	{
		unsigned long id;
		osapi::Message* msg = mq_.receive(id);
		handleMsg(msg,id);
		delete msg;
	}
}
