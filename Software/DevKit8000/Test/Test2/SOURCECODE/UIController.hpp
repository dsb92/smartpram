/*************BESKRIVELSE AF KLASSE************/
/* UIControlleren er en boundry klasse, som er selve broen fra QT interfacet til grænsefladen af Devkittet med messageQueues der ligger bagved. 
 * UIControlleren bliver her brugt som debug - men QT skal senere kalde de samme funktioner.
 * UIController skal kunne kommunikere med ManualController, AutomaticController og SettingsController. 
 * Dette kan desuden ses i setMqs() funktionen, da denne sætter de beskedkøer, den skal bruge for at sende beskederne til dem.
 */

#ifndef UICONTROLLER_H_
#define UICONTROLLER_H_

// Inkluderer common.hpp filen, hvori alle beskeder og filer, som UIController skal snakke med ligger.
#include "common.hpp"

// UIController nedarver fra osapi::ThreadFunctor, der er selve trådoprettelsen.
class UIController : public osapi::ThreadFunctor
{

public:
  // Constructor 
  UIController();
  
  // Besked id'er som UIController modtager fra andre kontrolklasser.
  enum
  {
    ID_CRADLE_STOPPED, // Besked som UIController får, når vugge er stoppet.
    ID_MOBILE_STOPPED, // Besked som UIController får, når uro er stoppet.
    ID_SETTINGS_CFM,   // Besked som UIController får, når nye indstillinger er blevet bekræftet.
    ID_MEASUREMENTS    // Besked som UIController får, når nye målinger er blevet modtaget og analyseret.
    
  };

  /*************FUNKTIONSPROTOTYPER************/
  
  // Prototype der henter klassens beskedkø via osapi::MsgQueue.
  osapi::MsgQueue* getMsgQueue() { return &mq_; }
  // Prototype der sætter alle beskedkøer som UIController skal bruge for at sende beskeder til de respektive klasser.
  void setMqs( osapi::MsgQueue* manualMq, osapi::MsgQueue* automaticMq, osapi::MsgQueue* settingsCtrlMq );
  // Prototype der starter vugge.
  void startCradle();
  // Prototype der stopper vugge.
  void stopCradle();
  // Prototype der starter uro.
  void startMobile();
  // Prototype der stopper uro.
  void stopMobile();
  // Prototype der starter automatisk styring.
  void startAutomatic();
  // Prototype der stopper automatisk styring.
  void stopAutomatic();
  // Prototype der henter nuværende indstillinger, når Bruger trykker på indstillingsknappen på QT user-interfacet.
  void getCurrentSettings();
  // Prototype der gemmer ændret indstillinger, når Bruger trykker på 'gem' knappen på QT user-interfacet.
  // Bemærk at vugge/urohastighed ikke kan justereres, men at denne automatisk kører 255 steps PWM styret. Og at denne er "gemt" væk på QT.
  void setSaveSettings(unsigned int _cradleTime, unsigned char _cradleSpeed, unsigned int _mobileTime, unsigned char _mobileSpeed, signed char _minTemperature, signed char _maxTemperature, signed char _maxSound); 

  // Prootype der sætter default indstillinger.
  void setDefaultSettings();

  /*************GLOBALE VARIABLER************/
  // Grunden til at disse variabler er sat som globale, er for at QT direkte kan tilgå dem.
  // Som en bedre løsning bør disse variabler være private, og man bør tilgå disse via set-og get metoder.
  
  // Temperaturvariabel af typen signed char - temperaturen kan være negativ.
  signed char temperatur_;
  // Lydvariabel af typen signed char - lydværdien kan ikke være negativ, men temperaturvariablen og lydvariablen indgå i samme signed char array og derfor skal denne // også være af typen signed char.
  signed char sound_;
  // Vuggetid variabel af typen unsigned int - Bruger har mulighed for at sætte vuggetid til maks 1092 minutter.
  // Dog har vi valgt Bruger maks kan indstille vuggetiden til 60 sekunder - dette er blot en prototype og kan i fremtidigt arbejde laves om minutter.
  unsigned int cradleTime_;
  // Urotid variabel af typen unsigned int.
  unsigned int mobileTime_;
  // Minimumstemperatur variabel af typen signed char.
  signed char minTemperature_;
  // Maksimumstemperatur variabel af typen signed char.
  signed char maxTemperature_;
  // Maksimal lydværdi af typen signed char.
  signed char maxSound_;
  
  // Vuggeknap af typen boolean som bruges i QT og her bruges til debug.  
  bool cradleOnManUIbutton_;
  // Uroknap af typen boolean som bruges i QT og her bruges til debug.  
  bool mobileOnManUIbutton_;
  // Automatiskknap af typen boolean, som bruges i QT og her bruges til debug. 
  bool automaticUIbutton_;
	
private:
  // UIController's egen beskedkø.
  osapi::MsgQueue mq_;
  // Størrelsen på beskedkøen.
  static const int MAX_QUEUE_SIZE = 10;
  // Funktionsprototype til at håndtere beskeder.
  void handleMsg(osapi::Message* msg, unsigned long id);
  // Bool variabel som sættes true i constructeren og bruges i en while-løkke i run() metoden.
  bool running_;
  // Bool minimumstemperatur variabel der vurderes til true eller false afhængig af tilstanden af temperaturen.
  bool minTemp_;
  // Bool maksimumsstemperatur variabel der vurderes til true eller false afhængig af tilstanden af temperaturen.
  bool maxTemp_;
  // Bool lyd variabel der vurderes til true eller false afhængig af tilstanden af lyden.
  bool soundHigh_;
  // Vuggehastighedsvariabel.
  unsigned char cradleSpeed_;
  // Urohastighedsvariabel.
  unsigned char mobileSpeed_;
  // Funktionsprototype der sætter gang i modtagelsen, håndteringen og sletningen af beskeder.
  void run();

  // Beskedkøer som UIController skal bruge.
  osapi::MsgQueue* manualMq_;
  osapi::MsgQueue* settingsCtrlMq_;
  osapi::MsgQueue* automaticMq_;

};

#endif
