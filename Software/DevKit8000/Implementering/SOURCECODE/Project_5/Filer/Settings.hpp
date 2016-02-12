
#ifndef SETTINGS_H_
#define SETTINGS_H_

class Settings
{

public:
  Settings() 
  {
    setMinTemperature();
    setMaxTemperature();
    setMaxSound();
    setCradleTime();
    setCradleSpeed();
    setMobileTime();
    setMobileSpeed();
  }
  
  void setMinTemperature( signed char minTemperature = 15 ) { minTemperature_ = minTemperature;}
  signed char getMinTemperature() { return minTemperature_;}
  void setMaxTemperature( signed char maxTemperature = 35 ) { maxTemperature_ = maxTemperature;}
  signed char getMaxTemperature() { return maxTemperature_; }
  void setMaxSound( signed char maxSound = 60 ) { maxSound_ = maxSound;}
  signed char getMaxSound( ) { return maxSound_; }
  void setCradleTime( unsigned int cradleTime = 30 ) { cradleTime_ = cradleTime;}
  unsigned int getCradleTime() { return cradleTime_; }
  void setCradleSpeed( unsigned char cradleSpeed = 255 ) { cradleSpeed_ = cradleSpeed;}
  unsigned char getCradleSpeed() { return cradleSpeed_; }
  void setMobileTime( unsigned int mobileTime = 30 ) { mobileTime_ = mobileTime;}
  unsigned int getMobileTime() { return mobileTime_; }
  void setMobileSpeed( unsigned char mobileSpeed = 255 ) { mobileSpeed_ = mobileSpeed;}
  unsigned char getMobileSpeed() { return mobileSpeed_; }
  

private:
  signed char minTemperature_;
  signed char maxTemperature_;
  signed char maxSound_;
  
  unsigned int cradleTime_;
  unsigned char cradleSpeed_;
  unsigned int mobileTime_;
  unsigned char mobileSpeed_;
};

#endif
