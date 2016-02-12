#ifndef UiBoundary_H
#define UiBoundary_H

#include <QMainWindow>
#include "Filer/UIController.hpp"
#include <QTimer>
#include <iostream>

namespace Ui {
class UiBoundary;
}

class UiBoundary : public QMainWindow
{
    Q_OBJECT

public:
    explicit UiBoundary(UIController* _objUIController, QWidget *parent = 0);
    ~UiBoundary();

    void set_settings_label();

public slots:
    void update_settings();

    void get_settings();

private slots:
    void on_Button_Vugge_clicked();

    void on_Save_settings_clicked();

    void on_Button_Automatisk_clicked();

    void on_Button_Uro_clicked();

    void on_Button_Indstillinger_clicked();

    void on_Tempmax_Slider_sliderMoved(int position);

    void on_Tempmin_Slider_sliderMoved(int position);

    void on_Lydmax_Slider_sliderMoved(int position);

    void on_Urotid_Slider_sliderMoved(int position);

    void on_Vuggetid_Slider_sliderMoved(int position);

    void on_Button_cancel_clicked();

    void on_Button_default_clicked();

private:
    Ui::UiBoundary *ui;

    signed char temp_in_;
    signed char sound_in_;

    int tempMin_;
    int tempMax_;
    int mobileTime_;
    int cradleTime_;
    int soundMax_;

    UIController* objUIController_;
};

#endif // UiBoundary_H
