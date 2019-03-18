#ifndef SCENE_H
#define SCENE_H

#include "planet_render.h"

#include <QWidget>
#include <Qt3DCore/qentity.h>

class Scene
{
private:
    PlanetRender *m_modifier;

public:
    Scene();
    Qt3DCore::QEntity *rootEntity;
    QWidget           *container;
    PlanetRender      *getModifier() {return m_modifier;}
};
#endif // SCENE_H
