//
//  remoteconfigmanager.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2019/12/4.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "remoteconfigmanager.h"

#include "configmanager.h"
#include "shadowclash.h"
#include "logger.h"
#include "paths.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QFile>
#include <QMessageBox>

QString RemoteConfigManager::getRemoteConfigData(QString url)
{
    QByteArray version = ("ShadowClash/" + ConfigManager::version).toUtf8();
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", version);
    QNetworkReply* reply = manager->sendCustomRequest(request, "GET", "");
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
        QString data = reply->readAll();
        reply->deleteLater();
        return data;
    } else {
        QString data = "";
        reply->deleteLater();
        return data;
    }
}

bool RemoteConfigManager::updateConfig(QString url, QString configName)
{
    QString configString = getRemoteConfigData(url);

    // otherwise if false this still execute
    if (configString.length() == 0) {
        // Download Failed
        QMessageBox alert;
        alert.setWindowTitle("ShadowClash");
        alert.setText(tr("Download fail"));
        alert.addButton(tr("OK"), QMessageBox::YesRole);
        alert.exec();
        Logger::log(tr("Download fail"), "error");
        return false;
    }

    QString verifyRes = verifyConfig(configString);

    if (verifyRes != "") {
        // Verify Failed
        QMessageBox alert;
        alert.setWindowTitle("ShadowClash");
        alert.setText(tr("Remote Config Format Error"));
        alert.addButton(tr("OK"), QMessageBox::YesRole);
        alert.exec();
        Logger::log(tr("Remote Config Format Error"), "error");
        return false;

    }

    QString savePath = Paths::configFolderPath + configName + ".yaml";

    try {
        if (QFile::exists(savePath)) {
            QFile::remove(savePath);
        }
        QFile file(savePath);
        file.open(QIODevice::WriteOnly);
        file.write(configString.toUtf8());
        file.close();
    } catch (...) {
        return false;
    }

    return true;
}

QString RemoteConfigManager::verifyConfig(QString string)
{
    QString res = verifyClashConfig(string.toLocal8Bit().data());
    if (res == "success") {
        return "";
    } else {
        return res;
    }
}
