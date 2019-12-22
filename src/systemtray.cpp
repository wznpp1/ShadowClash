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
#include "remoteconfigwindow.h"
#include "settings.h"
#include "systemtray.h"

#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QClipboard>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QInputDialog>
#include <QKeySequence>
#include <QMenu>
#include <QMessageBox>
#include <QSettings>
#include <QUrl>

#if defined(Q_OS_MAC)
#include <CoreServices/CoreServices.h>
#include <CoreFoundation/CoreFoundation.h>
#endif

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

    manageAction = new QAction(tr("Manage"));
    updateAction = new QAction(tr("Update"));
    autoUpdateAction = new QAction(tr("Auto Update"));

    dashBoardGroup = new QActionGroup(this);
    dashBoardGroup->setExclusive(true);

    uiGroup = new QActionGroup(this);
    uiGroup->setExclusive(true);

    clashxAction = new QAction(tr("ClashX"), uiGroup);
    yacdAction = new QAction(tr("Yacd"), uiGroup);

    showCurrentProxyAction = new QAction(tr("Show current proxy in menu"));
    useBuildInApiAction = new QAction(tr("Use built in api"));
    setBenchmarkUrlAction = new QAction(tr("Set benchmark url"));
    autoCloseConnectionAction = new QAction(tr("Auto Close Connection"));

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
    redirPortAction = new QAction("Redir Port:");
    redirPortAction->setEnabled(false);
    apiPortAction = new QAction("Api Port:");
    apiPortAction->setEnabled(false);

    quitAction = new QAction(tr("Quit"));

    connect(proxyModeGroup, SIGNAL(triggered(QAction*)), this, SLOT(switchProxyMode(QAction*)));
    connect(setAsSystemProxyAction, &QAction::triggered, this, &SystemTray::setSystemProxy);
    connect(copyExportCommandAction, &QAction::triggered, this, &SystemTray::copyExportCommand);
    connect(enhanceModeAction, &QAction::triggered, this, &SystemTray::setEnhanceMode);
    connect(speedTestAction, &QAction::triggered, this, &SystemTray::speedTest);
    connect(dashBoardAction, &QAction::triggered, this, &SystemTray::showWindow);
    connect(startAtLoginAction, &QAction::triggered, this, &SystemTray::setupAutoStart);
    connect(allowLanConnectionAction, &QAction::triggered, this, &SystemTray::allowFromLan);
    connect(manageAction, &QAction::triggered, this, &SystemTray::showRemoteConfigWindow);
    connect(configListGroup, SIGNAL(triggered(QAction*)), this, SLOT(switchConfig(QAction*)));
    connect(openConfigFolderAction, &QAction::triggered, this, &SystemTray::openConfigFolder);
    connect(reloadConfigAction, &QAction::triggered, this, &SystemTray::requestConfigUpdate);
    connect(uiGroup, SIGNAL(triggered(QAction*)), this, SLOT(switchUiDashboard(QAction*)));
    connect(setBenchmarkUrlAction, &QAction::triggered, this, &SystemTray::setBenchmarkUrl);
    connect(aboutAction, &QAction::triggered, this, &SystemTray::pushAboutWindow);
    connect(aboutQtAction, &QAction::triggered, QApplication::aboutQt);
    connect(showLogAction, &QAction::triggered, this, &SystemTray::showLog);
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

    manageAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
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
    remoteConfigMenu = new QMenu(tr("Remote Config"));
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
    configMenu->addMenu(remoteConfigMenu);
    configMenu->addAction(openConfigFolderAction);
    configMenu->addAction(reloadConfigAction);
    configMenu->addMenu(dashBoardMenu);
    configMenu->addMenu(experimentalMenu);

    remoteConfigMenu->addAction(manageAction);
    remoteConfigMenu->addAction(updateAction);
    remoteConfigMenu->addAction(autoUpdateAction);

    dashBoardMenu->addAction(clashxAction);
    dashBoardMenu->addAction(yacdAction);

    experimentalMenu->addAction(showCurrentProxyAction);
    experimentalMenu->addAction(useBuildInApiAction);
    experimentalMenu->addAction(setBenchmarkUrlAction);
    experimentalMenu->addAction(autoCloseConnectionAction);

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
    portsMenu->addAction(redirPortAction);
    portsMenu->addAction(apiPortAction);

    helpMenu->addMenu(portsMenu);

    trayIconMenu->addMenu(configMenu);
    trayIconMenu->addMenu(helpMenu);
    trayIconMenu->addAction(quitAction);

    QIcon icon = QIcon(":/icons/menu_icon@0,5x.png");

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
    showCurrentProxyAction->setCheckable(true);
    useBuildInApiAction->setCheckable(true);
    autoCloseConnectionAction->setCheckable(true);
    errorAction->setCheckable(true);
    warningAction->setCheckable(true);
    infoAction->setCheckable(true);
    debugAction->setCheckable(true);
    silentAction->setCheckable(true);
    clashxAction->setCheckable(true);
    yacdAction->setCheckable(true);
}

void SystemTray::updateInfo()
{
    ApiRequest::requestConfig();
    setConfigList();
    setTrayProxyMode();
    startAtLoginAction->setChecked(LaunchAtLogin::isAutoStart());
    allowLanConnectionAction->setChecked(ClashConfig::allowLan);
    setPortsMenu();
    setTrayLogLevel();
    setUiSelection();
}

void SystemTray::setTrayProxyMode()
{
    if (ClashConfig::mode == "Global") {
        proxyModeMenu->setTitle(tr("Proxy Mode (Global)"));
        globeAction->setChecked(true);
    } else if (ClashConfig::mode == "Rule") {
        proxyModeMenu->setTitle(tr("Proxy Mode (Rule)"));
        ruleAction->setChecked(true);
    } else if (ClashConfig::mode == "Direct") {
        proxyModeMenu->setTitle(tr("Proxy Mode (Direct)"));
        directAction->setChecked(true);
    }
}

void SystemTray::switchConfig(QAction *action)
{
    ConfigManager::selectConfigName = action->text();
    ApiRequest::requestConfigUpdate();
    action->setChecked(true);
    Settings::setConfig(ConfigManager::selectConfigName);
}

void SystemTray::setPortsMenu()
{
    httpPortAction->setText("Http Port:" + QString::number(ClashConfig::port));
    socksPortAction->setText("Socks Port:" + QString::number(ClashConfig::socketPort));
    redirPortAction->setText("Redir Port:" + QString::number(ClashConfig::redirPort));
    apiPortAction->setText("Api Port:" + ConfigManager::apiPort);
}

void SystemTray::setConfigList()
{
    QStringList configList = ConfigManager::getConfigFilesList();
    configListMenu->clear();
    for (int i=0; i<configList.size(); i++){
        QAction *action = new QAction(configList[i], configListGroup);
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
        ClashConfig::mode = "Global";
        proxyModeMenu->setTitle(tr("Proxy Mode (Global)"));
    } else if (action->text() == tr("Rule")) {
        ClashConfig::mode = "Rule";
        proxyModeMenu->setTitle(tr("Proxy Mode (Rule)"));
    } else if (action->text() == tr("Direct")) {
        ClashConfig::mode = "Direct";
        proxyModeMenu->setTitle(tr("Proxy Mode (Direct)"));
    }
    apirequest->updateOutBoundMode(ClashConfig::mode);
    action->setChecked(true);
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
    if (ConfigManager::windowNumber == 0) {
        mainwindow.show();
        mainwindow.raise();
        ConfigManager::windowNumber += 1;
    }
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
        ClashConfig::logLevel = "error";
    } else if (action->text() == tr("WARNING")) {
        apirequest->updateLogLevel("warning");
        ClashConfig::logLevel = "warning";
    } else if (action->text() == tr("INFO")) {
        apirequest->updateLogLevel("info");
        ClashConfig::logLevel = "info";
    } else if (action->text() == tr("DEBUG")) {
        apirequest->updateLogLevel("debug");
        ClashConfig::logLevel = "debug";
    } else if (action->text() == tr("SILENT")) {
        apirequest->updateLogLevel("silent");
        ClashConfig::logLevel = "silent";
    }
}

void SystemTray::setUiSelection()
{
    if (ConfigManager::selectDashBoard == tr("clashxdashboard")) {
        clashxAction->setChecked(true);
    } else if (ConfigManager::selectDashBoard == tr("yacddashboard")) {
        yacdAction->setChecked(true);
    }
}

void SystemTray::switchUiDashboard(QAction *action)
{
    if (action->text() == tr("ClashX")) {
        Settings::setDashboard("clashx");
    } else if (action->text() == tr("Yacd")) {
        Settings::setDashboard("yacd");
    }
    showSwitchUiNotification();
}

void SystemTray::setBenchmarkUrl()
{
    bool ok;
    QString text = QInputDialog::getText(0, "ShadowClash","Benchmark", QLineEdit::Normal, ConfigManager::benchMarkUrl, &ok);
    if (ok && !text.isEmpty()) {
        ConfigManager::benchMarkUrl = text;
    }
}

void SystemTray::showLog()
{
    QDesktopServices::openUrl(QUrl("file://" + Paths::logFilePath, QUrl::TolerantMode));
}

void SystemTray::showRemoteConfigWindow()
{
    RemoteConfigWindow *remoteconfigWindow = new RemoteConfigWindow();
    remoteconfigWindow->exec();
}

void SystemTray::showSwitchUiNotification()
{
    QMessageBox alert;
    alert.setWindowTitle("ShadowClash");
    alert.setText(tr("You have to restart this application in order to change dashboard"));
    alert.addButton(tr("OK"), QMessageBox::YesRole);
    alert.exec();
}
