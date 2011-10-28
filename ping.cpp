#include "ping.h"

Ping::Ping(QString ip) {
	this->ip = ip;
	this->process = new QProcess;
	QString arguments;

	//Limiter à un ping
	#ifdef CWINDOWS    //Windows
		arguments = "ping "+ip+" -n 1 -w 1";
	#endif

	#ifdef CLINUX
		arguments = "ping "+ip+" -c 1 -w 1";   //Linux
	#endif

	this->process->start(arguments);

	QObject::connect(this->process,
					 SIGNAL(finished(int,QProcess::ExitStatus)), this,
					 SLOT(retourPing(int,QProcess::ExitStatus)));
}

Ping::~Ping() {
	delete this->process;
}


void Ping::retourPing(int exitCode,QProcess::ExitStatus exitStatus) {
	PingEndState pingState;

	if(exitStatus == QProcess::CrashExit) {
		pingState = this->CRASHED;
	} else if(exitCode == 0) {
		pingState = this->RECEIVED;
	} else {
		pingState = this->LOST;
	}

	emit finished(pingState);
}


