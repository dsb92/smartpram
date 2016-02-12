/********************************************************************************
** Form generated from reading UI file 'uiboundary.ui'
**
** Created: Mon Dec 16 14:49:54 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIBOUNDARY_H
#define UI_UIBOUNDARY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UiBoundary
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *SmartPram;
    QPushButton *Button_Vugge;
    QPushButton *Button_Uro;
    QPushButton *Button_Automatisk;
    QPushButton *Button_Indstillinger;
    QLCDNumber *Temp_LCD;
    QLabel *Temperatur;
    QLabel *Degress;
    QLCDNumber *Sound_LCD;
    QLabel *Procent;
    QLabel *Sound;
    QLabel *Temp_Alarm;
    QLabel *Vugge_Ikon;
    QLabel *Uro_Ikon;
    QLabel *Auto_Ikon;
    QLabel *Sound_Alarm;
    QWidget *Indstillinger;
    QPushButton *Save_settings;
    QSlider *Lydmax_Slider;
    QLabel *Lydmax_Label;
    QLabel *Vuggetid_Label;
    QLabel *Urotid_Label;
    QSlider *Vuggetid_Slider;
    QSlider *Urotid_Slider;
    QLabel *Urotid_vaerdi;
    QLabel *lydmax_vaerdi;
    QSlider *Tempmax_Slider;
    QLabel *Tempmax_Label;
    QSlider *Tempmin_Slider;
    QLabel *Tempmin_Label;
    QLabel *Tempmax_vaerdi;
    QLabel *Tempmin_vaerdi;
    QLabel *Vuggetid_vaerdi;
    QPushButton *Button_cancel;
    QPushButton *Button_default;

    void setupUi(QMainWindow *UiBoundary)
    {
        if (UiBoundary->objectName().isEmpty())
            UiBoundary->setObjectName(QString::fromUtf8("UiBoundary"));
        UiBoundary->resize(480, 272);
        UiBoundary->setMaximumSize(QSize(480, 272));
        centralWidget = new QWidget(UiBoundary);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, -30, 480, 305));
        tabWidget->setMinimumSize(QSize(480, 272));
        tabWidget->setMaximumSize(QSize(480, 305));
        SmartPram = new QWidget();
        SmartPram->setObjectName(QString::fromUtf8("SmartPram"));
        Button_Vugge = new QPushButton(SmartPram);
        Button_Vugge->setObjectName(QString::fromUtf8("Button_Vugge"));
        Button_Vugge->setGeometry(QRect(30, 30, 101, 41));
        Button_Vugge->setStyleSheet(QString::fromUtf8(""));
        Button_Uro = new QPushButton(SmartPram);
        Button_Uro->setObjectName(QString::fromUtf8("Button_Uro"));
        Button_Uro->setGeometry(QRect(160, 30, 101, 41));
        Button_Automatisk = new QPushButton(SmartPram);
        Button_Automatisk->setObjectName(QString::fromUtf8("Button_Automatisk"));
        Button_Automatisk->setGeometry(QRect(80, 80, 101, 41));
        Button_Indstillinger = new QPushButton(SmartPram);
        Button_Indstillinger->setObjectName(QString::fromUtf8("Button_Indstillinger"));
        Button_Indstillinger->setGeometry(QRect(310, 30, 141, 41));
        Temp_LCD = new QLCDNumber(SmartPram);
        Temp_LCD->setObjectName(QString::fromUtf8("Temp_LCD"));
        Temp_LCD->setGeometry(QRect(320, 130, 71, 31));
        Temp_LCD->setProperty("intValue", QVariant(0));
        Temperatur = new QLabel(SmartPram);
        Temperatur->setObjectName(QString::fromUtf8("Temperatur"));
        Temperatur->setGeometry(QRect(240, 140, 81, 20));
        Degress = new QLabel(SmartPram);
        Degress->setObjectName(QString::fromUtf8("Degress"));
        Degress->setGeometry(QRect(410, 140, 57, 15));
        Sound_LCD = new QLCDNumber(SmartPram);
        Sound_LCD->setObjectName(QString::fromUtf8("Sound_LCD"));
        Sound_LCD->setGeometry(QRect(320, 180, 71, 31));
        Procent = new QLabel(SmartPram);
        Procent->setObjectName(QString::fromUtf8("Procent"));
        Procent->setGeometry(QRect(410, 190, 51, 20));
        Sound = new QLabel(SmartPram);
        Sound->setObjectName(QString::fromUtf8("Sound"));
        Sound->setGeometry(QRect(280, 190, 21, 16));
        Temp_Alarm = new QLabel(SmartPram);
        Temp_Alarm->setObjectName(QString::fromUtf8("Temp_Alarm"));
        Temp_Alarm->setGeometry(QRect(20, 170, 201, 16));
        Vugge_Ikon = new QLabel(SmartPram);
        Vugge_Ikon->setObjectName(QString::fromUtf8("Vugge_Ikon"));
        Vugge_Ikon->setGeometry(QRect(20, 10, 121, 16));
        Uro_Ikon = new QLabel(SmartPram);
        Uro_Ikon->setObjectName(QString::fromUtf8("Uro_Ikon"));
        Uro_Ikon->setGeometry(QRect(160, 10, 111, 16));
        Auto_Ikon = new QLabel(SmartPram);
        Auto_Ikon->setObjectName(QString::fromUtf8("Auto_Ikon"));
        Auto_Ikon->setGeometry(QRect(60, 120, 161, 16));
        Sound_Alarm = new QLabel(SmartPram);
        Sound_Alarm->setObjectName(QString::fromUtf8("Sound_Alarm"));
        Sound_Alarm->setGeometry(QRect(20, 200, 201, 16));
        tabWidget->addTab(SmartPram, QString());
        Indstillinger = new QWidget();
        Indstillinger->setObjectName(QString::fromUtf8("Indstillinger"));
        Save_settings = new QPushButton(Indstillinger);
        Save_settings->setObjectName(QString::fromUtf8("Save_settings"));
        Save_settings->setGeometry(QRect(230, 20, 101, 41));
        Lydmax_Slider = new QSlider(Indstillinger);
        Lydmax_Slider->setObjectName(QString::fromUtf8("Lydmax_Slider"));
        Lydmax_Slider->setGeometry(QRect(10, 190, 160, 16));
        Lydmax_Slider->setOrientation(Qt::Horizontal);
        Lydmax_Label = new QLabel(Indstillinger);
        Lydmax_Label->setObjectName(QString::fromUtf8("Lydmax_Label"));
        Lydmax_Label->setGeometry(QRect(20, 160, 57, 15));
        Vuggetid_Label = new QLabel(Indstillinger);
        Vuggetid_Label->setObjectName(QString::fromUtf8("Vuggetid_Label"));
        Vuggetid_Label->setGeometry(QRect(20, 30, 57, 15));
        Urotid_Label = new QLabel(Indstillinger);
        Urotid_Label->setObjectName(QString::fromUtf8("Urotid_Label"));
        Urotid_Label->setGeometry(QRect(20, 90, 57, 15));
        Vuggetid_Slider = new QSlider(Indstillinger);
        Vuggetid_Slider->setObjectName(QString::fromUtf8("Vuggetid_Slider"));
        Vuggetid_Slider->setGeometry(QRect(10, 60, 160, 16));
        Vuggetid_Slider->setPageStep(10);
        Vuggetid_Slider->setSliderPosition(0);
        Vuggetid_Slider->setTracking(true);
        Vuggetid_Slider->setOrientation(Qt::Horizontal);
        Urotid_Slider = new QSlider(Indstillinger);
        Urotid_Slider->setObjectName(QString::fromUtf8("Urotid_Slider"));
        Urotid_Slider->setGeometry(QRect(10, 120, 160, 16));
        Urotid_Slider->setOrientation(Qt::Horizontal);
        Urotid_vaerdi = new QLabel(Indstillinger);
        Urotid_vaerdi->setObjectName(QString::fromUtf8("Urotid_vaerdi"));
        Urotid_vaerdi->setGeometry(QRect(110, 90, 57, 15));
        lydmax_vaerdi = new QLabel(Indstillinger);
        lydmax_vaerdi->setObjectName(QString::fromUtf8("lydmax_vaerdi"));
        lydmax_vaerdi->setGeometry(QRect(110, 160, 57, 15));
        Tempmax_Slider = new QSlider(Indstillinger);
        Tempmax_Slider->setObjectName(QString::fromUtf8("Tempmax_Slider"));
        Tempmax_Slider->setGeometry(QRect(260, 110, 161, 16));
        Tempmax_Slider->setMaximumSize(QSize(1000000, 16777215));
        Tempmax_Slider->setMaximum(50);
        Tempmax_Slider->setOrientation(Qt::Horizontal);
        Tempmax_Label = new QLabel(Indstillinger);
        Tempmax_Label->setObjectName(QString::fromUtf8("Tempmax_Label"));
        Tempmax_Label->setGeometry(QRect(270, 80, 61, 16));
        Tempmin_Slider = new QSlider(Indstillinger);
        Tempmin_Slider->setObjectName(QString::fromUtf8("Tempmin_Slider"));
        Tempmin_Slider->setGeometry(QRect(260, 170, 160, 16));
        Tempmin_Slider->setMaximum(50);
        Tempmin_Slider->setSliderPosition(0);
        Tempmin_Slider->setOrientation(Qt::Horizontal);
        Tempmin_Label = new QLabel(Indstillinger);
        Tempmin_Label->setObjectName(QString::fromUtf8("Tempmin_Label"));
        Tempmin_Label->setGeometry(QRect(270, 140, 57, 15));
        Tempmax_vaerdi = new QLabel(Indstillinger);
        Tempmax_vaerdi->setObjectName(QString::fromUtf8("Tempmax_vaerdi"));
        Tempmax_vaerdi->setGeometry(QRect(360, 80, 57, 15));
        Tempmin_vaerdi = new QLabel(Indstillinger);
        Tempmin_vaerdi->setObjectName(QString::fromUtf8("Tempmin_vaerdi"));
        Tempmin_vaerdi->setGeometry(QRect(360, 140, 57, 15));
        Vuggetid_vaerdi = new QLabel(Indstillinger);
        Vuggetid_vaerdi->setObjectName(QString::fromUtf8("Vuggetid_vaerdi"));
        Vuggetid_vaerdi->setGeometry(QRect(120, 30, 57, 15));
        Button_cancel = new QPushButton(Indstillinger);
        Button_cancel->setObjectName(QString::fromUtf8("Button_cancel"));
        Button_cancel->setGeometry(QRect(350, 20, 101, 41));
        Button_default = new QPushButton(Indstillinger);
        Button_default->setObjectName(QString::fromUtf8("Button_default"));
        Button_default->setGeometry(QRect(300, 200, 91, 21));
        tabWidget->addTab(Indstillinger, QString());
        UiBoundary->setCentralWidget(centralWidget);

        retranslateUi(UiBoundary);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(UiBoundary);
    } // setupUi

    void retranslateUi(QMainWindow *UiBoundary)
    {
        UiBoundary->setWindowTitle(QApplication::translate("UiBoundary", "UiBoundary", 0, QApplication::UnicodeUTF8));
        Button_Vugge->setText(QApplication::translate("UiBoundary", "M Vugge", 0, QApplication::UnicodeUTF8));
        Button_Uro->setText(QApplication::translate("UiBoundary", "M Uro", 0, QApplication::UnicodeUTF8));
        Button_Automatisk->setText(QApplication::translate("UiBoundary", "Automatisk", 0, QApplication::UnicodeUTF8));
        Button_Indstillinger->setText(QApplication::translate("UiBoundary", "SystemIndstillinger", 0, QApplication::UnicodeUTF8));
        Temperatur->setText(QApplication::translate("UiBoundary", "Temperatur:", 0, QApplication::UnicodeUTF8));
        Degress->setText(QApplication::translate("UiBoundary", "grader", 0, QApplication::UnicodeUTF8));
        Procent->setText(QApplication::translate("UiBoundary", "%", 0, QApplication::UnicodeUTF8));
        Sound->setText(QApplication::translate("UiBoundary", "Lyd:", 0, QApplication::UnicodeUTF8));
        Temp_Alarm->setText(QApplication::translate("UiBoundary", "TEMP ALARM", 0, QApplication::UnicodeUTF8));
        Vugge_Ikon->setText(QApplication::translate("UiBoundary", "Vugge er ikke Aktiv", 0, QApplication::UnicodeUTF8));
        Uro_Ikon->setText(QApplication::translate("UiBoundary", "Uro er ikke Aktiv", 0, QApplication::UnicodeUTF8));
        Auto_Ikon->setText(QApplication::translate("UiBoundary", "Automatisk er ikke Aktiv", 0, QApplication::UnicodeUTF8));
        Sound_Alarm->setText(QApplication::translate("UiBoundary", "LYD ALARM", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(SmartPram), QApplication::translate("UiBoundary", "Smart Pram", 0, QApplication::UnicodeUTF8));
        Save_settings->setText(QApplication::translate("UiBoundary", "Gem", 0, QApplication::UnicodeUTF8));
        Lydmax_Label->setText(QApplication::translate("UiBoundary", "Lyd Max", 0, QApplication::UnicodeUTF8));
        Vuggetid_Label->setText(QApplication::translate("UiBoundary", "Vuggetid", 0, QApplication::UnicodeUTF8));
        Urotid_Label->setText(QApplication::translate("UiBoundary", "Urotid", 0, QApplication::UnicodeUTF8));
        Urotid_vaerdi->setText(QString());
        lydmax_vaerdi->setText(QString());
        Tempmax_Label->setText(QApplication::translate("UiBoundary", "Temp Max", 0, QApplication::UnicodeUTF8));
        Tempmin_Label->setText(QApplication::translate("UiBoundary", "Temp Min.", 0, QApplication::UnicodeUTF8));
        Tempmax_vaerdi->setText(QString());
        Tempmin_vaerdi->setText(QString());
        Vuggetid_vaerdi->setText(QString());
        Button_cancel->setText(QApplication::translate("UiBoundary", "Annuller", 0, QApplication::UnicodeUTF8));
        Button_default->setText(QApplication::translate("UiBoundary", "Default", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(Indstillinger), QApplication::translate("UiBoundary", "Indstillinger", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UiBoundary: public Ui_UiBoundary {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIBOUNDARY_H
