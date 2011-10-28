#ifndef PROCESS_H
#define PROCESS_H

#include<QProcess>

class Process : public QProcess
{
	Q_OBJECT

public:
	enum EndState {
		OK,
		FAIL
	};

	Process(QObject* parent = 0);


private slots:
	void printOutput();
	void finishedProcess(int, QProcess::ExitStatus);


signals:
	void outputToPrint(QString);
	void finished(Process::EndState);
};

#endif // PROCESS_H
