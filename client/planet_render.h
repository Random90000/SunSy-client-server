#ifndef PLANET_RENDER_H
#define PLANET_RENDER_H

#include <QObject>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QDiffuseMapMaterial>


class PlanetRender
{
    private:
        Qt3DCore::QEntity *m_rootEntity;
        Qt3DExtras::QSphereMesh *m_sphereMesh;
        std::vector<Qt3DCore::QEntity*> m_planetStarEntities;
        std::vector<Qt3DCore::QTransform *> m_planetStarTransform;
        std::vector<Qt3DExtras::QDiffuseMapMaterial *> m_planetStarMaterials;
    public:
        PlanetRender(Qt3DCore::QEntity * rootEntity);
        ~PlanetRender();
        void addOrbit(float radius);
        void movePlanetStar(int idx, double x, double y, double z, float roll);
        void updateStarRadius(int idx, float radius);
        void updateStarAmbient(int idx, QColor color);
        void showPlanet(int idx, bool visible = true);
        void hidePlanet(int idx) {showPlanet(idx, false);}
};

#endif // PLANET_RENDER_H
