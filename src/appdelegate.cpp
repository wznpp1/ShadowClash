//
//  appdelegate.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2018/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "appdelegate.h"
#include "shadowclash.h"
#include "configmanager.h"
#include "apirequest.h"
#include "runguard.h"
#include "proxyconfighelpermanager.h"
#include "notificationcenter.h"
#include "enhancemodemanager.h"

#include <QDebug>
#include <CoreServices/CoreServices.h>
#include <CoreFoundation/CoreFoundation.h>
#include <QCoreApplication>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QApplication>

void AppDelegate::applicationWillTerminate()
{
    // unset System Proxy
    if (ConfigManager::proxyPortAutoSet) {
        ProxyConfigHelperManager::setUpSystemProxy(0,0);
    }

    // stop tun2socks
    if (ConfigManager::enhanceMode) {
        EnhanceModeManager::stopTun2socks();
    }

    // quit the app
    QCoreApplication::quit();
}

void AppDelegate::startProxy()
{
    // setup ui config first
    CFURLRef url = (CFURLRef)CFAutorelease((CFURLRef)CFBundleCopyBundleURL(CFBundleGetMainBundle()));
    QString path = QUrl::fromCFURL(url).path() + "Contents/Resources/clashxdashboard";
    setUIPath(path.toLocal8Bit().data());

    char* string = run(1);
    QJsonDocument jsonResponse = QJsonDocument::fromJson(string);
    QJsonObject obj = jsonResponse.object();
    if (!obj.isEmpty()) {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(string);
        QJsonObject obj = jsonResponse.object();
        ConfigManager::apiPort = obj["externalController"].toString().split(":")[1];
        ConfigManager::apiSecret = obj["secret"].toString();
        ConfigManager::apiUrl = QString("http://127.0.0.1:") + ConfigManager::apiPort;
    } else {
        NotificationCenter::postConfigErrorNotice(QString::fromUtf8(string));
    }
}

void AppDelegate::updateConfig()
{
    startProxy();
    ApiRequest::requestConfigUpdate(false);
    syncConfig();
    // check config vaild via api
    ConfigManager::checkFinalRuleAndShowAlert();
}

void AppDelegate::syncConfig()
{
    ApiRequest::requestConfig();
}
