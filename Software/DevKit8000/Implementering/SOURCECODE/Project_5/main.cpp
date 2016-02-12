#include "Filer/common.hpp"
#include "uiboundary.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UIController objUIController;
    UiBoundary w(&objUIController);
    w.show();

      ManualController objManualController;
      AutomaticController objAutomaticController;
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

      objMeasurementsController.setMqs( objUIController.getMsgQueue(), objAutomaticController.getMsgQueue());

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
      objZigBeeIF_out.startSend();

      return a.exec();

      thrUIController.join();
        thrManualController.join();
        thrAutomaticController.join();
        thrSettingsController.join();
        thrMeasurementsController.join();
        thrCradle.join();
        thrMobile.join();
        thrZigBeeIF_out.join();
        thrZigBeeIF_in.join();

}

