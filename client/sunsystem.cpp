#include "sunsystem.h"
#include "planet_data.h"

#include <QtWidgets>

static float smoothOrbitRadius(float astroUnits) {
    return 1. + log(astroUnits/1.4  + 1.)*4.;
}

static PlanetData planets;

SunSystem::SunSystem(QWidget *parent)
    : QWidget(parent)
    , scene(new Scene())
    , client(new Client(scene))
    , planets_position(new QVector<double>(0))
    , elapsed()
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(scene->container);
    setLayout(mainLayout);

    for (const auto &p : planets)
        if (&p != &planets[0] && p.centerOfOrbit ==  SUN)
            scene->getModifier()->addOrbit(smoothOrbitRadius(p.a));

    setWindowTitle("SunSyClient " + QString::number(client->clientNumber));
    startTimer(100); //Update
}

void SunSystem::timerEvent(QTimerEvent*)
{
    if (client->planet_data->size() != 0)
    {
        for (int i = 1; i < (int)planets.size(); ++i)
        {
            if (planets[i].centerOfOrbit == SUN)
            {
                QVector<double> *c_pd = client->planet_data;
                scene->getModifier()->movePlanetStar(i, (*c_pd)[3*i - 3], (*c_pd)[3*i - 2], 0, (*c_pd)[3*i - 1]);
            }
        }
        client->planet_data->clear();
    }

    client->sendData();
}
