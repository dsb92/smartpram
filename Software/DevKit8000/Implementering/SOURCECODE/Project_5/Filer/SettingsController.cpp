#include "SettingsController.hpp"

// Skab relation mellem Settings og SettingsController, så vi kan kalde hinandens metoder.  
SettingsController::SettingsController( Settings* settingsPtr ) : mq_(MAX_QUEUE_SIZE)
{
  settingsPtr_ = settingsPtr;
  
  running_ = true;
}

// Indlæs indstillingsfilen og broadcast indstillinger til de klasser, som har brug for dem.
void SettingsController::init()
{
  loadSettings();
  broadcastSettings();
}

// Gemmer indstillinger i en fil.
void SettingsController::saveSettings()
{
  // Opret et objekt af ofstream og gør filen binært(ikke læseligt)
  std::ofstream outFile( "settings.dat", std::ios::binary );
  
  // Skrive til filen med det som settingsPtr_ peger på og med størrelsen på Settings.
  outFile.write( reinterpret_cast< const char * >( settingsPtr_ ), sizeof( Settings ) );
  
  // Luk fil.
  outFile.close();
}

// Indlæs indstillingsfilen.
void SettingsController::loadSettings()
{
  // Opret et objekt af ifstream og indlæs en fil af typen dat.
  std::ifstream inFile( "settings.dat", std::ios::in );
  // Hvis filen eksisterer, læs filen.
  if (inFile)
    inFile.read( reinterpret_cast< char * >( settingsPtr_ ), sizeof( Settings ) );
  // Hvis filen ikke eksisterer, brug default indstillinger og gem det i en ny fil. 
  else
    loadDefaultSettings();
  
 inFile.close();
}

// Indlæs default indstillinger
void SettingsController::loadDefaultSettings()
{
  // Hvis set funktionerne ikke indeholder argumenter, sættes variablerne til default værdier bestemt i Settings klassen.
  (settingsPtr_)->setMinTemperature();
  (settingsPtr_)->setMaxTemperature();
  (settingsPtr_)->setMaxSound();
  (settingsPtr_)->setCradleTime();
  (settingsPtr_)->setCradleSpeed();
  (settingsPtr_)->setMobileTime();
  (settingsPtr_)->setMobileSpeed();
  
  saveSettings();	// gemmer indstillingerne
  broadcastSettings();
  
}

// Broadcast indstillinger
void SettingsController::broadcastSettings()
{
    // Sender besked til Cradle om at læse nye indstillinger fra Settings.
      
    MsgSendSetting* msgSendToCradle = new MsgSendSetting;
      
    msgSendToCradle->time = ( (settingsPtr_)->getCradleTime() );
    msgSendToCradle->speed = ( (settingsPtr_)->getCradleSpeed() );
    
    cradleMq_->send(Cradle::ID_UPDATE_SETTING, msgSendToCradle);
    
    // Sender besked til Mobile om at læse nye indstillinger fra Settings.
    
    MsgSendSetting* msgSendToMobile = new MsgSendSetting;
      
    msgSendToMobile->time = ( (settingsPtr_)->getMobileTime() );
    msgSendToMobile->speed = ( (settingsPtr_)->getMobileSpeed() );
    
    mobileMq_->send(Mobile::ID_UPDATE_SETTING, msgSendToMobile);
      
    // Sender besked til GetMeasurements om at læse nye indstillinger fra Settings.
      
    MsgSendMeasurementsSetting* msgSendToMeasurements = new MsgSendMeasurementsSetting;
    
    msgSendToMeasurements->minTemperature = ( (settingsPtr_)->getMinTemperature() );
    msgSendToMeasurements->maxTemperature = ( (settingsPtr_)->getMaxTemperature() );
    msgSendToMeasurements->maxSound = ( (settingsPtr_)->getMaxSound() );
    
    measurementsMq_->send(MeasurementsController::ID_UPDATE_SETTING, msgSendToMeasurements);
    
}

// Håndter de beskeder som SettingsController modtager.
void SettingsController::handleMsg(osapi::Message* msg, unsigned long id)
{
  switch (id)
  {
    case ID_SETTINGS_REQ:
    {    
      MsgSettings* cfm = new MsgSettings;
      
      std::cout << std::endl;
      std::cout << "SettingsController: Receiving 'current settings' message from UIController" << std::endl;
      
      // Brug settings pointer til at bruge Settings' get metode til at hente indstillinger.
      // Assign disse til beskeden, der skal sendes.
      cfm->minTemperature = (settingsPtr_)->getMinTemperature();
      cfm->maxTemperature = (settingsPtr_)->getMaxTemperature();
      cfm->maxSound = (settingsPtr_)->getMaxSound();
      cfm->cradleTime = (settingsPtr_)->getCradleTime();
      cfm->cradleSpeed = (settingsPtr_)->getCradleSpeed();
      cfm->mobileTime = (settingsPtr_)->getMobileTime();
      cfm->mobileSpeed = (settingsPtr_)->getMobileSpeed();
      
      std::cout << "SettingsController: Sending 'confirm settings' message to UIController" << std::endl << std::endl;
      
      // Send besked til UIController om at indstillingerne er blevet bekræftet.
      UIMq_->send(UIController::ID_SETTINGS_CFM, cfm);

      break;
    }
    
    
    case ID_SAVE_SETTINGS:
    {
      MsgSettings* set = static_cast<MsgSettings*>(msg);
      
      //Opdater Settings med indstillinger fra UI
      (settingsPtr_)->setMinTemperature( set->minTemperature );
      (settingsPtr_)->setMaxTemperature( set->maxTemperature );
      (settingsPtr_)->setMaxSound( set->maxSound );
      (settingsPtr_)->setCradleTime( set->cradleTime );
      (settingsPtr_)->setCradleSpeed( set->cradleSpeed );
      (settingsPtr_)->setMobileTime( set->mobileTime );
      (settingsPtr_)->setMobileSpeed( set->mobileSpeed );
      
      std::cout << std::endl << "SettingsController: Settings saved!" << std::endl << std::endl;
      
      saveSettings();	//gemmer indstillingerne
      broadcastSettings(); // Broadcaster indstillinger
      
      break;
    }
    
    case ID_DEFAULT_SETTINGS:
    {
      loadDefaultSettings();
      
      break;
    }
  }
}

void SettingsController::setMqs( osapi::MsgQueue* UIMq, osapi::MsgQueue* cradleMq, osapi::MsgQueue* mobileMq, osapi::MsgQueue* measurementsMq )
{
	cradleMq_ = cradleMq;
	mobileMq_ = mobileMq;
	UIMq_ = UIMq;
	measurementsMq_ = measurementsMq;
}


void SettingsController::run()
{
	while(running_)
	{
		unsigned long id;
		osapi::Message* msg = mq_.receive(id);
		handleMsg(msg,id);
		delete msg;
	}
}
