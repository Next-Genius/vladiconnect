#include "putty.h"

Putty::Putty(QString host, QString user, QString password, Os os) : QObject(NULL) {
	this->process = new Process(NULL);

	QObject::connect(this->process, SIGNAL(outputToPrint(QString)),
				 this, SLOT(outputProcess(QString)));

	QObject::connect(this->process, SIGNAL(stateChanged(QProcess::ProcessState)),
				 this, SLOT(sendCommand(QProcess::ProcessState)));
	QObject::connect(this->process, SIGNAL(finished(Process::EndState)),
				 this, SLOT(finished(Process::EndState)));
	this->setHost(host);
	this->setUser(user);
	this->setPassword(password);
	this->os = os;
	this->setPath(QCoreApplication::applicationDirPath());
}

Putty::~Putty() {
	this->process->terminate();
	delete this->process;
	emit error(tr("End of the process."));
}

void Putty::setHost(QString host) {
	if(host.isEmpty()) {
		emit error(tr("The hostname can't be empty !"));
		return;
	}
	this->host = host;
}

void Putty::setUser(QString user) {
	if(user.isEmpty()) {
		emit error(tr("The login can't be empty !"));
		return;
	}
	this->user = user;
}

void Putty::setPassword(QString password) {
	if(password.isEmpty()) {
		emit error(tr("The password can't be empty !"));
		return;
	}
	this->password = password;
}

void Putty::setPath(QString path) {
	this->path = path;
}

bool Putty::isValid() {
	if(this->host.isEmpty() || this->user.isEmpty() || this->password.isEmpty() || this->path.isEmpty()) {
		return false;
	} else {
		return true;
	}
}

void Putty::addCommand(QString commande) {
	this->commands.enqueue(commande+ "\n");
}

void Putty::finished(Process::EndState state) {
	if(state == Process::FAIL) {
		emit output(tr("Finished with error"));
		emit error(tr("Finished with error"));
	} else {
		emit output(tr("Finished"));
	}
	emit finished();
}

void Putty::run() {

	if(!isValid()) {
		emit error(tr("Parameters are empty !"\
			" Please, specify username, password, etc."));
		return;
	}

	QString chemin_executable(this->path+"/plink.exe");
	QFile file(chemin_executable);

	if(!file.exists()) {
		emit error(tr("The program which permits the "
			"wake-on-lan has not been found ! "
			"Check the existence of the file :")+ " " + chemin_executable+"\n" );
		return;
	}

	QString commandeToExecute("\""+chemin_executable+"\" -ssh -v -pw "+this->password+" "+this->user+"@"+this->host+" ");
		//-v : verbosity
		//-l : specifier login
		//-P : port
		//-pw : password (not recommended)

	this->process->start(commandeToExecute);
}

void Putty::outputProcess(QString content) {
	emit output(content);
}

void Putty::sendCommand(QProcess::ProcessState state) {
	if(state == QProcess::Running) {
		if(!this->commands.isEmpty()) {
			while(!this->commands.isEmpty()) {
				this->process->write(this->commands.dequeue().toUtf8());
				//emit error("Défile" + QString::number(this->commands.size()));
			}

		} else {
			emit error(tr("There is no more command to send !"));
		}
			// /c ; ferme tout en forçant.
			// /a pour annuler un arret
			// /r pour un reboot

	} else {
		emit error(tr("The process is not ready !"));
	}
}

void Putty::rebootMachine() {
	if(this->os == LINUX) {
		this->addCommand("sudo shutdown -r now");
		this->addCommand(this->password);
	} else { //Windows
		this->addCommand("net rpc shutdown -f -I \\"+this->host+" -U \\"+this->user+"%"+this->password+" -t 30 -C \"Reboot lance par Vladiconnect\"");
			// /c ; ferme tout en forçant.
			// /a pour annuler un arret
			// /r pour un reboot
	}
}

void Putty::stopMachine() {
	//if(this->os == LINUX) {
		this->addCommand("sudo shutdown -hP now");
		this->addCommand(this->password);
		emit error(tr("Shutdown for the current Linux machine"));
	/*} else { //Windows
		#ifdef CWINDOWS
		this->addCommand("NET USER "+this->user+" \\"+this->host);
		this->addCommand("SHUTDOWN \\"+this->host+' /l /t: 30 "Arret à distance lancé par Vladiconnect" /y /c');
		#endif

		#ifdef CLINUX
		this->addCommand("net rpc shutdown -f -I \\"+this->host+" -U \\"+this->user+"%"+this->password+" -t 30 -C \"Arret lance par Vladiconnect\"");
			// /c ; ferme tout en forçant.
			// /a pour annuler un arret
			// /r pour un reboot
		#endif
	}*/
}


