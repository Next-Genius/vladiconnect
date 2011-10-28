#ifndef PUTTY_H
#define PUTTY_H

#include <QCoreApplication>
#include<QObject>
#include<QProcess>
#include<QFile>
#include<QQueue>
#include<QDebug>
#include"process.h"
//#include"server.h"

class Putty : public QObject
{
	Q_OBJECT

	public:

	enum Os {
		WINDOWS,
		WINDOWS_XP,
		WINDOWS_7,
		LINUX
	};

	Putty(QString hote, QString utilisateur, QString mdp, Os os);
	~Putty();

	void run();

	bool isValid();

	void setHost(QString);
	void setUser(QString);
	void setPassword(QString);
	void setPath(QString);
	void addCommand(QString);
	void stopMachine();
	void rebootMachine();

private slots:
	void outputProcess(QString);
	void sendCommand(QProcess::ProcessState);
	void finished(Process::EndState);
signals:
	void error(QString);
	void output(QString);
	void finished();
protected:
	int windows_arreter();

	QString host;
	QString user;
	QString password;
	QString path;
	QQueue<QString> commands;
	Process* process;

	Os os;

};


#endif // PUTTY_H
