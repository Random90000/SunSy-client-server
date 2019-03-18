#include "client_entity.h"

Client_entity::Client_entity(Qt3DCore::QEntity *rootEntity)
    : clientMesh(new Qt3DExtras::QSphereMesh())
    , clientEntityTransform(new Qt3DCore::QTransform())
    , clientEntityMaterial(new Qt3DExtras::QPhongMaterial())
    , clientEntity(new Qt3DCore::QEntity(rootEntity))
    , position(new QJsonObject({{"x",0.},{"y",0.},{"z",0.}}))
{
    clientEntityMaterial->setDiffuse(QColor(QRgb(0xbeb32b)));
    clientMesh->setRadius(1.);

    clientEntity->addComponent(clientEntityMaterial);
    clientEntity->addComponent(clientMesh);
    clientEntity->addComponent(clientEntityTransform);
}

Client_entity::~Client_entity()
{
    delete clientMesh;
    delete clientEntityTransform;
    delete clientEntityMaterial;
    delete clientEntity;
}

void Client_entity::moveClientEntity()
{
    float x = (float)position->value("x").toDouble();
    float y = (float)position->value("y").toDouble();
    float z = (float)position->value("z").toDouble();
    if (x != 0 || y != 0 || z != 0)
    {
        clientEntityTransform->setTranslation(QVector3D{x,y,z});
    }
}
