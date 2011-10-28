#include "process.h"


Process::Process(QObject* parent) : QProcess(parent)
{
	QObject::connect(this, SIGNAL(readyReadStandardError()),
					this, SLOT(printOutput()));
	QObject::connect(this, SIGNAL(readyReadStandardOutput()),
					this, SLOT(printOutput()));

	QObject::connect(this, SIGNAL(finished(int, QProcess::ExitStatus)),
					this, SLOT(finishedProcess(int, QProcess::ExitStatus)));
}


void Process::printOutput() {
	QString outputMessage(this->readAllStandardError()
						+ this->readAllStandardOutput());
	emit outputToPrint(outputMessage);

}

void Process::finishedProcess(int exitCode, QProcess::ExitStatus exitStatus) {
	if(exitStatus == QProcess::CrashExit || exitCode != 0) {
		emit finished(this->FAIL);
	} else {
		emit finished(this->OK);
	}
}
