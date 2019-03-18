#include "scene.h"

#include <QGuiApplication>

#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtGui/QScreen>

#include <Qt3DInput/QInputAspect>

#include <Qt3DExtras/qtorusmesh.h>
#include <Qt3DExtras/qplanemesh.h>

#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qpointlight.h>
#include <QPhongMaterial>
#include <QDiffuseMapMaterial>

#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>

#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DExtras/qforwardrenderer.h>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>

Scene::Scene()
    : rootEntity(new Qt3DCore::QEntity())
{
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x000000)));
    container = QWidget::createWindowContainer(view);
    QSize screenSize = view->screen()->size();
    container->setMinimumSize(QSize(1000, 500));
    container->setMaximumSize(screenSize);

    Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
    view->registerAspect(input);

    // Camera
    Qt3DRender::QCamera *cameraEntity = view->camera();

    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1.);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);

    Qt3DCore::QEntity *sunLightEntity = new Qt3DCore::QEntity(rootEntity);
    light = new Qt3DRender::QPointLight(sunLightEntity);
    light->setColor("white");
    light->setIntensity(1.16);
    sunLightEntity->addComponent(light);
    lightTransform = new Qt3DCore::QTransform(sunLightEntity);
    //lightTransform->setTranslation(cameraEntity->position());
    sunLightEntity->addComponent(lightTransform);

    // For camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
    camController->setCamera(cameraEntity);

    //Star sky
    Qt3DExtras::QPlaneMesh *skyMesh = new Qt3DExtras::QPlaneMesh();

    Qt3DExtras::QDiffuseMapMaterial *skyMaterial = new Qt3DExtras::QDiffuseMapMaterial();
    skyMaterial->setTextureScale(1.f);
    skyMaterial->setShininess(0.0f);
    skyMaterial->setAmbient(QColor::fromRgbF(.0f,.7f,.8f,1.f));
    Qt3DRender::QTextureImage *diffuseImage = new Qt3DRender::QTextureImage();
    diffuseImage->setSource(QUrl(QStringLiteral("qrc:/images/images/galaxy_starfield.jpg")));
    skyMaterial->diffuse()->addTextureImage (diffuseImage);

    Qt3DCore:: QEntity *skyEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DCore::QTransform *skyTransform = new Qt3DCore::QTransform();;
    skyTransform -> setScale(160.);
    skyTransform -> setRotationX(90);
    skyTransform -> setTranslation(QVector3D(0.,0.,-20.0));

    skyEntity->addComponent(skyMesh);
    skyEntity->addComponent(skyMaterial);
    skyEntity->addComponent(skyTransform);

    // Scene modifier
    m_modifier = new PlanetRender(rootEntity);

    // Set root object of the scene
    view->setRootEntity(rootEntity);

}
