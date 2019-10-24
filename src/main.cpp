#include "configmanager.h"
#include "systemtray.h"
#include "fvupdater.h"
#include "mainwindow.h"
#include "runguard.h"
#include "appdelegate.h"
#include "clashresourcemanager.h"
#include "proxyconfighelpermanager.h"
#include "appversionutil.h"
#include "enhancemodemanager.h"

#include <QApplication>
#include <QMessageBox>
#include <QObject>
#include <QDebug>

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
    ProxyConfigHelperManager::install();
    EnhanceModeManager::install();
    ClashResourceManager::check();
    ConfigManager::copySampleConfigIfNeed();

    // start proxy
    AppDelegate::updateConfig();

    // update Systemtray's info after proxy start
    systemtray->setTrayProxyMode();
    systemtray->setPortsMenu();

    // start watch config file change
    ConfigManager::watchConfigFile("config");

    // setup app settings
    AppVersionUtil::init();

    MainWindow w;
    w.show();
    return a.exec();
}
