#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "model.h"

class Controller: public QObject
{
    Q_OBJECT
    public:
    explicit Controller(Model* model, QObject* parent = nullptr);

    Q_INVOKABLE void setCel (QString cel_value);
    Q_INVOKABLE void setFahr(QString fahr_value);
    Q_INVOKABLE void setKel(QString kel_value);
    private:
        Model* model;
};

#endif // CONTROLLER_H
