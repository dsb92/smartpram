#include "MeasurementsController.hpp"



MeasurementsController::MeasurementsController() : mq_(MAX_QUEUE_SIZE)
{
  running_ = true;
  
  soundHigh_ = false;  
  temperatureLow_ = false;
  temperatureHigh_ = false;
  
  for ( unsigned int i=0; i<AVERAGESOUNDCHECK_SIZE; i++ )
    averageSoundCheck_[i] = false;
  
}


void MeasurementsController::handleMsg(osapi::Message* msg, unsigned long id)
{

  switch (id)
  {
    // Dette er fra SettingsController og bliver kun sendt/modtaget, når indstillinger er blevet opdateret.
    case ID_UPDATE_SETTING:
    {
      MsgSendMeasurementsSetting* msgSet = static_cast<MsgSendMeasurementsSetting*>(msg);
      
      minTemperature_ = msgSet-> minTemperature;
      maxTemperature_ = msgSet-> maxTemperature;
      maxSound_ = msgSet-> maxSound;
      
      break;
    }
    
    // Dette er fra ZigBee_in.
    case ID_UPDATE_MEASUREMENTS:
    {
      //indlæs besked
      MsgMeasurements* msgData = static_cast<MsgMeasurements*>(msg);
      
      temperature_ = msgData-> temperature;
      sound_ = msgData-> sound;
      
      std::cout << std::endl;
      std::cout << "MeasurementsController: Received 'update measurements' message from ZigBee_in" << std::endl;
      std::cout << "MeasurementsController: Analyzing measurements... " << std::endl;
      
      //analyse
      analyse();
      
      //send besked til UI
      MsgAnalysedMeasurements* msgAnalysedData = new MsgAnalysedMeasurements;
      
      msgAnalysedData-> temperature = temperature_;
      msgAnalysedData-> sound = sound_;
      
      msgAnalysedData-> temperatureLow = temperatureLow_;
      msgAnalysedData-> temperatureHigh = temperatureHigh_;
      msgAnalysedData-> soundHigh = soundHigh_;
      
      std::cout << "MeasurementsController: Measured temperature: " << (unsigned int)(msgAnalysedData-> temperature) << std::endl;
      std::cout << "MeasurementsController: Temperature is ";
      
      if ( temperatureLow_ )
	std::cout << "low" << std::endl;
      
      else if ( temperatureHigh_ )
	std::cout << "high" << std::endl;
      
      else
	std::cout << "OK" << std::endl;
      
      std::cout << "MeasurementsController: Measured sound: " << (unsigned int)(msgAnalysedData-> sound) << std::endl;
      std::cout << "MeasurementsController: Sound is ";
      
      if ( soundHigh_ )
	std::cout << "too high" << std::endl;
      else
	std::cout << "OK" << std::endl;
      
      UIMq_->send(UIController::ID_MEASUREMENTS, msgAnalysedData);
      
      std::cout << std::endl;
      
      break;
    }
      
    case ID_CHECK_SOUND:
    {
      std::cout << std::endl;
      std::cout << "MeasurementsController: Receiving 'check sound' message from AutomaticController" << std::endl;
      std::cout << "MeasurementsController: Checking sound... " << std::endl;
      
      if ( getAverageSoundCheck() )
      {
	std::cout << "MeasurementsController: Sound is too high!" << std::endl;
	std::cout << "MeasurementsController: Sending 'sound is too high' message to AutomaticController" << std::endl;
	
	MsgStandard* msgStd = new MsgStandard;
	
	automaticMq_->send(AutomaticController::ID_START_CRADLE, msgStd);
      }
      else
      {
	std::cout << "MeasurementsController: Sound is fine!" << std::endl;
	timerCradle_->arm(TIMERWAIT*1000);	
      }
      
      std::cout << std::endl;
      
      break;
    }
    
    case ID_CHECK_SOUND_AGAIN:
    {
      std::cout << std::endl;
      std::cout << "MeasurementsController: Receiving 'check sound again' message from AutomaticController" << std::endl;
      std::cout << "MeasurementsController: Checking sound... " << std::endl;
      
      if ( getAverageSoundCheck() )
      {
	std::cout << "MeasurementsController: Sound is too high!" << std::endl;
	std::cout << "MeasurementsController: Sending 'sound is too high' message to AutomaticController" << std::endl;
	
	MsgStandard* msgStd = new MsgStandard;
	
	automaticMq_->send(AutomaticController::ID_START_MOBILE, msgStd);
      }
      else
      {
	std::cout << "MeasurementsController: Sound is fine!" << std::endl;
	timerMobile_->arm(TIMERWAIT*1000);	
      }
      
      std::cout << std::endl;
      break;
    }
    
    case ID_TIMEOUT_CRADLE:
    {
	if ( getAverageSoundCheck() )
	{
	  MsgStandard* msgStd = new MsgStandard;
	  
	  automaticMq_->send(AutomaticController::ID_START_CRADLE, msgStd);
	}
	else
	{
	  timerCradle_->arm(TIMERWAIT*1000);
	}
      break;
    }
    
    
    case ID_TIMEOUT_MOBILE:
    {
	if ( getAverageSoundCheck() )
	{
	  MsgStandard* msgStd = new MsgStandard;
	  
	  automaticMq_->send(AutomaticController::ID_START_MOBILE, msgStd);
	}
	else
	{
	  timerMobile_->arm(TIMERWAIT*1000);
	}
      break;
    }
    
    
    case ID_AUTOMATIC_STOPPED:
    {
      timerCradle_->disArm();	//stop timeren
      timerMobile_->disArm();	//stop timeren
      break;
    }
     
     
     
  }
}
  
void MeasurementsController::analyse( )
{
  if ( temperature_ < minTemperature_ )
  {
    temperatureLow_ = true;
    temperatureHigh_ = false;
  }
  else if ( temperature_ > maxTemperature_ )
  {
    temperatureLow_ = false;
    temperatureHigh_ = true;
  }
  else
  {
    temperatureLow_ = false;
    temperatureHigh_ = false;
  }
  
  if ( sound_ > maxSound_ )
  {
    soundHigh_ = true;
  }
  else
  {
    soundHigh_ = false;
  } 
  
  setAverageSoundCheck();
}

void MeasurementsController::setAverageSoundCheck()
{
  for ( unsigned int i=0; i<AVERAGESOUNDCHECK_SIZE-1; i++)
  {
    averageSoundCheck_[i] = averageSoundCheck_[i+1];
  }
  
  averageSoundCheck_[AVERAGESOUNDCHECK_SIZE-1] = soundHigh_;
}


bool MeasurementsController::getAverageSoundCheck()
{
  unsigned int trueCheck = 0;
  
  for ( unsigned int i=0; i<AVERAGESOUNDCHECK_SIZE; i++)
  {
    if ( averageSoundCheck_[i] )
      trueCheck++;
  }
  
  if ( trueCheck >= AVERAGESOUNDCHECK_TRUECHECK )
    return true;
  else
    return false;
}

void MeasurementsController::setMqs( osapi::MsgQueue* UIMq, osapi::MsgQueue* automaticMq )
{
  UIMq_ = UIMq;
  automaticMq_ = automaticMq;
}


void MeasurementsController::run()
{
  timerCradle_ = osapi::createNewTimer(&mq_, ID_TIMEOUT_CRADLE);	//create timer object
  timerMobile_ = osapi::createNewTimer(&mq_, ID_TIMEOUT_CRADLE);	//create timer object
  
  while(running_)
  {
    unsigned long id;
    osapi::Message* msg = mq_.receive(id);
    handleMsg(msg,id);
    delete msg;
  }
  
  timerCradle_->disArm();	//stop timer
  timerMobile_->disArm();	//stop timer
}
