#include "aboutwindow.h"
#include "fvupdater.h"
#include "mainwindow.h"
#include "notificationcenter.h"
#include "paths.h"
#include "systemtray.h"

#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QKeySequence>
#include <QMenu>
#include <QUrl>

SystemTray::SystemTray()
{
}

void SystemTray::createActions()
{
    proxyModeAction = new QAction("Proxy Mode");
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
    connect(copyExportCommandAction, &QAction::triggered, this, &SystemTray::copyExportCommand);
    connect(speedTestAction, &QAction::triggered, this, &SystemTray::speedTest);
    connect(dashBoardAction, &QAction::triggered, this, &SystemTray::showWindow);
    connect(openConfigFolderAction, &QAction::triggered, this, &SystemTray::openConfigFolder);
    connect(aboutAction, &QAction::triggered, this, &SystemTray::pushAboutWindow);
    connect(aboutQtAction, &QAction::triggered, QApplication::aboutQt);
    connect(checkUpdateAction, &QAction::triggered, FvUpdater::sharedUpdater(), &FvUpdater::CheckForUpdatesNotSilent);
    connect(quitAction, &QAction::triggered, &QCoreApplication::quit);
}

void SystemTray::createShortCuts()
{
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
    configMenu = new QMenu(tr("Config"));
    helpMenu = new QMenu(tr("Help"));
    portsMenu = new QMenu(tr("Ports"));

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

    QIcon icon = QIcon(":/resources/icons/menu_icon.png");

#if defined(Q_OS_MACOS) || defined(Q_OS_MAC)
    icon.setIsMask(true);
#endif

    trayIcon = new QSystemTrayIcon(icon);
    trayIcon->setContextMenu(trayIconMenu);
}

void SystemTray::copyExportCommand()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText("export https_proxy=http://127.0.0.1:%1;export http_proxy=http://127.0.0.1:%1;export all_proxy=socks5://127.0.0.1:%2");
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
}

void SystemTray::showWindow()
{
    MainWindow *mainwindow;
    mainwindow->show();
}

void SystemTray::openConfigFolder()
{
    QDesktopServices::openUrl(QUrl(Paths::configFolderPath, QUrl::TolerantMode));
}

void SystemTray::pushAboutWindow()
{
    AboutWindow *view = new AboutWindow();
    view->exec();
}
