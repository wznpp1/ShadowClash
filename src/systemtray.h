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
Q_OBJECT
public:
    SystemTray();
    void createActions();
    void createShortCuts();
    void createTrayIcon();
    void setCheckable();
    void setTrayProxyMode();
    void setPortsMenu();
    void setSystemProxy();
    void copyExportCommand();
    void setEnhanceMode();
    void speedTest();
    void showWindow();
    void setupAutoStart();
    void allowFromLan();
    void openConfigFolder();
    void pushAboutWindow();
    bool isSpeedTesting;
    NotificationCenter *notificationCenter;
    ApiRequest *apirequest;
    LaunchAtLogin *launchAtLogin;
    QSystemTrayIcon *trayIcon;

public slots:
    void switchProxyMode(QAction *action);

private:

    QActionGroup *proxyModeGroup;
    QActionGroup *dashBoardGroup;

    QAction *globeAction;
    QAction *ruleAction;
    QAction *directAction;
    QAction *setAsSystemProxyAction;
    QAction *copyExportCommandAction;
    QAction *enhanceModeAction;
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
    QAction *clashxAction;
    QAction *yacdAction;
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
    QMenu *proxyModeMenu;
    QMenu *configMenu;
    QMenu *dashBoardMenu;
    QMenu *helpMenu;
    QMenu *portsMenu;
};

#endif // SYSTEMTRAY_H
