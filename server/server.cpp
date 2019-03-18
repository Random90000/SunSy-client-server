#include "server.h"

#include <QTcpServer>
#include <QJsonObject>

Server::Server(Scene *scene)
    : scene(scene)
    , clients(new QMap<int, Client_entity *>)
    , planets_position(new QJsonArray({0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.}))
{
    if (this->listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Server: listen";
    }
    else
    {
        qDebug() << "Server: " << this->errorString();
    }

    connect(this, SIGNAL(readyExchange()),
            this, SLOT(exchangeData()));
}

void Server::incomingConnection(int socketDescriptor)
{
    Client_entity *entity = new Client_entity(scene->rootEntity, socketDescriptor);

    //entity->socket->setSocketDescriptor(socketDescriptor);
    entity->socket->write(QString::number(entity->socket->socketDescriptor()).toLatin1());

    connect(entity->socket, SIGNAL(disconnected()),
            this,           SLOT(deleteClient()));

    clients->insert(socketDescriptor, entity);

    qDebug() << "Server: Client connected " << socketDescriptor;
}

void Server::exchangeData()
{
    for (auto i = clients->begin(); i != clients->end(); i++)
    {
        *i.value()->position = QJsonDocument::fromBinaryData(i.value()->socket->readAll()).object();
        i.value()->moveClientEntity();

        QJsonObject out;
        out.insert("planets_position", *planets_position);

        for (auto j = clients->begin(); j != clients->end() ; j++)
        {
            if (j != i)
            {
                out.insert(QString::number(j.value()->socket->socketDescriptor()), *j.value()->position);
            }
        }

        i.value()->socket->write(QJsonDocument(out).toBinaryData());
        i.value()->socket->flush();
    }
}

void Server::deleteClient()
{
    for (auto i = clients->begin(); i != clients->end(); i++)
    {
        if (i.value()->socket == sender())
        {
            qDebug() << "Server: Client disconnected " << i.value()->clientNumber;
            for (auto j = clients->begin(); j != clients->end(); j++)
            {
                j.value()->socket->write(QJsonDocument(
                                         QJsonObject{{"delete",(int)i.value()->clientNumber}}
                                                                            ).toBinaryData());
            }
            clients->erase(i);
            i.value()->~Client_entity();
        }
    }
}
