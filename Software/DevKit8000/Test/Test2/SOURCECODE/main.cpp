#include "common.hpp"


int main()
{
  
  //initialiser tråde og objekter til testcases
  
  ManualController objManualController;
  AutomaticController objAutomaticController;
  UIController objUIController;
  Settings objSettings;
  SettingsController objSettingsController(&objSettings);
  MeasurementsController objMeasurementsController;
  Cradle objCradle;
  Mobile objMobile;
  ZigBeeIF_out objZigBeeIF_out;
  ZigBeeIF_in objZigBeeIF_in;
  
  objUIController.setMqs( objManualController.getMsgQueue(), objAutomaticController.getMsgQueue(),  objSettingsController.getMsgQueue() );
  
  objManualController.setMqs( objCradle.getMsgQueue(), objMobile.getMsgQueue(), objUIController.getMsgQueue() );
  
  objAutomaticController.setMqs( objCradle.getMsgQueue(), objMobile.getMsgQueue(), objUIController.getMsgQueue(), objMeasurementsController.getMsgQueue()  );
  
  objSettingsController.setMqs( objUIController.getMsgQueue(), objCradle.getMsgQueue(), objMobile.getMsgQueue(), objMeasurementsController.getMsgQueue() );
  
  objMeasurementsController.setMqs( objUIController.getMsgQueue(), objAutomaticController.getMsgQueue() );
  
  objCradle.setMqs( objManualController.getMsgQueue(), objAutomaticController.getMsgQueue(), objZigBeeIF_out.getMsgQueue() );
  
  objMobile.setMqs( objManualController.getMsgQueue(), objAutomaticController.getMsgQueue(), objZigBeeIF_out.getMsgQueue() );
  
  objZigBeeIF_in.setMqs( objMeasurementsController.getMsgQueue() );
  
  osapi::Thread thrUIController(&objUIController);
  osapi::Thread thrManualController(&objManualController);
  osapi::Thread thrAutomaticController(&objAutomaticController);
  osapi::Thread thrSettingsController(&objSettingsController);
  osapi::Thread thrMeasurementsController(&objMeasurementsController);
  osapi::Thread thrCradle(&objCradle);
  osapi::Thread thrMobile(&objMobile);
  osapi::Thread thrZigBeeIF_out(&objZigBeeIF_out);
  osapi::Thread thrZigBeeIF_in(&objZigBeeIF_in);
  
  thrUIController.start();
  thrManualController.start();
  thrAutomaticController.start();
  thrSettingsController.start();
  thrMeasurementsController.start();
  thrCradle.start();
  thrMobile.start();
  thrZigBeeIF_out.start();
  thrZigBeeIF_in.start();
  
  
  objSettingsController.init();
  
  
  //indstil settings, således at disse indstillers værdier kan forventes i den resterende test.
  
  std::cout << std::endl << "Test-kommentar: Indstil indstillinger. MinTemp = 15, MaxTemp = 35, MaxSound = 60" << std::endl << std::endl;
  
  //setCurrentSettings(unsigned int _cradleTime, unsigned int _cradleSpeed, unsigned int _mobileTime, unsigned int _mobileSpeed, unsigned int _minTemperature, unsigned int _maxTemperature, unsigned int _maxSound)
  objUIController.setSaveSettings(4, 255, 4, 255, 15, 35, 60 ); 
  
  sleep(5);
  
  std::cout << std::endl << std::endl << "Test-kommentar: (simuleret) Der modtages datapakke med temperatur = 25 og lyd = 10. " << std::endl << std::endl;
  objZigBeeIF_in.setTest(10, 25);
  objZigBeeIF_in.receiveData();

  sleep(1);
  
  std::cout << std::endl << std::endl << "Test-kommentar: (simuleret) Der modtages datapakke med temperatur = 37 og lyd = 31. " << std::endl << std::endl;
  objZigBeeIF_in.setTest(31, 37);
  objZigBeeIF_in.receiveData();

  sleep(1);
  
  std::cout << std::endl << std::endl << "Test-kommentar: (simuleret) Der modtages datapakke med temperatur = 37 og lyd = 68. " << std::endl << std::endl;
  objZigBeeIF_in.setTest(68, 37);
  objZigBeeIF_in.receiveData();

  sleep(1);
  
  std::cout << std::endl << std::endl << "Test-kommentar: (simuleret) Der modtages datapakke med temperatur = 12 og lyd = 68. " << std::endl << std::endl;
  objZigBeeIF_in.setTest(68, 12);
  objZigBeeIF_in.receiveData();
  
  sleep(1);
  
  std::cout << std::endl << "Test-kommentar: Indstil indstillinger. MinTemp = 20, MaxTemp = 30, MaxSound = 41" << std::endl << std::endl;
  objUIController.setSaveSettings(4, 255, 4, 255, 20, 30, 41 ); 
  
  sleep(1);
  
  std::cout << std::endl << std::endl << "Test-kommentar: (simuleret) Der modtages datapakke med temperatur = 12 og lyd = 42. " << std::endl << std::endl;
  objZigBeeIF_in.setTest(42, 12);
  objZigBeeIF_in.receiveData();
  
  sleep(1);
  
  std::cout << std::endl << std::endl << "Test-kommentar: (simuleret) Der modtages datapakke med temperatur = 29 og lyd = 40. " << std::endl << std::endl;
  objZigBeeIF_in.setTest(40, 29);
  objZigBeeIF_in.receiveData();
 
  sleep(1);

  std::cout << std::endl << std::endl << "Testen er slut nu." << std::endl << std::endl;
  
 
  //Evt. oprydning (eksekveres aldrig)
  
  thrUIController.join();
  thrManualController.join();
  thrAutomaticController.join();
  thrSettingsController.join();
  thrMeasurementsController.join();
  thrCradle.join();
  thrMobile.join();
  thrZigBeeIF_out.join();
  thrZigBeeIF_in.join();

  return 0;
}