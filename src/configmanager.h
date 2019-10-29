#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QDate>
#include <QTime>
#include <QObject>
#include <QString>
#include <QFileSystemWatcher>
#include <QSettings>

class ConfigManager: public QObject
{
Q_OBJECT
public:

    static const QString version;
    static QString apiPort;
    static QString apiSecret;
    static QString apiUrl;
    static const QDate buildDate;
    static const QTime buildTime;
    static bool startAtLogin;
    static bool allowConnectFromLan;
    static QString selectConfigName;
    static bool proxyPortAutoSet;
    static QSettings settings;
    static bool enhanceMode;
    static bool buildInApiMode;

    static QFileSystemWatcher *watcher;

    static void watchConfigFile(QString configName);
    static void copySampleConfigIfNeed();
    static void checkFinalRuleAndShowAlert();
    static void showNoFinalRuleAlert();
    static QStringList getConfigFilesList();

private slots:
    static void fileChanged();
};

#endif // CONFIGMANAGER_H
