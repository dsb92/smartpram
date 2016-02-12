
#ifndef MEASUREMENTSCONTROLLER_H_
#define MEASUREMENTSCONTROLLER_H_

#include "common.hpp" 


class MeasurementsController : public osapi::ThreadFunctor
{

public:
  MeasurementsController();
  
  enum
  {
    ID_UPDATE_SETTING,
    ID_UPDATE_MEASUREMENTS,
    ID_CHECK_SOUND,
    ID_CHECK_SOUND_AGAIN,
    ID_TIMEOUT_CRADLE,
    ID_TIMEOUT_MOBILE,
    ID_AUTOMATIC_STOPPED
  };

  osapi::MsgQueue* getMsgQueue() { return &mq_; }

  void setMqs( osapi::MsgQueue* UIMq, osapi::MsgQueue* automaticMq );
  void analyse();
  void setAverageSoundCheck();
  bool getAverageSoundCheck();

private:
  osapi::MsgQueue mq_;
  static const int MAX_QUEUE_SIZE = 10;
  void handleMsg(osapi::Message* msg, unsigned long id);
  bool running_;
  bool checkSound_;
  void run();
  
  static const int TIMERWAIT = 1;
  
  static const unsigned int AVERAGESOUNDCHECK_SIZE = 5;
  static const unsigned int AVERAGESOUNDCHECK_TRUECHECK = 3;
  bool averageSoundCheck_[AVERAGESOUNDCHECK_SIZE];
  
  
  osapi::ITimerId*  timerCradle_;
  osapi::ITimerId*  timerMobile_;

  osapi::MsgQueue* UIMq_;
  osapi::MsgQueue* automaticMq_;
  
  signed char minTemperature_;
  signed char maxTemperature_;
  signed char maxSound_;
  
  signed char temperature_;
  signed char sound_;
  
  bool temperatureLow_;
  bool temperatureHigh_;
  bool soundHigh_;
  
};

#endif