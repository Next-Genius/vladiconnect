#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include<QObject>
#include<QUdpSocket>

class UdpSocket : public QObject
{
	Q_OBJECT
public:
	UdpSocket(unsigned int port, QObject *parent = 0);
	void setPort(unsigned int port);
	unsigned int getPort();

protected:
	unsigned int port;
	QUdpSocket *udpSocket;
};

#endif // UDPSOCKET_H
