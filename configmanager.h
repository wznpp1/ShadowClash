#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QDate>
#include <QTime>
#include <QString>

class ConfigManager
{
public:
    ConfigManager();

    static const QString version;
    static QString apiPort;
    static QString apiSecret;
    static QString apiUrl;
    static const QDate buildDate;
    static const QTime buildTime;

    void checkFinalRuleAndShowAlert();
};

#endif // CONFIGMANAGER_H
