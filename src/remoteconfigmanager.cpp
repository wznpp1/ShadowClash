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

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QFile>

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
    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200) {
        return reply->readAll();
    } else {
        return "error";
    }
}

QString RemoteConfigManager::updateConfig()
{
    /*
    QString configString = getRemoteConfigData();
    if (configString == "error") {
        // Download Failed
    }

    QString verifyRes = verifyConfig(configString);
    if (verifyRes != "success") {
        // Verify Failed
    }

    if (QFile::exists()) {
        QFile::remove();

    }
    */
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
