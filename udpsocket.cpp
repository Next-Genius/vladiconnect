#include "udpsocket.h"

UdpSocket::UdpSocket(unsigned int port, QObject *parent): QObject(parent)
{
    this->udpSocket = new QUdpSocket(this);
    this->setPort(port);

}

void UdpSocket::setPort(unsigned int port) {
    this->port = port;
    this->udpSocket->bind(this->port, QUdpSocket::ShareAddress);
}

unsigned int UdpSocket::getPort() {
    return this->port;
}
