#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include "aboutwindow.h"
#include "notificationcenter.h"

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
    void openConfigFolder();
    void pushAboutWindow();
    bool isSpeedTesting;
    NotificationCenter *notificationCenter;
    QSystemTrayIcon *trayIcon;

private:
    QAction *proxyModeAction;
    QAction *setAsSystemProxyAction;
    QAction *copyExportCommandAction;
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
