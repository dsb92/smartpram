#include "ZigBeeIF_out.hpp"

ZigBeeIF_out::ZigBeeIF_out() : mq_(MAX_QUEUE_SIZE)
{
    // Initialisere ZigBee system kald.
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

void ZigBeeIF_out::handleMsg(osapi::Message* msg, unsigned long id)
{
  switch (id)
  {
    case ID_CRADLE_START:
    {
      // Der oprettes en ny beskedpointer, som sættes lig med den besked, som den modtager fra Cradle med opdateret vuggehastighed og vuggetid.
      MsgSendSetting* msgRec = static_cast<MsgSendSetting*> (msg);

      std::cout << "ZigBeeIF_out: Receiving 'start cradle' from Cradle" << std::endl;
      std::cout << "ZigBeeIF_out: Starting cradle with received cradle time: " << (unsigned int) msgRec->time << std::endl;
      
      // Sætter vuggehastighed med beskedens vuggehastighed som argument.
      setCradleSpeed( msgRec->speed );
      
      break;
    }
    
    case ID_CRADLE_STOP:
    {
      std::cout << "ZigBeeIF_out: Receiving 'stop cradle' from Cradle. Cradle has stopped" << std::endl;
      
      // Sætter vuggehastighed til 0.
      setCradleSpeed( 0 );
      break;
    }
    
     case ID_MOBILE_START:
     {
       // Der oprettes en ny beskedpointer, som sættes lig med den besked, som den modtager fra Mobile med opdateret urohastighed og urotid.
       MsgSendSetting* msgRec = static_cast<MsgSendSetting*> (msg);

      std::cout << "ZigBeeIF_out: Receiving 'start mobile' from Mobile" << std::endl;
      std::cout << "ZigBeeIF_out: Starting mobile with received mobile time: " << (unsigned int) msgRec->time << std::endl;
      
      // Sætter urohastighed med beskedens urohastighed som argument.
      setMobileSpeed( msgRec->speed );
      break;
     }
     
     case ID_MOBILE_STOP:
     {
      std::cout << "ZigBeeIF_out: Receiving 'stop mobile' from Mobile. Mobile has stopped" << std::endl;
      
      // Sætter urohastighed til 0.
      setMobileSpeed(0);
      break;
     }
     
     case ID_TIME_OUT:
     {
      // Sender data'er. 
      sendData();
      // Starter sendingstiden.
      timer_->arm(SENDFREQ_SEC*1000);
      break;     
     }
  };
}

void ZigBeeIF_out::setCradleSpeed( unsigned char cradleSpeed )
{
  // Argumentet sættes ind på bufferOut_ arrayet på plads 0.
  bufferOut_[CRADLE_OUT_POSITION] = cradleSpeed;
}

void ZigBeeIF_out::setMobileSpeed( unsigned char mobileSpeed )
{
  // Argumentet sættes ind på bufferOut_ arrayet på plads 1.
  bufferOut_[MOBILE_OUT_POSITION] =  mobileSpeed;
}

void ZigBeeIF_out::sendData( )
{
    //Send data med ZigBee driver
    int fd = open( DEV_PATH, O_WRONLY );
    write( fd, &bufferOut_, BUFFERSIZE_OUT );
    close( fd );

   
    //DEBUG std::cout
    std::cout << std::endl << std::endl << "Zigbee Out: Sending out cradleSpeed = " << (unsigned int) bufferOut_[CRADLE_OUT_POSITION] << " and mobileSpeed = " << (unsigned int) bufferOut_[MOBILE_OUT_POSITION] << "." << std::endl << std::endl;

}

void ZigBeeIF_out::startSend()
{
  // Alarmclock med en frekvens der svarer til sendefrekvensen.
  timer_->arm(SENDFREQ_SEC*1000);
}

void ZigBeeIF_out::stopSend()
{
  // Stop timer.
  timer_->disArm();
}


void ZigBeeIF_out::run()
{
  // Opret timerobjekt.
  timer_ = osapi::createNewTimer(&mq_, ID_TIME_OUT);
  
  setCradleSpeed( 0 );
  setMobileSpeed( 0 );

  while(running_)
  {
    unsigned long id;
    osapi::Message* msg = mq_.receive(id);
    handleMsg(msg,id);
    delete msg;
  }
}
