#ifndef REMOTECONFIGMANAGER_H
#define REMOTECONFIGMANAGER_H

#include <QString>
#include <QObject>

class RemoteConfigManager: public QObject
{
public:
    QString getRemoteConfigData(QString url);
    QString updateConfig();
    QString verifyConfig(QString string);
};

#endif // REMOTECONFIGMANAGER_H
