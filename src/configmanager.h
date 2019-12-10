//
//  configmanager.h
//  ShadowClash
//
//  Created by TheWanderingCoel on 2018/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

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
    static bool enhanceMode;
    static bool buildInApiMode;
    static QString selectDashBoard;
    static QString benchMarkUrl;
    static int windowNumber; // current number of windows active

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
