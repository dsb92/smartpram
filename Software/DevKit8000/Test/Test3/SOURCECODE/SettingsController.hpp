/*************BESKRIVELSE AF KLASSE************/
/* SettingsController er en kontrolklasse, der har en association til en domain klasse kaldt Settings.
 * Denne klasse sørger for at kontrollere ændringer og forespørge om indstillinger. 
 * Den sørger også for at indlæse en fil hvori alle nuværende indstillinger ligger samt sørger for at broadcaste disse under opstart.

 */

#ifndef SETTINGSCONTROLLER_H_
#define SETTINGSCONTROLLER_H_

/*************INKLUDERER IOSTREAM, IOMANIP og FSTREAM TIL AT GEMME OG INDLÆSE EN FIL*************/
#include <iostream>
#include <iomanip>
#include <fstream>

#include "common.hpp" 

class SettingsController : public osapi::ThreadFunctor
{
public:
  // Association til Settings domain klassen.
  SettingsController( Settings* settingsPtr );
  
  enum
  {
    ID_SAVE_SETTINGS, 	// Besked som SettingsController får, når den skal gemme indstillinger.
    ID_SETTINGS_REQ,  	// Besked som SettingsController får, når den forespørge om nuværende indstillinger.
    ID_DEFAULT_SETTINGS // Besked som SettingsController får, når den sætte default indstillinger 
  };
  
  /*************FUNKTIONSPROTOTYPER************/
  
  // Prototype der henter klassens beskedkø via osapi::MsgQueue.
  osapi::MsgQueue* getMsgQueue() { return &mq_; }
  // Prototype der sætter alle beskedkøer som UIController skal bruge for at sende beskeder til de respektive klasser.
  void setMqs( osapi::MsgQueue* UIMq, osapi::MsgQueue* cradleMq, osapi::MsgQueue* mobileMq, osapi::MsgQueue* measurementsMq );
  // Prototype der indlæser nuværende indstillinger og broadcaster dem videre til dem, som skal bruge dem.
  void init();
  // Prototype der gemmer ændret indstillinger i en fil via fstream biblioteket.
  void saveSettings();
  // Prototype der indlæser nuværende indstillinger fra en fil via fstream biblioteket.
  void loadSettings();
  // Indlæser default indstillinger.
  void loadDefaultSettings();
  // Broadcaster indstillinger til dem, som skal bruge dem.
  void broadcastSettings();

private:
  osapi::MsgQueue mq_;
  static const int MAX_QUEUE_SIZE = 10;
  void handleMsg(osapi::Message* msg, unsigned long id);
  bool running_;
  void run();

  // Beskedkøer som SettingsController skal hente for at sende beskeder til de respektive klasser.
  osapi::MsgQueue* cradleMq_;
  osapi::MsgQueue* mobileMq_;
  osapi::MsgQueue* UIMq_;
  osapi::MsgQueue* measurementsMq_;

  // Associations pointer til Settings. Herved kan SettingsController tilgå Settings set-og get metoder.
  Settings* settingsPtr_;
};

#endif