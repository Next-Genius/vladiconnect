#include "sender.h"

Sender::Sender(unsigned port, QObject *parent) : UdpSocket(port, parent)
{

}

void Sender::sendMessage(QString message) {
	QNetworkInterface myNetworkInterface = QNetworkInterface();
	QList<QHostAddress> hosts =  myNetworkInterface.allAddresses();
	QString hostname;

	if(hosts.first().toString() == QString("127.0.0.1") && hosts.count() > 3) {
		hostname = hosts.at(3).toString();
	} else {
		hostname = hosts.first().toString();
	}

	message += " " + QString(tr("from")) + " " + hostname;
	QByteArray datagram = message.toUtf8();
	this->udpSocket->writeDatagram(datagram.data(), datagram.size(),
			      QHostAddress::Broadcast, this->port);
}

