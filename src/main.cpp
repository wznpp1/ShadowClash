#include "configmanager.h"
#include "fvupdater.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName("ShadowCoel");
    QApplication::setApplicationVersion(ConfigManager::version);
    QApplication::setOrganizationName("coelwu");
    QApplication::setOrganizationDomain("com.coelwu");

    FvUpdater::sharedUpdater()->SetFeedURL("https://raw.github.com/pypt/fervor/master/sample/Appcast.xml");
    FvUpdater::sharedUpdater()->CheckForUpdatesSilent();

    MainWindow w;
    w.show();
    return a.exec();
}
