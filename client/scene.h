#ifndef SCENE_H
#define SCENE_H

#include "planet_render.h"

#include <Qt3DRender/qcamera.h>
#include <QWidget>
#include <QVector3D>
#include <Qt3DExtras/qt3dwindow.h>

class Scene
{
private:
    PlanetRender *m_modifier;

public:
    Scene();
    Qt3DCore::QEntity      *rootEntity;
    Qt3DExtras::Qt3DWindow *view;
    QWidget                *container;
    PlanetRender           *getModifier() {return m_modifier;}
};
#endif // SCENE_H
