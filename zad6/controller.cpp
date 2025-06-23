#include "controller.h"

Controller::Controller (Model *model, QObject *parent): model(model), QObject{parent} {}

double Controller::getCelsius()
{
    return this->model->getCelsius();
}
double Controller::getFahrenheit()
{
    return this->model->getFahrenheit();
}
double Controller::getKelvin()
{
    return this->model->getKelvin();
}

void Controller::setCel(QString cel_value)
{
    bool ok = false;
    double cel = cel_value.toDouble(&ok);
    if (ok){
    this->model->setCelsius(cel);
    this->model->setFahrenheit(this->model->convertCelToFahr());
    this->model->setKelvin(this->model->convertCelToKel());
    }
    this->model->setCel_valid(ok);
}

void Controller::setFahr(QString fahr_value)
{
    bool ok = false;
    double fahr = fahr_value.toDouble(&ok);
    if (ok){
        this->model->setFahrenheit(fahr);
        this->model->setCelsius(this->model->convertFahrToCel());
        this->model->setKelvin(this->model->convertFahrToKel());
    }
    this->model->setFahr_valid(ok);
}

void Controller::setKel(QString kel_value)
{
    bool ok = false;
    double kel = kel_value.toDouble(&ok);
    if (ok){
        this->model->setKelvin(kel);
        this->model->setCelsius(this->model->convertKelToCel());
        this->model->setFahrenheit(this->model->convertKelToFahr());
    }
    this->model->setKel_valid(ok);
}




