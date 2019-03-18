#include "planet_data.h"

PlanetData::PlanetData()
{
        push_back(PlanetParams{
            "sun",
            /*radius:*/ 694.439, /*tilt:*/ 63.87, /*a:*/ 0,/*period:*/ 25.05,
            /*x:*/ 0, /*y:*/ 0, /*z:*/ 0,
            /*centerOfOrbit:*/ SUN });

        push_back(PlanetParams{
            "mercury",
            /*radius:*/ 2.433722, /*tilt:*/ 0.04, /*a:*/ 0.387098, /*period:*/ 58.646,
            /*x:*/ 0, /*y:*/ 0, /*z:*/ 0,
            /*centerOfOrbit:*/ SUN
        });

        push_back(PlanetParams{
            "venus",
            /*radius:*/ 6.046079, /*tilt:*/ 177.36, /*a:*/ 0.723330, /*period:*/ 243.0185,
            /*x:*/ 0, /*y:*/ 0, /*z:*/ 0,
            /*centerOfOrbit:*/ SUN
        });

        push_back(PlanetParams{
            "earth",
            /*radius:*/ 6.371, /*tilt:*/ 25.44, /*a:*/ 1, /*period:*/ 0.997,
            /*x:*/ 0, /*y:*/ 0, /*z:*/ 0,
            /*centerOfOrbit:*/ SUN
        });

        push_back(PlanetParams{
            "mars",
            /*radius:*/ 3.389372, /*tilt:*/ 25.19, /*a:*/ 1.523688, /*period:*/ 1.025957,
            /*x:*/ 0, /*y:*/ 0, /*z:*/ 0,
            /*centerOfOrbit:*/ SUN
        });

        push_back(PlanetParams{
            "jupiter",
            /*radius:*/ 71.41254, /*tilt:*/ 3.13, /*a:*/ 5.20256, /*period:*/ 0.4135,
            /*x:*/ 0, /*y:*/ 0, /*z:*/ 0,
            /*centerOfOrbit:*/ SUN
        });

        push_back(PlanetParams{
            "saturn",
            /*radius:*/ 60.19958, /*tilt:*/ 26.73, /*a:*/ 9.55475, /*period:*/ 0.4395,
            /*x:*/ 0, /*y:*/ 0, /*z:*/ 0,
            /*centerOfOrbit:*/ SUN
        });

        push_back(PlanetParams{
            "uranus",
            /*radius:*/ 25.5286, /*tilt:*/ 97.77, /*a:*/ 19.18171, /*period:*/ 0.71833,
            /*x:*/ 0, /*y:*/ 0, /*z:*/ 0,
            /*centerOfOrbit:*/ SUN
        });

        push_back(PlanetParams{
            "neptune",
            /*radius:*/ 24.73859, /*tilt:*/ 28.32, /*a:*/ 30.05826, /*period:*/ 0.6713,
            /*x:*/ 0, /*y:*/ 0, /*z:*/ 0,
            /*centerOfOrbit:*/ SUN
        });

        push_back(PlanetParams{
            "moon",
            /*radius:*/ 1.5424, /*tilt:*/ 28.32, /*a:*/ 0.273, /*period:*/ 27.321582,
            /*x:*/ 0, /*y:*/ 0, /*z:*/ 0,
            /*centerOfOrbit:*/ EARTH
        });

    }

