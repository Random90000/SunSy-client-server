#ifndef SERVER_H
#define SERVER_H

#include "client_entity.h"
#include "scene.h"

#include <QDebug>
#include <QTcpSocket>
#include <QTcpServer>
#include <QByteArray>
#include <QVector>
#include <QDataStream>
#include <QMap>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(Scene *scene = nullptr);
    Scene                      *scene;
    QMap<int, Client_entity *> *clients;
    QJsonArray                 *planets_position;

public slots:
    void incomingConnection(int socketDescriptor);
    void exchangeData();
    void deleteClient();

signals:
    void readyExchange();
};

#endif // SERVER_H
