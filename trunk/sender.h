#ifndef SENDER_H
#define SENDER_H

#include<QNetworkInterface>
#include"udpsocket.h"

class Sender : public UdpSocket
{
	Q_OBJECT

public:
	Sender(unsigned port, QObject *parent);
	void sendMessage(QString message);
};

#endif // SENDER_H
