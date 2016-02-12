#include "UIController.hpp"

// Constructor initialisering der initialisere beskedkø og sætte de respektive boolvariabler(knapper) til false
// samt sætter running igang og temperatur og lyd til 0.
UIController::UIController() : mq_(MAX_QUEUE_SIZE)
{
  cradleOnManUIbutton_ = false;
  mobileOnManUIbutton_ = false;
  automaticUIbutton_ = false;
  running_ = true;
  temperatur_ = 0;
  sound_ = 0;
}

// Håndtering af beskeder, som UIController modtager.
void UIController::handleMsg(osapi::Message* msg, unsigned long id)
{

  switch (id)
  {
    case ID_CRADLE_STOPPED:
    {
      //UI modtager besked fra manualController/AutomaticController om at vuggen er stoppet, fordi den ønskede tid er gået.
      
      // Hvis automatisk styring kører, og hvis manuel vugge ikke kører.
      if ( automaticUIbutton_ & !cradleOnManUIbutton_ )
      {
	std::cout << "UIController: Receiving 'stopped cradle' message from AutomaticController. \nCradle has stopped due to timeout" << std::endl;
      }
      // Hvis automatisk styring ikke kører, og hvis manuel vugge kører.
      else if ( !automaticUIbutton_ & cradleOnManUIbutton_ )
      {
	std::cout << "UIController: Receiving 'stopped cradle' message from ManualController. \nCradle has stopped due to timeout" << std::endl;
	cradleOnManUIbutton_ = false;
      }

      break;
    }
    
    case ID_MOBILE_STOPPED:
    {
      //UI modtager besked fra manualController/AutomaticController om at vuggen er stoppet, fordi den ønskede tid er gået.
      
      // Hvis automatisk styring kører, og hvis manuel uro ikke kører.
      if ( automaticUIbutton_ & !mobileOnManUIbutton_ )
      {
	std::cout << "UIController: Receiving 'stopped mobile' message from AutomaticController. \nMobile has stopped due to timeout" << std::endl;
      }
      // Hvis automatisk styring ikke kører, og hvis manuel uro kører.
      else if ( !automaticUIbutton_ & mobileOnManUIbutton_ )
      {
	std::cout << "UIController: Receiving 'stopped cradle' message from ManualController. \nCradle has stopped due to timeout" << std::endl;
	mobileOnManUIbutton_ = false;
      }

      break;
    }
    
    case ID_SETTINGS_CFM:
    {
      // Sæt en ny besked pointer lig med den besked, som netop blev modtaget.
      MsgSettings* cfm = static_cast<MsgSettings*> (msg);
      
      // Udskriv ændret indstillinger.
      std::cout << "UIController:: Receiving 'confirm setting' message from SettingsController" << std::endl;
      std::cout << "UIController:: Current settings are: " << std::endl;
      std::cout << "Min.temperature: " << (unsigned int)(cfm->minTemperature) << std::endl;
      std::cout << "Max.temperature: " << (unsigned int)(cfm->maxTemperature) << std::endl;
      std::cout << "Max.sound: " << (unsigned int)(cfm->maxSound) << std::endl;
      std::cout << "Cradle time: " << (unsigned int)(cfm->cradleTime) << std::endl;
      std::cout << "Cradle speed: " << (unsigned int)(cfm->cradleSpeed) << std::endl;
      std::cout << "Mobile time: " << (unsigned int)(cfm->mobileTime) << std::endl;
      std::cout << "Mobile speed: " << (unsigned int)(cfm->mobileSpeed) << std::endl;
      
      // Sæt UIControllers private data'er lig med beskedens.
      cradleTime_ = cfm->cradleTime;
      cradleSpeed_ = cfm->cradleSpeed;
      mobileTime_ = cfm->mobileTime;
      mobileSpeed_ = cfm->mobileSpeed;
      minTemperature_ = cfm->minTemperature;
      maxTemperature_ = cfm->maxTemperature;
      maxSound_ = cfm->maxSound;

      break;
    }
    
    case ID_MEASUREMENTS:
    {
      // Sæt en ny besked pointer lig med den besked, som netop blev modtaget.
      MsgAnalysedMeasurements* msgAnalysedData = static_cast<MsgAnalysedMeasurements*> (msg);
      
      // Læs fra beskedens analyserede data'er og sæt lig med UIControllers.
      temperatur_ = (msgAnalysedData-> temperature);
      sound_ = (msgAnalysedData-> sound);
      minTemp_ = (msgAnalysedData->temperatureLow);
      maxTemp_ = (msgAnalysedData->temperatureHigh);
      soundHigh_ = (msgAnalysedData->soundHigh);
      
      // Udskriv status på lyd og temperatur.
      std::cout << std::endl << "UIcontroller: Measurementdata received" << std::endl; 
       
      if (minTemp_)
	std::cout << "TEMPERATURE IS TOO LOW!" << std::endl;
      else if (maxTemp_)
	std::cout << "TEMPERATURE IS TOO HIGH!" << std::endl;
      else
	std::cout << "TEMPERATURE IS OK" << std::endl;
       
      if (soundHigh_)
	std::cout << "SOUND IS TOO HIGH!" << std::endl;
      else
	std::cout << "SOUND IS OK!" << std::endl;
       
      std::cout << std::endl << std::endl;
       
      break;
    }
  }
}

// Sæt lokale beskedkøer lig med UIControllers. Herved har UIController de nødvendige beskedkøer for at kunne sende beskeder.
void UIController::setMqs(osapi::MsgQueue* manualMq, osapi::MsgQueue* automaticMq, osapi::MsgQueue* settingsCtrlMq )
{
  manualMq_ = manualMq;
  settingsCtrlMq_ = settingsCtrlMq;
  automaticMq_ = automaticMq;
}

// Start vugge.
void UIController::startCradle()
{
  // Hvis automatisk styring ikke kører, og hvis manuel vugge kører.
  if( !automaticUIbutton_ && cradleOnManUIbutton_ )
  {
    MsgStandard* msgStartCradle = new MsgStandard;

    std::cout << "UIController: Sending 'start cradle manual' message to ManualController" << std::endl;
    
    // Brug ManualController's beskedkø til at sende en besked.
    // Send besked til ManualController - hvordan den skal håndtere det "ID_START_CRADLE" og selve standard beskeden, der tom.
    manualMq_->send(ManualController::ID_START_CRADLE, msgStartCradle);
  }
  else
  {
    std::cout << "UIController: Cannot start 'startCradle' command because manuel mobile or automatic is running" << std::endl;
  }
}

// Stop vugge
void UIController::stopCradle()
{
  // Stop kun vugge, hvis vugge allerede kører.
  if( cradleOnManUIbutton_ )
  {
    MsgStandard* msgStopCradle = new MsgStandard;
    std::cout << "UIController: Sending 'stop cradle' message to ManualController" << std::endl;
    // Send besked til ManualController om at stoppe vugge.
    manualMq_->send(ManualController::ID_STOP_CRADLE, msgStopCradle);
  }
  else
    std::cout << "UIController: Cannot start 'stopCradle' command because manuel cradle is not running" << std::endl;

}
// Star uro.
void UIController::startMobile()
{
  // Hvis automatisk styring ikke kører, og hvis manuel uro kører.
  if( !automaticUIbutton_ && mobileOnManUIbutton_ )
  {
    MsgStandard* msgStartMobile = new MsgStandard;
    
    std::cout << "UIController: Sending 'start mobile' message to ManualController" << std::endl;
    
    // Send besked til ManualController om at starte uro.
    manualMq_->send(ManualController::ID_START_MOBILE, msgStartMobile);
  }
  else
  {
    std::cout << "UIController: Cannot start 'startMobile' command because manuel cradle or automatic is running" << std::endl;
  }

}

// Stop uro.
void UIController::stopMobile()
{
  // Stop kun uro, hvis uro allerede kører.
  if( mobileOnManUIbutton_ )
  {
    MsgStandard* msgStopMobile = new MsgStandard;
    std::cout << "UIController: Sending 'stop mobile' message to ManualController" << std::endl;
    
    // Send besked til ManualController om at stoppe uro.
    manualMq_->send(ManualController::ID_STOP_MOBILE, msgStopMobile);
  }
  else
    std::cout << "UIController: Cannot start 'stopMobile' command because mobile manuel is not running" << std::endl;
}

// Start automatisk styring.
void UIController::startAutomatic()
{
  // Start kun automatisk styring, hvis der er trykket på "Automatisk" knappen, og hvis vugge og uro ikke kører.
  if( automaticUIbutton_ )
  {
    MsgStandard* msgStartAutomatic = new MsgStandard;
    
    std::cout << "UIController: Sending 'start automatic cradle' message to AutomaticController" << std::endl;
    
    // Send besked til AutomaticController om at tjekke status på lyden.
    automaticMq_->send(AutomaticController::ID_CHECK_SOUND, msgStartAutomatic);
  }
  else
  {
    std::cout << "UIController: Cannot start 'startAutomatic' command because manuel cradle or mobile is running" << std::endl;
  }
}

// Stop automatisk styring.
void UIController::stopAutomatic()
{
  // Stop kun automatisk styring, hvis den allerede kører.
  if( automaticUIbutton_ )
  {
    MsgStandard* msgStopAutomatic = new MsgStandard;
    std::cout << "UIController: Sending 'stop automatic' message to AutomaticController" << std::endl;
    
    // Send besked til AutomaticController om at stoppe automatisk styring.
    automaticMq_->send(AutomaticController::ID_STOP_AUTOMATIC, msgStopAutomatic);
    
    automaticUIbutton_ = false;
  }
  else
    std::cout << "UIController: Cannot start 'stopAutomatic' command because automatic is not running" << std::endl;
}

// Hent nuværende indstillinger.
void UIController::getCurrentSettings()
{  
  MsgStandard* msgGetSettings = new MsgStandard;
  std::cout << "UIController: Requesting 'current settings' message to SettingsController" << std::endl;
  
  // Send besked til SettingsController om at forespørge nuværende indstillinger.
  settingsCtrlMq_->send(SettingsController::ID_SETTINGS_REQ, msgGetSettings);
}

// Gem ændret indstillinger.
void UIController::setSaveSettings(unsigned int cradleTime, unsigned char cradleSpeed, unsigned int mobileTime, unsigned char mobileSpeed, signed char minTemperature, signed char maxTemperature, signed char maxSound)
{
    MsgSettings* msgSet = new MsgSettings;

    // Læs ændret indstillinger og tildel til beskedens.
    msgSet->cradleTime = cradleTime;
    msgSet->cradleSpeed = cradleSpeed;
    msgSet->mobileTime = mobileTime;
    msgSet->mobileSpeed = mobileSpeed;
    msgSet->minTemperature = minTemperature;
    msgSet->maxTemperature = maxTemperature;
    msgSet->maxSound = maxSound;
    
    std::cout << "UIController: Sending 'save settings' message to SettingsController" << std::endl;
    
    // Send besked til SettingsController om at gemme indstillinger med beskeden, der indeholder de nye indstillinger.
    settingsCtrlMq_->send(SettingsController::ID_SAVE_SETTINGS, msgSet);
}

// Sæt default indstillinger.
void UIController::setDefaultSettings()
{
  MsgStandard* msgSet = new MsgStandard;
  
  std::cout << "UIController: Sending 'setting default settings' message to SettingsController" << std::endl;
  
  // Send besked til SettingsController om at sætte default indstillinger.
  settingsCtrlMq_->send(SettingsController::ID_DEFAULT_SETTINGS, msgSet);
}


// Modtag besked, håndtere og slet.
void UIController::run()
{
	while(running_)
	{
		unsigned long id;
		osapi::Message* msg = mq_.receive(id);
		handleMsg(msg,id);
		delete msg;
	}
}
