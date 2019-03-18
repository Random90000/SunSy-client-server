#ifndef SUNSYSTEM_H
#define SUNSYSTEM_H

#include "client.h"

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QCheckBox>
#include <QGridLayout>
#include <QVector>

class SunSystem : public QWidget
{
    Q_OBJECT

private:
        Scene           *scene;
        Client          *client;
        QVector<double> *planets_position;
        time_t elapsed;

public:
    explicit SunSystem(QWidget *parent = nullptr);

protected:
        void timerEvent(QTimerEvent* event);
};

#endif // SUNSYSTEM_H
