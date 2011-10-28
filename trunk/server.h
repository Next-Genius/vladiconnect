#ifndef SERVER_H
#define SERVER_H

#include<QIcon>
#include<QListWidgetItem>
#include"ping.h"
#include"wol.h"
#include"putty.h"

class Server : public QObject, public QListWidgetItem
{
	Q_OBJECT
public:
	static unsigned int nextId;
	enum ItemType {
		Type,
		UserType ,
		SERVER_TYPE = 1001 //Number >1000 (<1000 reseverd for Qt)
	};

	enum State {
		OFF,
		ON,
		STARTING,
		SHUTING_DOWN,
		REBOOTING
	};

	Server(QListWidget* parent = 0, int type = SERVER_TYPE);
	~Server();

	void ping();
	void start();
	void shutdown();
	void restart();
	void execute(QString);
	void stopProcessus();

	void setName(const QString name);
	void setIp(const QString ip);
	void setMac(const QString mac);
	void setSubnetmask(const QString subnetmask);

	void setOsFromString(QString);

	void setDescription(const QString description);
	void setUser(const QString user);
	void setPassword(const QString password);

	void setOff();
	void setOn();
	void setStarting();
	void setShutingDown();
	void setRebooting();

	const unsigned int& getId();
	const QString getName();
	const QString& getIp();
	const QString& getMac();
	const QString& getSubnetmask();

	const QString getOsToString();

	const QString& getDescription();
	const QString& getUser();
	const QString& getPassword();

	bool isOff();
	bool isOn();
	bool isStarting();
	bool isShutingDown();
	bool isRebooting();

private slots:
	void retourPing(Ping::PingEndState);
	void errorCallback(QString);
	void outputCallback(QString);
	void deletePutty();
signals:
	void stateChanged(State);
	void error(QString);
	void output(QString);
	void info(QString);

private:
	bool openNewPutty();
	const unsigned int id;
	QString ip;
	QString mac;
	QString subnetmask;

	QString description;

	QString user;
	QString password;

	State state;
	Putty::Os os;
	Ping* pingProcess;
	Putty* putty;

};

#endif // SERVER_H
