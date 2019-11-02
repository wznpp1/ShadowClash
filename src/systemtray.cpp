//
//  systemtray.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2018/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "aboutwindow.h"
#include "apirequest.h"
#include "appdelegate.h"
#include "clashconfig.h"
#include "configmanager.h"
#include "enhancemodemanager.h"
#include "fvupdater.h"
#include "launchatlogin.h"
#include "mainwindow.h"
#include "notificationcenter.h"
#include "paths.h"
#include "proxyconfighelpermanager.h"
#include "systemtray.h"

#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QClipboard>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QKeySequence>
#include <QMenu>
#include <QMessageBox>
#include <QSettings>
#include <QUrl>

void SystemTray::createActions()
{
    proxyModeGroup = new QActionGroup(this);
    proxyModeGroup->setExclusive(true);

    globeAction = new QAction(tr("Global"), proxyModeGroup);
    ruleAction = new QAction(tr("Rule"), proxyModeGroup);
    directAction = new QAction(tr("Direct"), proxyModeGroup);
    // Separator
    setAsSystemProxyAction = new QAction(tr("Set as system proxy"));
    copyExportCommandAction = new QAction(tr("Copy export command"));
    enhanceModeAction = new QAction(tr("Enhance Mode"));
    // Separator
    startAtLoginAction = new QAction(tr("Start at login"));
    showNetworkIndicatorAction = new QAction(tr("Show network indicator"));
    allowLanConnectionAction = new QAction(tr("Allow connect from Lan"));
    // Separator
    dashBoardAction = new QAction(tr("DashBoard"));
    speedTestAction = new QAction(tr("SpeedTest"));
    // Config Menu
    configListGroup = new QActionGroup(this);
    configListGroup->setExclusive(true);
    openConfigFolderAction = new QAction(tr("Open config Folder"));
    reloadConfigAction = new QAction(tr("Reload config"));

    dashBoardGroup = new QActionGroup(this);
    dashBoardGroup->setExclusive(true);

    clashxAction = new QAction(tr("ClashX"));
    yacdAction = new QAction(tr("Yacd"));

    showCurrentProxyAction = new QAction(tr("Show current proxy in menu"));
    useBuildInApiAction = new QAction(tr("Use built in api"));
    setBenchmarkUrlAction = new QAction(tr("Set benchmark url"));

    // Help Menu
    aboutAction = new QAction(tr("About"));
    aboutQtAction = new QAction(tr("About Qt"));
    logGroup = new QActionGroup(this);
    logGroup->setExclusive(true);
    errorAction = new QAction(tr("ERROR"), logGroup);
    warningAction = new QAction(tr("WARNING"), logGroup);
    infoAction = new QAction(tr("INFO"), logGroup);
    debugAction = new QAction(tr("DEBUG"), logGroup);
    silentAction = new QAction(tr("SILENT"), logGroup);
    checkUpdateAction = new QAction(tr("Check Update"));
    showLogAction = new QAction(tr("Show Log"));
    // Ports Menu
    httpPortAction = new QAction("Http Port:");
    httpPortAction->setEnabled(false);
    socksPortAction = new QAction("Socks Port:");
    socksPortAction->setEnabled(false);
    apiPortAction = new QAction("Api Port:");
    apiPortAction->setEnabled(false);

    quitAction = new QAction("Quit");

    connect(proxyModeGroup, SIGNAL(triggered(QAction*)), this, SLOT(switchProxyMode(QAction*)));
    connect(setAsSystemProxyAction, &QAction::triggered, this, &SystemTray::setSystemProxy);
    connect(copyExportCommandAction, &QAction::triggered, this, &SystemTray::copyExportCommand);
    connect(enhanceModeAction, &QAction::triggered, this, &SystemTray::setEnhanceMode);
    connect(speedTestAction, &QAction::triggered, this, &SystemTray::speedTest);
    connect(dashBoardAction, &QAction::triggered, this, &SystemTray::showWindow);
    connect(startAtLoginAction, &QAction::triggered, this, &SystemTray::setupAutoStart);
    connect(allowLanConnectionAction, &QAction::triggered, this, &SystemTray::allowFromLan);
    connect(configListGroup, SIGNAL(triggered(QAction*)), this, SLOT(switchConfig(QAction*)));
    connect(openConfigFolderAction, &QAction::triggered, this, &SystemTray::openConfigFolder);
    connect(reloadConfigAction, &QAction::triggered, this, &SystemTray::requestConfigUpdate);
    connect(aboutAction, &QAction::triggered, this, &SystemTray::pushAboutWindow);
    connect(aboutQtAction, &QAction::triggered, QApplication::aboutQt);
    connect(logGroup, SIGNAL(triggered(QAction*)), this, SLOT(setLogLevel(QAction*)));
    connect(checkUpdateAction, &QAction::triggered, FvUpdater::sharedUpdater(), &FvUpdater::CheckForUpdatesNotSilent);
    connect(quitAction, &QAction::triggered, &AppDelegate::applicationWillTerminate);
}

void SystemTray::createShortCuts()
{
    globeAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_G));
    ruleAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_R));
    directAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_D));

    setAsSystemProxyAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    copyExportCommandAction->setShortcuts(QKeySequence::Copy);
    enhanceModeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));

    dashBoardAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    speedTestAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));

    openConfigFolderAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    reloadConfigAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));

    checkUpdateAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
    showLogAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));

    quitAction->setShortcuts(QKeySequence::Quit);
}

void SystemTray::createTrayIcon()
{
    trayIconMenu = new QMenu();
    proxyModeMenu = new QMenu("Proxy Mode");
    configMenu = new QMenu(tr("Config"));
    dashBoardMenu = new QMenu(tr("Dashboard"));
    experimentalMenu = new QMenu(tr("Experimental"));
    helpMenu = new QMenu(tr("Help"));
    configListMenu = new QMenu(tr("Swtich Config"));
    logMenu = new QMenu(tr("Log level"));
    portsMenu = new QMenu(tr("Ports"));

    proxyModeMenu->addAction(globeAction);
    proxyModeMenu->addAction(ruleAction);
    proxyModeMenu->addAction(directAction);

    trayIconMenu->addMenu(proxyModeMenu);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(setAsSystemProxyAction);
    trayIconMenu->addAction(copyExportCommandAction);
    trayIconMenu->addAction(enhanceModeAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(startAtLoginAction);
    trayIconMenu->addAction(showNetworkIndicatorAction);
    trayIconMenu->addAction(allowLanConnectionAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(dashBoardAction);
    trayIconMenu->addAction(speedTestAction);
    trayIconMenu->addSeparator();

    configMenu->addMenu(configListMenu);
    configMenu->addAction(openConfigFolderAction);
    configMenu->addAction(reloadConfigAction);
    configMenu->addMenu(dashBoardMenu);
    configMenu->addMenu(experimentalMenu);

    dashBoardMenu->addAction(clashxAction);
    dashBoardMenu->addAction(yacdAction);

    experimentalMenu->addAction(showCurrentProxyAction);
    experimentalMenu->addAction(useBuildInApiAction);
    experimentalMenu->addAction(setBenchmarkUrlAction);

    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
    helpMenu->addMenu(logMenu);
    logMenu->addAction(errorAction);
    logMenu->addAction(warningAction);
    logMenu->addAction(infoAction);
    logMenu->addAction(debugAction);
    logMenu->addAction(silentAction);
    helpMenu->addAction(checkUpdateAction);
    helpMenu->addAction(showLogAction);

    portsMenu->addAction(httpPortAction);
    portsMenu->addAction(socksPortAction);
    portsMenu->addAction(apiPortAction);

    helpMenu->addMenu(portsMenu);

    trayIconMenu->addMenu(configMenu);
    trayIconMenu->addMenu(helpMenu);
    trayIconMenu->addAction(quitAction);

    QIcon icon = QIcon(":/icons/menu_icon.png");

#if defined(Q_OS_MACOS) || defined(Q_OS_MAC)
    icon.setIsMask(true);
#endif

    trayIcon = new QSystemTrayIcon(icon);
    trayIcon->setContextMenu(trayIconMenu);

    connect(trayIcon, &QSystemTrayIcon::activated, this, &SystemTray::updateInfo);
}

void SystemTray::setCheckable()
{
    globeAction->setCheckable(true);
    ruleAction->setCheckable(true);
    directAction->setCheckable(true);
    setAsSystemProxyAction->setCheckable(true);
    enhanceModeAction->setCheckable(true);
    startAtLoginAction->setCheckable(true);
    showNetworkIndicatorAction->setCheckable(true);
    allowLanConnectionAction->setCheckable(true);
    errorAction->setCheckable(true);
    warningAction->setCheckable(true);
    infoAction->setCheckable(true);
    debugAction->setCheckable(true);
    silentAction->setCheckable(true);
}

void SystemTray::updateInfo()
{
    ApiRequest::requestConfig();
    setConfigList();
    setTrayProxyMode();
    allowLanConnectionAction->setChecked(ClashConfig::allowLan);
    setPortsMenu();
    setTrayLogLevel();
}

void SystemTray::setTrayProxyMode()
{
    proxyModeMenu->setTitle(tr(qPrintable(QString("Proxy Mode (%1)").arg(ClashConfig::mode))));
    if (ClashConfig::mode == "Globe") {
        globeAction->setChecked(true);
    } else if (ClashConfig::mode == "Rule") {
        ruleAction->setChecked(true);
    } else if (ClashConfig::mode == "Direct") {
        directAction->setChecked(true);
    }
}

void SystemTray::switchConfig(QAction *action)
{
    ConfigManager::selectConfigName = action->text();
    ApiRequest::requestConfigUpdate(true);
    action->setChecked(true);
}

void SystemTray::setPortsMenu()
{
    httpPortAction->setText("Http Port:" + QString::number(ClashConfig::port));
    socksPortAction->setText("Socks Port:" + QString::number(ClashConfig::socketPort));
    apiPortAction->setText("Api Port:" + ConfigManager::apiPort);
}

void SystemTray::setConfigList()
{
    QStringList configList = ConfigManager::getConfigFilesList();
    for (int i=0; i<configList.size(); i++){
        QAction *action = new QAction(configList[i]);
        if (configList[i] == ConfigManager::selectConfigName) {
            action->setCheckable(true);
            action->setChecked(true);
        }
        configListMenu->addAction(action);
    }
}

void SystemTray::setTrayLogLevel()
{
    if (ClashConfig::logLevel == "error") {
        errorAction->setChecked(true);
    } else if (ClashConfig::logLevel == "warning") {
        warningAction->setChecked(true);
    } else if (ClashConfig::logLevel == "info") {
        infoAction->setChecked(true);
    } else if (ClashConfig::logLevel == "debug") {
        debugAction->setChecked(true);
    } else if (ClashConfig::logLevel == "silent") {
        silentAction->setChecked(true);
    }
}

void SystemTray::switchProxyMode(QAction *action)
{
    if (action->text() == tr("Global")) {
        apirequest->updateOutBoundMode("Global");
        ClashConfig::mode = "Global";
    } else if (action->text() == tr("Rule")) {
        apirequest->updateOutBoundMode("Rule");
        ClashConfig::mode = "Rule";
    } else if (action->text() == tr("Direct")) {
        apirequest->updateOutBoundMode("Direct");
        ClashConfig::mode = "Direct";
    }
    action->setChecked(true);
    proxyModeMenu->setTitle(tr(qPrintable(QString("Proxy Mode (%1)").arg(ClashConfig::mode))));
}

void SystemTray::setSystemProxy()
{
    ConfigManager::proxyPortAutoSet = !ConfigManager::proxyPortAutoSet;
    if (ConfigManager::proxyPortAutoSet) {
        int port = ClashConfig::port;
        int socketPort = ClashConfig::socketPort;
        ProxyConfigHelperManager::setUpSystemProxy(port, socketPort);
    } else {
        ProxyConfigHelperManager::setUpSystemProxy(0, 0);
    }
}

void SystemTray::copyExportCommand()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->clear();
    int port = ClashConfig::port;
    int socksport = ClashConfig::socketPort;
    clipboard->setText(QString("export https_proxy=http://127.0.0.1:%1;export http_proxy=http://127.0.0.1:%1;export all_proxy=socks5://127.0.0.1:%2").arg(port).arg(socksport));
}

void SystemTray::setEnhanceMode()
{
    ConfigManager::enhanceMode = !ConfigManager::enhanceMode;
    if (ConfigManager::enhanceMode) {
        EnhanceModeManager::startTun2socks();
    } else {
        EnhanceModeManager::stopTun2socks();
    }
}

void SystemTray::speedTest()
{
    if (isSpeedTesting) {
        notificationCenter->postSpeedTestingNotice();
        return;
    }
    notificationCenter->postSpeedTestBeginNotice();

    isSpeedTesting = true;

    notificationCenter->postSpeedTestFinishNotice();
    isSpeedTesting = false;
}

void SystemTray::showWindow()
{
    MainWindow mainwindow;
    // prevent Mulitple Windows
    apirequest->requestConfigUpdate(true);
}

void SystemTray::setupAutoStart()
{
    LaunchAtLogin *launchAtLogin = new LaunchAtLogin();
    launchAtLogin->setupAutoStart(!ConfigManager::startAtLogin);
    ConfigManager::startAtLogin = !ConfigManager::startAtLogin;
    startAtLoginAction->setChecked(ConfigManager::startAtLogin);
}

void SystemTray::allowFromLan()
{
    apirequest->updateAllowLan(!ClashConfig::allowLan);
    ClashConfig::allowLan = !ClashConfig::allowLan;
    allowLanConnectionAction->setChecked(ClashConfig::allowLan);
}

void SystemTray::openConfigFolder()
{
    QDesktopServices::openUrl(QUrl("file://" + Paths::configFolderPath, QUrl::TolerantMode));
}

void SystemTray::requestConfigUpdate()
{
    ApiRequest::requestConfigUpdate(true);
}

void SystemTray::pushAboutWindow()
{
    AboutWindow *view = new AboutWindow();
    view->exec();
}

void SystemTray::setLogLevel(QAction *action)
{
    if (action->text() == tr("ERROR")) {
        apirequest->updateLogLevel("error");
        ClashConfig::mode = "error";
    } else if (action->text() == tr("WARNING")) {
        apirequest->updateLogLevel("warning");
        ClashConfig::mode = "warning";
    } else if (action->text() == tr("INFO")) {
        apirequest->updateLogLevel("info");
        ClashConfig::mode = "info";
    } else if (action->text() == tr("DEBUG")) {
        apirequest->updateLogLevel("debug");
        ClashConfig::mode = "debug";
    } else if (action->text() == tr("SILENT")) {
        apirequest->updateLogLevel("silent");
        ClashConfig::mode = "silent";
    }
}

/*
void SystemTray::setBenchmarkUrl()
{
    QMessageBox alert;
    alert.setText("Benchmark");
}*/
