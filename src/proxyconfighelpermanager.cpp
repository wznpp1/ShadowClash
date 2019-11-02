//
//  proxyconfighelpermanager.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2019/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "paths.h"
#include "proxyconfighelpermanager.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QProcess>

void ProxyConfigHelperManager::install()
{
    QString dir = Paths::configFolderPath;
    QProcess *task = new QProcess;
    QStringList param;

#ifdef Q_OS_WIN
    if (!QFile::exists(dir + "ProxyConfig.exe")) {
        QFile::copy(":/ProxyConfig.exe",dir + "ProxyConfig.exe");
    }

#elif defined(Q_OS_MAC)
    if (!QFile::exists(dir + "ProxyConfig")) {
        QFile::copy(":/ProxyConfig",dir + "ProxyConfig");
    }

    if (!QFile::exists(dir + "install_proxy_helper.sh")) {
        QFile::copy(":/install_proxy_helper.sh",dir + "install_proxy_helper.sh");
        if (showInstallHelperAlert()) {
            QString script = QString("do shell script \"bash %1 \\\"%2\\\"\" with administrator privileges").arg(dir + "install_proxy_helper.sh").arg(dir);
            param << "-l" << "AppleScript";
            task->start("/usr/bin/osascript", param);
            task->write(script.toUtf8());
            task->closeWriteChannel();
            task->waitForFinished();
        }
    }

#elif defined(Q_OS_LINUX)
    if (!QFile::exists(dir + "ProxyConfig")) {
        QFile::copy(":/ProxyConfigLinux",dir);
        QFile::rename(dir + "ProxyConfigLinux", dir + "ProxyConfig");
    }
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
    QList<QAbstractButton*> alertButtons = alert.buttons();
    alert.exec();
    if (alertButtons.at(0) == alert.clickedButton()) {
        return true;
    } else {
        return false;
    }
}
