#ifndef CLIENT_H
#define CLIENT_H

#include "client_entity.h"
#include "scene.h"

#include <QTcpSocket>
#include <QDataStream>
#include <QByteArray>
#include <QVector>
#include <QVector3D>
#include <QMap>

class Client : public QObject
{
    Q_OBJECT

public:
    Client(Scene *scene = nullptr);
    Scene                      *scene;
    QVector<double>            *planet_data;
    QMap<int, Client_entity *> *other_clients_data;
    QTcpSocket                 *socket = nullptr;
    int                         clientNumber;

public slots:
    void getData();
    void sendData();

};

#endif // CLIENT_H
