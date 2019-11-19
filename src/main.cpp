//
//  main.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2018/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "appdelegate.h"
#include "appversionutil.h"
#include "clashresourcemanager.h"
#include "configmanager.h"
#include "enhancemodemanager.h"
#include "fvupdater.h"
#include "logger.h"
#include "mainwindow.h"
#include "proxyconfighelpermanager.h"
#include "runguard.h"
#include "systemtray.h"

#include <QApplication>
#include <QMessageBox>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RunGuard guard("ShadowClash");

    // make sure only one shadowclash
    if (!guard.isSingleInstance()) {
        QMessageBox alert;
        alert.setWindowTitle("ShadowClash");
        alert.setText(QObject::tr("Another instance of ShadowClash is already running."));
        alert.exec();
        return -1;
    }

    QApplication::setApplicationName("ShadowClash");
    QApplication::setApplicationVersion(ConfigManager::version);
    QApplication::setOrganizationName("coelwu");
    QApplication::setOrganizationDomain("com.coelwu");

    // setup systemtray first
    SystemTray *systemtray = new SystemTray;
    systemtray->createActions();
    systemtray->createShortCuts();
    systemtray->createTrayIcon();
    systemtray->setCheckable();
    systemtray->trayIcon->show();

    FvUpdater::sharedUpdater()->SetFeedURL("https://raw.github.com/pypt/fervor/master/sample/Appcast.xml");
    FvUpdater::sharedUpdater()->CheckForUpdatesSilent();

    // install proxy helper
    ClashResourceManager::check();
    ConfigManager::copySampleConfigIfNeed();
    ProxyConfigHelperManager::install();
    EnhanceModeManager::install();
    Logger::init();

    // start proxy
    AppDelegate::updateConfig();

    // update Systemtray's info after proxy start
    systemtray->setTrayProxyMode();
    systemtray->setPortsMenu();
    systemtray->setTrayLogLevel();
    systemtray->setConfigList();

    // start watch config file change
    ConfigManager::watchConfigFile("config");

    // setup app settings
    AppVersionUtil::init();

    MainWindow w;
    w.show();
    return a.exec();
}
