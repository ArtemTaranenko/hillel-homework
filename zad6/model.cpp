#include "model.h"
#include <cmath>

double roundToDecimals(double value)
{
    double factor = std::pow(10.0, 5);
    return std::round(value * factor) / factor;
}

Model::Model(double cel, double fahr, double kel, QObject* parent)
    :celsius(cel), fahrenheit(fahr), kelvin(kel), QObject{parent} {}

double Model::getCelsius()
{
    return this->celsius;
}

double Model::getFahrenheit()
{
    return this->fahrenheit;
}

double Model::getKelvin()
{
    return this->kelvin;
}

void Model::setCelsius(double cel_value)
{
    this->celsius = cel_value;
}

void Model::setFahrenheit(double fahr_value)
{
    this->fahrenheit = fahr_value;
}

void Model::setKelvin(double kel_value)
{
    this->kelvin = kel_value;
}


double Model::convertCelToFahr()
{
    return roundToDecimals(this->getCelsius() * 1.8 + 32);
}

double Model::convertCelToKel()
{
    return roundToDecimals(this->getCelsius() + 273.15);
}

double Model::convertFahrToCel()
{
    return roundToDecimals((this->getFahrenheit() - 32) / 1.8);
}

double Model::convertFahrToKel()
{
    return roundToDecimals(this->convertFahrToCel() + 273.15);
}

double Model::convertKelToCel()
{
    return roundToDecimals(this->getKelvin() - 273.15);
}

double Model::convertKelToFahr()
{
    return roundToDecimals(this->convertKelToCel() * 1.8 + 32);
}

bool Model::getCel_valid()
{
    return this->cel_valid;
}

bool Model::getFahr_valid()
{
    return this->fahr_valid;
}

bool Model::getKel_valid()
{
    return this->kel_valid;
}

void Model::setCel_valid(bool valid)
{
    this->cel_valid = valid;
    emit this->cel_validChanged(this->cel_valid);
}

void Model::setFahr_valid(bool valid)
{
    this->fahr_valid = valid;
    emit this->fahr_validChanged(this->fahr_valid);
}

void Model::setKel_valid(bool valid)
{
    this->kel_valid = valid;
    emit this->kel_validChanged(this->kel_valid);
}
