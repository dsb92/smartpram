#include "ZigBeeIF_in.hpp"

ZigBeeIF_in::ZigBeeIF_in()
{
    // Intialisere ZigBee system calls
    system( RESET );
    system( INIT );
    system( SET_CH );
    system( SET_TXPOWER );
    system( SOURCE_PANID );
    system( SOURCE_SHORTADR );
    system( DESTINATION_PANID );
    system( DESTINATION_SHORTADR );
    system( FLUSH );
    system( STAT_IRQ );

  running_ = true;
}

void ZigBeeIF_in::receiveData()
{
  // Henter datapakke via en filoperations read funktion.
  // Det antages at funktionen "sover" her, hvis der ikke er data klar.
   getDatapackage();
    
   MsgMeasurements* msgData = new MsgMeasurements;
   
   // Henter temperaturværdi fra bufferIn_ array.
   msgData->temperature = getTemperature();
   // Henter lydværdi fra bufferIn_ array.
   msgData->sound = getSound();
   
   std::cout << std::endl;
   std::cout << "ZigBeeIF_in: Sending 'update measurements' message to MeasurementsController" << std::endl << std::endl;
   
   // Sender besked til MeasurementsController med de nye målinger.
   measurementsMq_->send(MeasurementsController::ID_UPDATE_MEASUREMENTS, msgData);  
}

signed char ZigBeeIF_in::getTemperature()
{
  return bufferIn_[TEMPERATURE_IN_POSITION];
}

signed char ZigBeeIF_in::getSound()
{
  return bufferIn_[SOUND_IN_POSITION];
}

void ZigBeeIF_in::setTest(signed char sound, signed char temperature) // SOM TEST
{
  bufferIn_[SOUND_IN_POSITION] = sound; // SOM TEST.
  bufferIn_[TEMPERATURE_IN_POSITION] = temperature;
}

void ZigBeeIF_in::getDatapackage()
{
  //Brug driver: Sov indtil data er tilgængelig og indlæs da denne.
    int fd = open( DEV_PATH, O_RDONLY );
    read( fd, &bufferIn_, BUFFERSIZE_IN );
    close( fd );
}

void ZigBeeIF_in::run()
{
  while(running_)
  {
     //udkommenteret til DEBUG 
    //receiveData();
    sleep(1); //DEBUG: Så der ikke opstår CPUburn
  }
}


void ZigBeeIF_in::setMqs( osapi::MsgQueue* measurementsMq )
{
  measurementsMq_ = measurementsMq;
}

