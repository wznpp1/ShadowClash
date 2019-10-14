#include "paths.h"
#include "proxyconfighelpermanager.h"

#include <QMessageBox>
#include <QProcess>

ProxyConfigHelperManager::ProxyConfigHelperManager()
{

}
void ProxyConfigHelperManager::checkMMDB()
{
    QString path = Paths::configFolderPath + "/Country.mmdb";
}

void ProxyConfigHelperManager::setUpSystemProxy(int port, int socksPort)
{
    QProcess *task = new QProcess;
    QStringList param;
#ifdef Q_OS_WIN
    if (port && socksPort) {
        param << "-p" << QString("127.0.0.1:") + QString(socksPort);
    } else {
        param << "-d";
    }
    task->start(QString(Paths::configFolderPath) + "/ProxyConfig.exe", param);
    task->waitForFinished();

#elif defined Q_OS_MAC
    if (port && socksPort) {
        param << QString(port) << QString(socksPort) << "enable";
    } else {
        param << "0" << "0" << "disable";
    }
    task->start(QString(Paths::configFolderPath) + "/ProxyConfig", param);
    task->waitForFinished();
#endif
}

bool ProxyConfigHelperManager::showInstallHelperAlert()
{
    QMessageBox alert;
    alert.setWindowTitle("ShadowClash");
    alert.setText("ShadowClash needs to install a helper tool with administrator privileges to set system proxy quickly.");
    alert.addButton(tr("Install"), QMessageBox::YesRole);
    alert.addButton(tr("Quit"), QMessageBox::NoRole);
    if (alert.exec() == QMessageBox::Yes) {
        return true;
    } else {
        return false;
    }
}

void ProxyConfigHelperManager::showCreateConfigDirFailAlert()
{
    QMessageBox alert;
    alert.setWindowTitle("ShadowClash");
    alert.setText("ShadowClash fail to create ~/.config/clash folder. Please check privileges or manually create folder and restart ShadowClash.");
    alert.addButton(tr("Quit"), QMessageBox::NoRole);
    alert.exec();
}
