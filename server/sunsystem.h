#ifndef SUNSYSTEM_H
#define SUNSYSTEM_H

#include "scene.h"
#include "server.h"

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
        Server          *server;
        QGridLayout     *mainLayout;
        time_t elapsed;

public:
    explicit SunSystem(QWidget *parent = nullptr);

protected:
        void timerEvent(QTimerEvent* event);

};

#endif // SUNSYSTEM_H
