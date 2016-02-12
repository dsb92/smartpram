#include "uiboundary.h"
#include "ui_uiboundary.h"

UiBoundary::UiBoundary(UIController* _objUIController, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UiBoundary)
{
    ui->setupUi(this);


    QTimer* timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(update_settings()));
    timer1->start(1000);

    temp_in_ = 0; // Fra UiControl
    sound_in_ = 0; // Fra UiControl

     tempMin_ = 0; // Variable der bliver sat i System Indstillinger via. sliders
     tempMax_ = 0;  // Variable der bliver sat i System Indstillinger via. sliders
     soundMax_ = 0;  // Variable der bliver sat i System Indstillinger via. sliders
     mobileTime_ = 0;  // Variable der bliver sat i System Indstillinger via. sliders
     cradleTime_ = 0;  // Variable der bliver sat i System Indstillinger via. sliders
     objUIController_ = _objUIController; // Object af UIControl, association til klassen.
}

UiBoundary::~UiBoundary()
{
    delete ui;
}


void UiBoundary::on_Button_Vugge_clicked() // Knap til at starte Manuel Vugning
{
    QPalette* palette2 = new QPalette;

    if(objUIController_->automaticUIbutton_ == false)
    {
        if(objUIController_->cradleOnManUIbutton_ == false) // Hvis cradle_ er nul skal den køre startCradle();
        {
            objUIController_->cradleOnManUIbutton_ = true;
            ui->Vugge_Ikon->setText("Vugge er Aktiv");
            palette2->setColor(QPalette::Button, Qt::green); // Sætter baggrunds farven på knappen til grøn
            ui->Button_Vugge->setPalette(*palette2);
            objUIController_->startCradle();
        }
        else // Ellers skal den køre stopCradle();
        {
            ui->Vugge_Ikon->setText("Vugge er ikke Aktiv");
            palette2->setColor(QPalette::Button, Qt::lightGray); // Sætter baggrunds farven på knappen til lysgrå
            ui->Button_Vugge->setPalette(*palette2);
            objUIController_->stopCradle();
            objUIController_->cradleOnManUIbutton_ = false;
        }
    }
    else
    {
        objUIController_->cradleOnManUIbutton_ = false;
        ui->Vugge_Ikon->setText("Vugge er ikke Aktiv");
        palette2->setColor(QPalette::Button, Qt::gray); // Sætter baggrunds farven på knappen til grå
        ui->Button_Vugge->setPalette(*palette2);
    }
}

void UiBoundary::on_Save_settings_clicked()
{
    // Gem indstillinger. Kald en UIController funktion
    ui->tabWidget->setCurrentIndex(0);
    objUIController_->setSaveSettings(cradleTime_, 255, mobileTime_, 255, tempMin_, tempMax_, soundMax_);
}

void UiBoundary::on_Button_Automatisk_clicked() // Knap til at starte Automatisk styring
{
    QPalette* palette3 = new QPalette;

    if(objUIController_->mobileOnManUIbutton_  == false && objUIController_->cradleOnManUIbutton_ == false)
    {
        if(objUIController_->automaticUIbutton_ == false) // Hvis auto_ er nul skal den køre startAutomatic();
        {
            objUIController_->automaticUIbutton_ = true;
            ui->Auto_Ikon->setText("Automatisk er Aktiv");
            palette3->setColor(QPalette::Button, Qt::green); // Sætter baggrunds farven på knappen til grøn
            ui->Button_Automatisk->setPalette(*palette3);
            objUIController_->startAutomatic();
        }
        else // Ellers skal den køre stopAutomatic();
        {
            ui->Auto_Ikon->setText("Automatisk er ikke Aktiv");
            palette3->setColor(QPalette::Button, Qt::lightGray); // Sætter baggrunds farven på knappen til lysgrå
            ui->Button_Automatisk->setPalette(*palette3);
            objUIController_->stopAutomatic();
            objUIController_->automaticUIbutton_ = false;
        }
    }
    else
    {
        objUIController_->automaticUIbutton_ = false;
        ui->Auto_Ikon->setText("Automatisk er ikke Aktiv");
        palette3->setColor(QPalette::Button, Qt::gray); // Sætter baggrunds farven på knappen til grå
        ui->Button_Automatisk->setPalette(*palette3);
    }
}

void UiBoundary::on_Button_Uro_clicked() // Knap til at starte Uro Manuel
{
    QPalette* palette1 = new QPalette;

    if(objUIController_->automaticUIbutton_ == false)
    {
        if(objUIController_->mobileOnManUIbutton_ == false) // Hvis mobile_ er nul skal den køre startMobile();
        {
            objUIController_->mobileOnManUIbutton_ = true;
            ui->Uro_Ikon->setText("Uro er Aktiv");
            palette1->setColor(QPalette::Button, Qt::green); // Sætter baggrunds farven på knappen til grøn
            ui->Button_Uro->setPalette(*palette1);
            objUIController_->startMobile();
        }
        else // Ellers skal den køre stopMobile();
        {
            ui->Uro_Ikon->setText("Uro er ikke Aktiv");
            palette1->setColor(QPalette::Button, Qt::lightGray); // Sætter baggrunds farven på knappen til lysgrå
            ui->Button_Uro->setPalette(*palette1);
            objUIController_->stopMobile();
            objUIController_->mobileOnManUIbutton_ = false;
        }
     }
    else
    {
        objUIController_->mobileOnManUIbutton_ = false;
        ui->Uro_Ikon->setText("Uro er ikke Aktiv");
        palette1->setColor(QPalette::Button, Qt::gray); // Sætter baggrunds farven på knappen til grå
        ui->Button_Uro->setPalette(*palette1);
    }
}

void UiBoundary::on_Button_Indstillinger_clicked()
{
    objUIController_->getCurrentSettings();
    cradleTime_ = objUIController_->cradleTime_;
    mobileTime_ = objUIController_->mobileTime_;
    soundMax_ = objUIController_->maxSound_;
    tempMin_ = objUIController_->minTemperature_;
    tempMax_ = objUIController_->maxTemperature_;
    set_settings_label();
    ui->Lydmax_Slider->setSliderPosition(soundMax_);
    ui->Tempmax_Slider->setSliderPosition(tempMax_);
    ui->Tempmin_Slider->setSliderPosition(tempMin_);
    ui->Urotid_Slider->setSliderPosition(mobileTime_);
    ui->Vuggetid_Slider->setSliderPosition(cradleTime_);
    QTimer::singleShot(100, this, SLOT(get_settings()));
}

void UiBoundary::on_Tempmax_Slider_sliderMoved(int position)
{
    tempMax_ = position;
    ui->Tempmax_vaerdi->setNum(tempMax_);
}

void UiBoundary::on_Tempmin_Slider_sliderMoved(int position)
{
    tempMin_ = position;
    ui->Tempmin_vaerdi->setNum(tempMin_);
}

void UiBoundary::on_Lydmax_Slider_sliderMoved(int position)
{
    soundMax_ = position;
    ui->lydmax_vaerdi->setNum(soundMax_);
}

void UiBoundary::on_Urotid_Slider_sliderMoved(int position)
{
    mobileTime_ = position;
    ui->Urotid_vaerdi->setNum(mobileTime_);
}


void UiBoundary::on_Vuggetid_Slider_sliderMoved(int position)
{
    cradleTime_ = position;
    ui->Vuggetid_vaerdi->setNum(cradleTime_);
}

void UiBoundary::update_settings()
{
    temp_in_ = objUIController_->temperatur_;
    sound_in_ = objUIController_->sound_;
    ui->Temp_LCD->display(temp_in_);
    ui->Sound_LCD->display(sound_in_);

    if(temp_in_ >= tempMax_)
        ui->Temp_Alarm->setText("TEMPERATUREN ER FOR HOEJ");
    else
         ui->Temp_Alarm->setText("TEMPERATUREN ER OK");

    if(sound_in_ >= soundMax_)
        ui->Sound_Alarm->setText("LYDEN ER FOR HOEJ");

    else
        ui->Sound_Alarm->setText("LYDEN ER OK");

    if(temp_in_ <= tempMin_)
        ui->Temp_Alarm->setText("TEMPERATUREN ER FOR LAV");
    else
        ui->Temp_Alarm->setText("TEMPERATUREN ER OK");

    if(objUIController_->cradleOnManUIbutton_ == false)
    {
        QPalette* palette4 = new QPalette;
        ui->Vugge_Ikon->setText("Vugge er ikke Aktiv");
        palette4->setColor(QPalette::Button, Qt::gray); // Sætter baggrunds farven på knappen til grå
        ui->Button_Vugge->setPalette(*palette4);
    }
    else
    {

    }
    if(objUIController_->mobileOnManUIbutton_ == false)
    {
        QPalette* palette5 = new QPalette;
        ui->Uro_Ikon->setText("Uro er ikke Aktiv");
        palette5->setColor(QPalette::Button, Qt::gray);
        ui->Button_Uro->setPalette(*palette5);
    }
    else
    {

    }
}

void UiBoundary::get_settings()
{
    ui->tabWidget->setCurrentIndex(1); // For at skifte tab
}

void UiBoundary::set_settings_label()
{
    ui->Vuggetid_vaerdi->setNum(cradleTime_);
    ui->Urotid_vaerdi->setNum(mobileTime_);
    ui->lydmax_vaerdi->setNum(soundMax_);
    ui->Tempmax_vaerdi->setNum(tempMax_);
    ui->Tempmin_vaerdi->setNum(tempMin_);
}

void UiBoundary::on_Button_cancel_clicked()
{
    ui->tabWidget->setCurrentIndex(0);  // Går tilbage til HovedMenu
}


void UiBoundary::on_Button_default_clicked()
{
    objUIController_->setDefaultSettings();
    ui->tabWidget->setCurrentIndex(0);
}

