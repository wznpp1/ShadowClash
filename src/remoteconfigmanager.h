#ifndef REMOTECONFIGMANAGER_H
#define REMOTECONFIGMANAGER_H

#include <QObject>

class RemoteConfigManager: public QObject
{
public:
    static QString getRemoteConfigData(QString url);
    static bool updateConfig(QString url, QString configName);
    static QString verifyConfig(QString string);
};

#endif // REMOTECONFIGMANAGER_H
