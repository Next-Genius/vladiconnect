#ifndef RECEIVER_H
#define RECEIVER_H

#include"udpsocket.h"

class Receiver : public UdpSocket
{
	Q_OBJECT

public:
	Receiver(unsigned int port, QObject *parent = 0);

private slots:
	void processPendingDatagrams();

signals:
	void receivedMessage(QString);

};

#endif // RECEIVER_H
