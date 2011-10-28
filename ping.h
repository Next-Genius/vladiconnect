#ifndef PING_H
#define PING_H

#include<QProcess>
#include<QObject>

class Ping : public QObject
{
	Q_OBJECT

public:
	enum PingEndState {
		CRASHED,
		RECEIVED,
		LOST
	};

	Ping(QString ip);
	~Ping();

private slots:
	void retourPing(int,QProcess::ExitStatus);
signals:
	void finished(Ping::PingEndState);

private:
	QString ip;
	QProcess* process;
};

#endif // PING_H
