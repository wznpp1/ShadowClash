#include "paths.h"
#include "proxyconfighelpermanager.h"

#include <QMessageBox>
#include <QProcess>
#include <QFile>
#include <QDir>
#include <QDebug>

ProxyConfigHelperManager::ProxyConfigHelperManager()
{

}

void ProxyConfigHelperManager::install()
{
    QString dir = Paths::configFolderPath;

#ifdef Q_OS_WIN
    QFile::copy(":/ProxyConfig.exe",Paths::configFolderPath);

#elif defined(Q_OS_MAC)
    QFile::copy(":/ProxyConfig",Paths::configFolderPath);

#elif defined(Q_OS_LINUX)
    QFile::copy(":/ProxyConfigLinux",Paths::configFolderPath);
    QFile::rename(dir + "ProxyConfigLinux", dir + "ProxyConfig");
#endif

    QProcess *task = new QProcess;
    QStringList param;
    task->setWorkingDirectory(Paths::configFolderPath);
#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
    param << "chown" << "root:admin" << "\"ProxyConfig\"";
    task->start("sudo", param);
    task->waitForFinished();
    param.clear();
    param << "chown" << "+s" << "\"ProxyConfig\"";
    task->start("sudo", param);
    task->waitForFinished();
#endif

}

void ProxyConfigHelperManager::setUpSystemProxy(int port, int socksPort)
{
    QProcess *task = new QProcess;
    QStringList param;
#ifdef Q_OS_WIN
    if (port && socksPort) {
        param << "-p" << QString("127.0.0.1:") + QString::number(socksPort);
    } else {
        param << "-d";
    }
    task->start(QString(Paths::configFolderPath) + "ProxyConfig.exe", param);
    task->waitForFinished();

#elif defined Q_OS_MAC
    if (port && socksPort) {
        param << QString::number(port) << QString::number(socksPort) << "enable";
    } else {
        param << "0" << "0" << "disable";
    }
    task->start(QString(Paths::configFolderPath) + "ProxyConfig", param);
    qDebug() << port;
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
