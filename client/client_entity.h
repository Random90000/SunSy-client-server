#ifndef CLIENT_ENTITY_H
#define CLIENT_ENTITY_H

#include <QObject>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/qspheremesh.h>
#include <Qt3DExtras/qphongmaterial.h>

#include <QVector>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

class Client_entity
{
    public:
        Client_entity(Qt3DCore::QEntity *rootEntity);
        ~Client_entity();
        Qt3DExtras::QSphereMesh    *clientMesh;
        Qt3DCore::QTransform       *clientEntityTransform;
        Qt3DExtras::QPhongMaterial *clientEntityMaterial;
        Qt3DCore::QEntity          *clientEntity;
        QJsonObject                *position;

        void moveClientEntity();

};

#endif // CLIENT_ENTITY_H
