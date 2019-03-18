#ifndef PLANET_DATA_H
#define PLANET_DATA_H

#include <QString>
#include <vector>


enum PlanetId {
    SUN=0,
    MERCURY,
    VENUS,
    EARTH,
    MARS,
    JUPITER,
    SATURN,
    URANUS,
    NEPTUNE,
    MOON
};

struct PlanetParams {
    QString name;
    double  radius, // planet radius
            tilt, // planet axis angle
            a, // 2* semi-major axis, or mean distance from Sun
            period, // sidereal rotation period
            x, y, z;
    PlanetId centerOfOrbit; // the planet in the center of the orbit
    // (orbital elements based on http://www.stjarnhimlen.se/comp/ppcomp.html)
};

class PlanetData :public std::vector<PlanetParams>
{
public:
    PlanetData();
};

#endif // PLANET_DATA_H
