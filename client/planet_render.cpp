#include "planet_data.h"
#include "planet_render.h"

#include <QtCore/QDebug>
#include <QPhongAlphaMaterial>
#include <QDiffuseMapMaterial>
#include <QTextureImage>
#include <Qt3DExtras/qtorusmesh.h>

static float smoothRadius(double r) {
    return std::min(1.,(log(1+4.*r)-1.)/8.);
}

PlanetRender::PlanetRender(Qt3DCore::QEntity *rootEntity)
    : m_rootEntity(rootEntity)
{
    //Planet data
    PlanetData planets;

    // Sphere shape data
    Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh();
    sphereMesh->setRings(64);
    sphereMesh->setSlices(64);
    sphereMesh->setRadius(1);

    // Spherical Planets and star(s)
    for (int i=0; i < (int)planets.size(); ++i)
        if (planets[i].centerOfOrbit==SUN) {
            const QString& planetName = planets[i].name;
            Qt3DExtras::QDiffuseMapMaterial *normalDiffuseSpecularMapMaterial = new Qt3DExtras::QDiffuseMapMaterial();
            normalDiffuseSpecularMapMaterial->setTextureScale(1.f);
            normalDiffuseSpecularMapMaterial->setShininess(20.0f);
            if (i == SUN)
                normalDiffuseSpecularMapMaterial->setAmbient(QColor::fromRgbF(1.f, 1.f, 0.85f, 1.0f));
            Qt3DRender::QTextureImage *diffuseImage = new Qt3DRender::QTextureImage();
            diffuseImage->setSource(QUrl(QString("qrc:/images/images/")+planetName+"map2k.jpg"));
            normalDiffuseSpecularMapMaterial->diffuse()->addTextureImage(diffuseImage);

            // Sphere mesh transform
            m_planetStarTransform.push_back(new Qt3DCore::QTransform());

            //m_planetStarTransform[i]->setScale(i? 0.55f : 0.3f);
            m_planetStarTransform[i]->setScale(smoothRadius(planets[i].radius));

            Qt3DCore::QEntity *planet = new Qt3DCore::QEntity(m_rootEntity);
            planet->addComponent(sphereMesh);
            planet->addComponent(normalDiffuseSpecularMapMaterial);
            planet->addComponent(m_planetStarTransform[i]);
            m_planetStarEntities.push_back(planet);
        }
}

void PlanetRender::addOrbit(float radius) {
    Qt3DExtras::QTorusMesh *torusMesh = new Qt3DExtras::QTorusMesh();
    torusMesh->setMinorRadius(0.02f);
    torusMesh->setRings(200);
    torusMesh->setRadius(radius);

    Qt3DExtras::QPhongAlphaMaterial *orbitMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    orbitMaterial->setShininess(200.0f);
    orbitMaterial->setAmbient(QColor::fromRgbF(1.0f,1.0f,.3f,0.1f));

    Qt3DCore:: QEntity *orbitEntity = new Qt3DCore::QEntity(m_rootEntity);
    orbitEntity->addComponent(torusMesh);
    orbitEntity->addComponent(orbitMaterial);
    //No transform is needed
}

void  PlanetRender::movePlanetStar(int idx, double x, double y, double z, float roll) {
    PlanetData planets;
    m_planetStarTransform[idx]->setRotation(QQuaternion::fromEulerAngles(90+planets[idx].tilt,0,0) * QQuaternion::fromEulerAngles(0,roll,0));
    m_planetStarTransform[idx]->setTranslation(QVector3D(x, y, z));
}

void PlanetRender::updateStarRadius(int idx, float radius) {
    m_planetStarTransform[idx]->setScale(radius);
}

void PlanetRender::updateStarAmbient(int idx, QColor color) {
    m_planetStarMaterials[idx]->setAmbient(color);
}

void PlanetRender::showPlanet(int idx, bool visible) {
    m_planetStarEntities[idx]->setEnabled(visible);
}
