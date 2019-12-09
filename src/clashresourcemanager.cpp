//
//  clashresourcemanager.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2018/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "appversionutil.h"
#include "clashresourcemanager.h"
#include "paths.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include <QString>

void ClashResourceManager::check()
{
    checkConfigDir();
    checkMMDB();
    upgardeYmlExtensionName();
}

void ClashResourceManager::checkConfigDir()
{
    QDir dir(Paths::configFolderPath);
    if (!dir.exists()) {
        try {
            dir.mkpath(".");
        } catch (...) {
            showCreateConfigDirFailAlert();
        }
    }
}

void ClashResourceManager::checkMMDB()
{
    QString path = Paths::configFolderPath + "Country.mmdb";

    if (QFile::exists(path)) {
        if (AppVersionUtil::hasVersionChanged() || AppVersionUtil::isFirstLaunch()) {
            QFile::remove(path);
        }
    }

    if (!QFile::exists(path)) {

        QFile::copy(":/Country.mmdb", path);
    }
}

void ClashResourceManager::upgardeYmlExtensionName()
{
    QDir dir(Paths::configFolderPath);
    QFileInfoList list = dir.entryInfoList();
    for (int i=0;i<list.size();++i) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.suffix() == "yml") {
            QFile::rename(fileInfo.filePath(), fileInfo.filePath().split(".")[0] + ".yaml");
        }
    }
}

void ClashResourceManager::installHelper()
{
    QString dir = Paths::configFolderPath;
    QProcess *task = new QProcess;
    QStringList param;

    if (!QFile::exists(dir + "install_helper.sh")) {
        QFile::copy(":/install_helper.sh",dir + "install_helper.sh");
        if (showInstallHelperAlert()) {
            QString script = QString("do shell script \"bash %1 \\\"%2\\\"\" with administrator privileges").arg(dir + "install_helper.sh").arg(dir);
            param << "-l" << "AppleScript";
            task->start("/usr/bin/osascript", param);
            task->write(script.toUtf8());
            task->closeWriteChannel();
            task->waitForFinished();
        }
    }
}
void ClashResourceManager::showCreateConfigDirFailAlert()
{
    QMessageBox alert;
    alert.setWindowTitle("ShadowClash");
    alert.setText(tr("ShadowClash fail to create ~/.config/clash folder. Please check privileges or manually create folder and restart ShadowClash."));
    alert.addButton(tr("OK"), QMessageBox::YesRole);
    alert.exec();
}

bool ClashResourceManager::showInstallHelperAlert()
{
    QMessageBox alert;
    alert.setWindowTitle("ShadowClash");
    alert.setText(tr("ShadowClash needs to install a helper tool with administrator privileges to set system proxy and enchance mode quickly."));
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
