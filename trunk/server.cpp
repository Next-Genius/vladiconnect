#include "server.h"

unsigned int Server::nextId = 1;

Server::Server(QListWidget* parent, int type) : QListWidgetItem(parent, type), id(Server::nextId)
{
	Server::nextId++;
	this->pingProcess = NULL;
	this->putty = NULL;
	this->setOff();
}

Server::~Server() {
	if(this->pingProcess != NULL) {
		delete this->pingProcess;
	}
	if(this->putty != NULL) {
		delete this->putty;
	}
}

void Server::setName(const QString name) {
	this->setText(name);
}

void Server::setUser(const QString user) {
	this->user = user;
}

void Server::setPassword(const QString password) {
	this->password = password;
}

void Server::setIp(const QString ip) {
	this->ip = ip;
}

void Server::setMac(const QString mac) {
	this->mac = mac;
}

void Server::setSubnetmask(const QString subnetmask) {
	this->subnetmask = subnetmask;
}

void Server::setDescription(const QString description) {
	this->description = description;
}

void Server::setOsFromString(QString) {
	this->os = Putty::WINDOWS;
}

const unsigned int& Server::getId() {
	return this->id;
}

const QString Server::getName() {
	return this->text();
}

const QString& Server::getIp() {
	return this->ip;
}

const QString& Server::getMac() {
	return this->mac;
}

const QString& Server::getSubnetmask() {
	return this->subnetmask;
}

const QString& Server::getPassword() {
	return this->password;
}

const QString& Server::getUser() {
	return this->user;
}

const QString& Server::getDescription() {
	return this->description;
}

const QString Server::getOsToString() {
	return QString("Linux");
}

void Server::start() {
	QString myMac = this->getMac();
	if(myMac.isEmpty()) {
		emit error(tr("The MAC address is empty !"));
		return;
	}
	QRegExp regExp("^([a-fA-F0-9]{2}:){5}[a-fA-F0-9]{2}$");
	if(!myMac.contains(regExp)) {
		emit error(tr("The MAC adresse is not correct. "
							 "Please, check syntax !"));
		return;
	}
	wol::send_wol(myMac);
	this->setStarting();
	emit error(tr("A magic-paquet has been sent to %1.").arg(myMac));
}

void Server::ping() {
	QString myIp = this->getIp();
	if(myIp.isEmpty()) {
		emit error("L'adresse IP de la machine est vide !");
		return;
	}
	if(pingProcess != NULL) {
		emit error("Un ping est déjà en cours pour ce serveur !");
		return;
	}
	this->pingProcess = new Ping(myIp);
	QObject::connect(this->pingProcess, SIGNAL(finished(Ping::PingEndState)),
					this, SLOT(retourPing(Ping::PingEndState)));
}


void Server::retourPing(Ping::PingEndState statePing) {

	if(statePing == Ping::CRASHED) {
		emit error("Le processus ne s'est pas terminé correctement (crash)");
	} else if(statePing == Ping::RECEIVED) {
		//if(this->isOff() || this->isStarting()) {
			//Edit only if the computer will keep alive (else we keep the current icon)
			this->setOn();
		//}

	} else {
		this->setOff();
	}

	delete this->pingProcess;
	this->pingProcess = NULL;
}

void Server::outputCallback(QString myString) {
	emit output(myString);
}

void Server::errorCallback(QString myString) {
	emit error(myString);
}


bool Server::openNewPutty() {
	if(!this->isOn()) {
		emit error(tr("The machine is not connected. " \
		"It's not possible execute any command !"));
		return false;
	}
	if(this->putty != NULL) {
		emit error(tr("A command has already been launched on this machine ! "\
			"Please wait !"));
		return false;
	}

	this->putty = new Putty(this->getIp(), this->getUser(), this->getPassword(), this->os);

	QObject::connect(this->putty, SIGNAL(error(QString)), this, SLOT(errorCallback(QString)));
	QObject::connect(this->putty, SIGNAL(output(QString)), this, SLOT(outputCallback(QString)));
	QObject::connect(this->putty, SIGNAL(finished()), this, SLOT(deletePutty()));

	return true;
}

void Server::shutdown() {
	if(this->openNewPutty()) {
		this->putty->addCommand(QString("y"));
		this->putty->stopMachine();
		this->putty->run();

		this->setShutingDown();
	}
	emit error(tr("The machine %1 will be shutdown.").arg(this->getIp()));
}

void Server::restart() {
	if(this->openNewPutty()) {
		this->putty->addCommand(QString("y"));
		this->putty->rebootMachine();
		this->putty->run();

		this->setRebooting();
		emit error(tr("The machine %1 will be reboot.").arg(this->getIp()));
	}

}

void Server::execute(QString commande) {
	if(this->openNewPutty()) {
		this->putty->addCommand(QString("y"));
		this->putty->addCommand(commande);
		this->putty->addCommand(QString("logout"));
		this->putty->run();

		emit error(tr("The command %1 has been launched on %2.").arg(commande, this->getIp()));
	}

}

void Server::deletePutty() {
	if(this->putty != NULL) {
		delete this->putty;
		this->putty = NULL;
	}
}

void Server::stopProcessus() {
	if(this->putty == NULL) {
		emit error(tr("There is no process to stop"));
		return;
	} else {
		this->deletePutty();
		emit error(tr("Process has been stopped !"));
	}
}


void Server::setOff() {
	this->state = this->OFF;
	this->setIcon(QIcon(":/images/network-offline.png"));
	emit stateChanged(this->state);
}

void Server::setOn() {
	this->state = this->ON;
	this->setIcon(QIcon(":/images/network-transmit-receive.png"));
	emit stateChanged(this->state);
}

void Server::setStarting() {
	this->state = this->STARTING;
	this->setIcon(QIcon(":/images/start.png"));
	emit stateChanged(this->state);
}

void Server::setShutingDown() {
	this->state = this->SHUTING_DOWN;
	this->setIcon(QIcon(":/images/stop.png"));
	emit stateChanged(this->state);
}

void Server::setRebooting() {
	this->state = this->REBOOTING;
	this->setIcon(QIcon(":/images/restart.png"));
	emit stateChanged(this->state);
}

bool Server::isOff() {
	return this->state == this->OFF;
}

bool Server::isOn() {
	return this->state == this->ON;
}

bool Server::isStarting() {
	return this->state == this->STARTING;
}

bool Server::isShutingDown() {
	return this->state == this->SHUTING_DOWN;
}

bool Server::isRebooting() {
	return this->state == this->REBOOTING;
}
