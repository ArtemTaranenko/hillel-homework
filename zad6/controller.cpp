#include "controller.h"

Controller::Controller (Model *model, QObject *parent): model(model), QObject{parent} {}


void Controller::setCel(QString cel_value)
{
    bool ok = false;
    double cel = cel_value.toDouble(&ok);

    if (ok && cel >= -273.15) {
        this->model->setCelsius(cel);
        this->model->setFahrenheit(this->model->convertCelToFahr());
        this->model->setKelvin(this->model->convertCelToKel());
        this->model->setCel_valid(ok);
        this->model->setFahr_valid(ok);
        this->model->setKel_valid(ok);
    } else {
        this->model->setCel_valid(false);
    }
}

void Controller::setFahr(QString fahr_value)
{
    bool ok = false;
    double fahr = fahr_value.toDouble(&ok);

    if (ok) {
        if (fahr >= -459.67) {
            this->model->setFahrenheit(fahr);
            this->model->setCelsius(this->model->convertFahrToCel());
            this->model->setKelvin(this->model->convertFahrToKel());
            this->model->setCel_valid(ok);
            this->model->setFahr_valid(ok);
            this->model->setKel_valid(ok);
        }
        else {
            this->model->setFahr_valid(false);
        }
    } else {
        this->model->setFahr_valid(false);
    }
}

void Controller::setKel(QString kel_value)
{
    bool ok = false;
    double kel = kel_value.toDouble(&ok);

    if (ok && kel >= 0.0) {
        this->model->setKelvin(kel);
        this->model->setCelsius(this->model->convertKelToCel());
        this->model->setFahrenheit(this->model->convertKelToFahr());
        this->model->setCel_valid(ok);
        this->model->setFahr_valid(ok);
        this->model->setKel_valid(ok);
    } else {
        this->model->setKel_valid(false);
    }
}





