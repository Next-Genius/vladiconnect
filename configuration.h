#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>

class Configuration : public QObject
{
public:
    Configuration();
	void load();
	void save();
};

#endif // CONFIGURATION_H
