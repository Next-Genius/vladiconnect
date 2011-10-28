#include "receiver.h"

Receiver::Receiver(unsigned int port, QObject *parent): UdpSocket(port, parent)
{

    connect(udpSocket, SIGNAL(readyRead()),
                 this, SLOT(processPendingDatagrams()));
}


void Receiver::processPendingDatagrams()
{
    while (this->udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
	this->udpSocket->readDatagram(datagram.data(), datagram.size());

        emit receivedMessage(QString(datagram.data()));

    }
}

