#include "configmanager.h"
#include "systemtray.h"
#include "fvupdater.h"
#include "mainwindow.h"
#include "runguard.h"

#include <QApplication>
#include <QMessageBox>
#include <QObject>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RunGuard guard("ShadowClash");

    QApplication::setApplicationName("ShadowClash");
    QApplication::setApplicationVersion(ConfigManager::version);
    QApplication::setOrganizationName("coelwu");
    QApplication::setOrganizationDomain("com.coelwu");

    if (!guard.isSingleInstance()) {
        QMessageBox alert;
        alert.setWindowTitle("ShadowClash");
        alert.setText(QObject::tr("Another instance of ShadowClash is already running."));
        alert.exec();
        return -1;
    }

    SystemTray *systemtray = new SystemTray;
    systemtray->createActions();
    systemtray->createShortCuts();
    systemtray->createTrayIcon();
    systemtray->trayIcon->show();

    FvUpdater::sharedUpdater()->SetFeedURL("https://raw.github.com/pypt/fervor/master/sample/Appcast.xml");
    FvUpdater::sharedUpdater()->CheckForUpdatesSilent();

    MainWindow w;
    w.show();
    return a.exec();
}
