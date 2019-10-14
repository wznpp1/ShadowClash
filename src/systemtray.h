#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include "aboutwindow.h"
#include "apirequest.h"
#include "notificationcenter.h"
#include "mainwindow.h"
#include "launchatlogin.h"

#include <QSystemTrayIcon>
#include <QLabel>
#include <QMenu>

class SystemTray: public QObject
{
public:
    SystemTray();
    void createActions();
    void createShortCuts();
    void createTrayIcon();
    void copyExportCommand();
    void speedTest();
    void showWindow();
    void AllowFromLan();
    void openConfigFolder();
    void pushAboutWindow();
    bool isSpeedTesting;
    NotificationCenter *notificationCenter;
    ApiRequest *apirequest;
    LaunchAtLogin *launchAtLogin;
    QSystemTrayIcon *trayIcon;

private:
    QAction *proxyModeAction;
    QAction *setAsSystemProxyAction;
    QAction *copyExportCommandAction;
    // Separator
    QAction *startAtLoginAction;
    QAction *showNetworkIndicatorAction;
    QAction *allowLanConnectionAction;
    // Separator
    QAction *speedTestAction;
    QAction *dashBoardAction;
    // Config Menu
    QAction *openConfigFolderAction;
    QAction *reloadConfigAction;
    // Help Menu
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *checkUpdateAction;
    QAction *showLogAction;
    QAction *quitAction;

    QAction *httpPortAction;
    QAction *socksPortAction;
    QAction *apiPortAction;

    QMenu *trayIconMenu;
    QMenu *configMenu;
    QMenu *helpMenu;
    QMenu *portsMenu;
};

#endif // SYSTEMTRAY_H
