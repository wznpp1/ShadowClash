#include "clashresourcemanager.h"
#include "paths.h"
#include "appversionutil.h"

#include <QDir>
#include <QString>
#include <QFile>
#include <QMessageBox>

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
            dir.mkdir(".");
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

void ClashResourceManager::showCreateConfigDirFailAlert()
{
    QMessageBox alert;
    alert.setWindowTitle("ShadowClash");
    alert.setText("ShadowClash fail to create ~/.config/clash folder. Please check privileges or manually create folder and restart ShadowClash.");
    alert.addButton(tr("OK"), QMessageBox::YesRole);
    alert.exec();
}
