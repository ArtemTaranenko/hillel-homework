#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class Model: public QObject
{
    Q_OBJECT
    Q_PROPERTY(double celsius READ getCelsius WRITE setCelsius NOTIFY celsiusChanged)
    Q_PROPERTY(double fahrenheit READ getFahrenheit WRITE setFahrenheit NOTIFY fahrenheitChanged)
    Q_PROPERTY(double kelvin READ getKelvin WRITE setKelvin NOTIFY kelvinChanged)
    Q_PROPERTY(bool cel_valid READ getCel_valid WRITE setCel_valid NOTIFY cel_validChanged)
    Q_PROPERTY(bool fahr_valid READ getFahr_valid WRITE setFahr_valid NOTIFY fahr_validChanged)
    Q_PROPERTY(bool kel_valid READ getKel_valid WRITE setKel_valid NOTIFY kel_validChanged)
    public:
    explicit Model (double cel, double fahr, double kel, QObject* parent = nullptr);

    double getCelsius();
    double getFahrenheit();
    double getKelvin();

    void setCelsius(double cel_value);
    void setFahrenheit(double fahr_value);
    void setKelvin(double kel_value);

    double convertCelToFahr();
    double convertCelToKel();
    double convertFahrToCel();
    double convertFahrToKel();
    double convertKelToCel();
    double convertKelToFahr();

    bool getCel_valid();
    bool getFahr_valid();
    bool getKel_valid();

    void setCel_valid(bool valid);
    void setFahr_valid(bool valid);
    void setKel_valid(bool valid);

    signals:
    void celsiusChanged (double cel_value);
    void fahrenheitChanged (double fahr_value);
    void kelvinChanged (double kel_value);
    void cel_validChanged(bool valid);
    void fahr_validChanged(bool valid);
    void kel_validChanged(bool valid);

    private:
        double celsius;
        double fahrenheit;
        double kelvin;
        bool cel_valid;
        bool fahr_valid;
        bool kel_valid;
};

#endif // MODEL_H
