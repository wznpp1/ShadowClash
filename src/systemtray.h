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
    void createActions();
    void createShortCuts();
    void createTrayIcon();
    void setCheckable();
    void updateInfo();
    void setTrayProxyMode();
    void setPortsMenu();
    void setConfigList();
    void setTrayLogLevel();
    void setSystemProxy();
    void copyExportCommand();
    void setEnhanceMode();
    void speedTest();
    void showWindow();
    void setupAutoStart();
    void allowFromLan();
    void openConfigFolder();
    void requestConfigUpdate();
    void pushAboutWindow();
    bool isSpeedTesting;
    NotificationCenter *notificationCenter;
    ApiRequest *apirequest;
    LaunchAtLogin *launchAtLogin;
    QSystemTrayIcon *trayIcon;

public slots:
    void switchProxyMode(QAction *action);
    void switchConfig(QAction *action);
    void setLogLevel(QAction *action);

private:

    QActionGroup *proxyModeGroup;
    QActionGroup *dashBoardGroup;
    QActionGroup *configListGroup;
    QActionGroup *logGroup;

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
    QAction *showCurrentProxyAction;
    QAction *useBuildInApiAction;
    QAction *setBenchmarkUrlAction;
    // Help Menu
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *checkUpdateAction;
    QAction *errorAction;
    QAction *warningAction;
    QAction *infoAction;
    QAction *debugAction;
    QAction *silentAction;
    QAction *showLogAction;
    QAction *quitAction;

    QAction *httpPortAction;
    QAction *socksPortAction;
    QAction *apiPortAction;

    QMenu *trayIconMenu;
    QMenu *logMenu;
    QMenu *proxyModeMenu;
    QMenu *configMenu;
    QMenu *dashBoardMenu;
    QMenu *experimentalMenu;
    QMenu *helpMenu;
    QMenu *configListMenu;
    QMenu *portsMenu;
};

#endif // SYSTEMTRAY_H
