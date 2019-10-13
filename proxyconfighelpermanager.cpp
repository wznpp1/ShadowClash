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

void ProxyConfigHelperManager::showInstallHelperAlert()
{
    QMessageBox alert;
    alert.setWindowTitle("ShadowCoel");
    alert.setText("ShadowCoel needs to install a small tool to ~/.config/clash with administrator privileges to set system proxy quickly.\nOtherwise you need to type in the administrator password every time you change system proxy through ShadowCoel.");
    alert.addButton(tr("Install"), QMessageBox::YesRole);
    alert.addButton(tr("Quit"), QMessageBox::NoRole);
    alert.exec();
}

void ProxyConfigHelperManager::showCreateConfigDirFailAlert()
{
    QMessageBox alert;
    alert.setWindowTitle("ShadowCoel");
    alert.setText("ShadowCoel fail to create ~/.config/clash folder. Please check privileges or manually create folder and restart ShadowCoel.");
    alert.addButton(tr("Quit"), QMessageBox::NoRole);
    alert.exec();
}
