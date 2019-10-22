#include "aboutwindow.h"
#include "apirequest.h"
#include "configmanager.h"
#include "fvupdater.h"
#include "mainwindow.h"
#include "notificationcenter.h"
#include "paths.h"
#include "systemtray.h"
#include "launchatlogin.h"
#include "clashconfig.h"
#include "proxyconfighelpermanager.h"

#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QClipboard>
#include <QCoreApplication>
#include <QSettings>
#include <QDesktopServices>
#include <QKeySequence>
#include <QMenu>
#include <QUrl>
#include <QDebug>

SystemTray::SystemTray()
{
}

void SystemTray::createActions()
{
    proxyModeGroup = new QActionGroup(this);
    proxyModeGroup->setExclusive(true);

    globeAction = new QAction(tr("Global"), proxyModeGroup);
    ruleAction = new QAction(tr("Rule"), proxyModeGroup);
    directAction = new QAction(tr("Direct"), proxyModeGroup);

    setAsSystemProxyAction = new QAction(tr("Set as system proxy"));
    copyExportCommandAction = new QAction(tr("Copy export command"));

    startAtLoginAction = new QAction(tr("Start at login"));
    showNetworkIndicatorAction = new QAction(tr("Show network indicator"));
    allowLanConnectionAction = new QAction(tr("Allow connect from Lan"));
    // Separator
    dashBoardAction = new QAction(tr("DashBoard"));
    speedTestAction = new QAction(tr("SpeedTest"));
    // Config Menu
    openConfigFolderAction = new QAction(tr("Open config Folder"));
    reloadConfigAction = new QAction(tr("Reload config"));

    dashBoardGroup = new QActionGroup(this);
    dashBoardGroup->setExclusive(true);

    clashxAction = new QAction(tr("ClashX"));
    yacdAction = new QAction(tr("Yacd"));
    // Help Menu
    aboutAction = new QAction(tr("About"));
    aboutQtAction = new QAction(tr("About Qt"));
    checkUpdateAction = new QAction(tr("Check Update"));
    showLogAction = new QAction(tr("Show Log"));
    // Ports Menu
    httpPortAction = new QAction("Http Port:");
    socksPortAction = new QAction("Socks Port:");
    apiPortAction =  new QAction("Api Port:");

    quitAction = new QAction("Quit");

    connect(proxyModeGroup, SIGNAL(triggered(QAction*)), this, SLOT(switchProxyMode(QAction*)));
    connect(setAsSystemProxyAction, &QAction::triggered, this, &SystemTray::setSystemProxy);
    connect(copyExportCommandAction, &QAction::triggered, this, &SystemTray::copyExportCommand);
    connect(speedTestAction, &QAction::triggered, this, &SystemTray::speedTest);
    connect(dashBoardAction, &QAction::triggered, this, &SystemTray::showWindow);
    connect(startAtLoginAction, &QAction::triggered, this, &SystemTray::setupAutoStart);
    connect(allowLanConnectionAction, &QAction::triggered, this, &SystemTray::allowFromLan);
    connect(openConfigFolderAction, &QAction::triggered, this, &SystemTray::openConfigFolder);
    connect(aboutAction, &QAction::triggered, this, &SystemTray::pushAboutWindow);
    connect(aboutQtAction, &QAction::triggered, QApplication::aboutQt);
    connect(checkUpdateAction, &QAction::triggered, FvUpdater::sharedUpdater(), &FvUpdater::CheckForUpdatesNotSilent);
    connect(quitAction, &QAction::triggered, &QCoreApplication::quit);
}

void SystemTray::createShortCuts()
{
    globeAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_G));
    ruleAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_R));
    directAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_D));

    setAsSystemProxyAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    copyExportCommandAction->setShortcuts(QKeySequence::Copy);

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
    helpMenu = new QMenu(tr("Help"));
    portsMenu = new QMenu(tr("Ports"));

    proxyModeMenu->addAction(globeAction);
    proxyModeMenu->addAction(ruleAction);
    proxyModeMenu->addAction(directAction);

    trayIconMenu->addMenu(proxyModeMenu);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(setAsSystemProxyAction);
    trayIconMenu->addAction(copyExportCommandAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(startAtLoginAction);
    trayIconMenu->addAction(showNetworkIndicatorAction);
    trayIconMenu->addAction(allowLanConnectionAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(dashBoardAction);
    trayIconMenu->addAction(speedTestAction);
    trayIconMenu->addSeparator();

    configMenu->addAction(openConfigFolderAction);
    configMenu->addAction(reloadConfigAction);
    configMenu->addMenu(dashBoardMenu);

    dashBoardMenu->addAction(clashxAction);
    dashBoardMenu->addAction(yacdAction);

    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
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
}

void SystemTray::setCheckable()
{
    globeAction->setCheckable(true);
    ruleAction->setCheckable(true);
    directAction->setCheckable(true);
    setAsSystemProxyAction->setCheckable(true);
    startAtLoginAction->setCheckable(true);
    showNetworkIndicatorAction->setCheckable(true);
    allowLanConnectionAction->setCheckable(true);
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

void SystemTray::pushAboutWindow()
{
    AboutWindow *view = new AboutWindow();
    view->exec();
}
