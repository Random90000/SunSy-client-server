#include "sunsystem.h"
#include "planet_data.h"

#include <QtWidgets>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>


static float smoothOrbitRadius(float astroUnits) {
    return 1. + log(astroUnits/1.4  + 1.)*4.;
}

static PlanetData planets;

SunSystem::SunSystem(QWidget *parent)
    : QWidget(parent)
    , scene(new Scene())
    , server(new Server(scene))
    , mainLayout(new QGridLayout)
    , elapsed()
{
    mainLayout->addWidget(scene->container);
    setLayout(mainLayout);

    for (const auto &p : planets)
        if (&p != &planets[0] && p.centerOfOrbit ==  SUN)
            scene->getModifier()->addOrbit(smoothOrbitRadius(p.a));

    setWindowTitle(tr("Sun System Server"));
    startTimer(100); //Update
}

void SunSystem::timerEvent(QTimerEvent*)
{
    double new_x;
    double new_y;
    double new_roll;
    double r;
    double t;

    for (int i = 1; i < (int)planets.size(); ++i)
        if (planets[i].centerOfOrbit == SUN)
        {
            r = smoothOrbitRadius(planets[i].a);
            // Kepler law: t**2 = r**3
            // Let's apply Kepler low to smoothed radix :-)
            t = sqrt(r*r*r);
            new_x    = r*sin(0.2*elapsed/t);
            new_y    = r*cos(0.2*elapsed/t);
            new_roll = 12.*elapsed / planets[i].period;
            scene->getModifier()->movePlanetStar(i, new_x, new_y, 0., new_roll);
            (*server->planets_position)[3*i - 3] = new_x;
            (*server->planets_position)[3*i - 2] = new_y;
            (*server->planets_position)[3*i - 1] = new_roll;
        }
    emit server->readyExchange();
    elapsed++;
}
