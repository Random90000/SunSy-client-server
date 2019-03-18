#include "client.h"

#include <QtNetwork>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

Client::Client(Scene *scene)
    : scene(scene)
    , planet_data(new QVector<double>(0))
    , other_clients_data(new QMap<int, Client_entity *>)
    , socket(new QTcpSocket(this))
{
    qDebug() << "Client: created";

    socket->connectToHost("127.0.0.1", 1234);
    socket->waitForReadyRead(5000);
    clientNumber = QString::fromLatin1(socket->readAll()).toInt();

    connect(socket, SIGNAL(readyRead()),
            this,   SLOT(getData()));
    connect(socket, SIGNAL(disconnected()),
            this,   SLOT(deleteLater()));
}

void Client::getData()
{
    if (socket != nullptr)
    {
        QJsonObject in = QJsonDocument::fromBinaryData(socket->readAll()).object();

        for (auto i = in.begin(); i != in.end(); i++)
        {
            if (i.key() == "planets_position")
            {
                for (auto i : in["planets_position"].toArray())
                {
                    planet_data->push_back(i.toDouble());
                }
            }
            else if (i.key() == "delete")
            {
                qDebug() << i.value();
                if (other_clients_data->contains(i.value().toInt()))
                {
                    (*other_clients_data)[i.value().toInt()]->~Client_entity();
                    other_clients_data->take(i.value().toInt());
                }
            }
            else
            {
                if (!other_clients_data->contains(i.key().toInt()))
                {
                    (*other_clients_data)[i.key().toInt()]  = new Client_entity(scene->rootEntity);
                }
                *(*other_clients_data)[i.key().toInt()]->position = i.value().toObject();
                (*other_clients_data)[i.key().toInt()]->moveClientEntity();
            }
        }
    }
}

void Client::sendData()
{
    if (socket != nullptr)
    {
        QVector3D position = scene->view->camera()->position();
        socket->write(QJsonDocument(QJsonObject({{"x",position.x()},
                                                 {"y",position.y()},
                                                 {"z",position.z()}})).toBinaryData());
        socket->flush();
    }
}
