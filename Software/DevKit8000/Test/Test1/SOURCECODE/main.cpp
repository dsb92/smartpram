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
  
  std::cout << std::endl << "Test-kommentar: Indstil indstillinger" << std::endl << std::endl;
  
  //setCurrentSettings(unsigned int _cradleTime, unsigned int _cradleSpeed, unsigned int _mobileTime, unsigned int _mobileSpeed, unsigned int _minTemperature, unsigned int _maxTemperature, unsigned int _maxSound)
  objUIController.setSaveSettings(10, 255, 15, 255, 15, 35, 60 ); 
  
  sleep(5);
  
  std::cout << std::endl << "Start ZigBee_out" << std::endl << std::endl;
  
  objZigBeeIF_out.startSend();
  
  sleep(5);
  
  //Start cradle, som når at udløbe
  std::cout << std::endl << "Test-kommentar: Start cradle i tiden cradleTime." << std::endl << std::endl;
  
  objUIController.cradleOnManUIbutton_ = true;
  objUIController.startCradle();
  
  std::cout << std::endl << "Test-kommentar: Vent 15 sek i mainprogrammet." << std::endl << std::endl;
  sleep(15);
  
  std::cout << std::endl << "Test-kommentar: Cradle burde være stoppet nu." << std::endl << std::endl;
  
  sleep(5);
  
  //Start cradle, med stop før tid
  std::cout << std::endl << "Test-kommentar: Start cradle i tiden cradleTime - men stoppes før tid." << std::endl << std::endl;
  
  objUIController.cradleOnManUIbutton_ = true;
  objUIController.startCradle();
  
  std::cout << std::endl << std::endl << "Test-kommentar: Vent 5 sek i mainprogrammet." << std::endl << std::endl;
  sleep(5);
  
  std::cout << std::endl << "Test-kommentar: Cradle stoppes før tid." << std::endl << std::endl;
  objUIController.stopCradle();
  
  sleep(5);
  
  
  //Start mobile, som når at udløbe
  std::cout << std::endl << "Test-kommentar: Start mobile i tiden mobileTime." << std::endl << std::endl;
  
  objUIController.mobileOnManUIbutton_ = true;
  objUIController.startMobile();
  
  std::cout << std::endl << "Test-kommentar: Vent 20 sek i mainprogrammet." << std::endl << std::endl;
  sleep(20);
  
  std::cout << std::endl << "Test-kommentar: Mobile burde være stoppet nu." << std::endl << std::endl;
  
  sleep(5);
  
  
  //Start mobile med stop før tid
  std::cout << std::endl << "Test-kommentar: Start mobile i tiden mobileTime - men stoppes før tid." << std::endl << std::endl;
  
  objUIController.mobileOnManUIbutton_ = true;
  objUIController.startMobile();
  
  std::cout << std::endl << "Test-kommentar: Vent 5 sek i mainprogrammet." << std::endl << std::endl;
  sleep(5);
  
  std::cout << std::endl << "Test-kommentar: Mobile stoppes før tid." << std::endl << std::endl;
  objUIController.stopMobile();
  
  sleep(5);
  
  
  //Start cradle og mobile så de overlapper hinanden
  std::cout << std::endl << "Test-kommentar: Start cradle i tiden cradleTime." << std::endl << std::endl;
  objUIController.cradleOnManUIbutton_ = true;
  objUIController.startCradle();
  
  std::cout << std::endl << "Test-kommentar: Vent 5 sek i mainprogrammet." << std::endl << std::endl;
  sleep(5);
  
  std::cout << std::endl << "Test-kommentar: Start mobile i tiden mobileTime." << std::endl << std::endl;
  objUIController.mobileOnManUIbutton_ = true;
  objUIController.startMobile();
  
  std::cout << std::endl << "Test-kommentar: Både Cradle og Mobile burde være stoppet nu." << std::endl << std::endl;
  
  sleep(20);
  
  std::cout << std::endl << "Test-kommentar: Testen er slut nu." << std::endl << std::endl;
  
  
 
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