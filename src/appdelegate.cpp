//
//  appdelegate.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2018/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "apirequest.h"
#include "appdelegate.h"
#include "configmanager.h"
#include "enhancemodemanager.h"
#include "logger.h"
#include "notificationcenter.h"
#include "proxyconfighelpermanager.h"
#include "runguard.h"
#include "shadowclash.h"

#if defined (Q_OS_MAC)
#include <CoreServices/CoreServices.h>
#include <CoreFoundation/CoreFoundation.h>
#endif

#include <QApplication>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QUrl>

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
#if defined (Q_OS_WIN)
    QString path = QCoreApplication::applicationDirPath() + "/clashxdashboard";
#elif defined (Q_OS_MAC)
    CFURLRef url = (CFURLRef)CFAutorelease((CFURLRef)CFBundleCopyBundleURL(CFBundleGetMainBundle()));
    QString path = QUrl::fromCFURL(url).path() + "Contents/Resources/clashxdashboard";
#elif defined (Q_OS_LINUX)
    QString path = QCoreApplication::applicationDirPath() + "/clashxdashboard";
#endif
    setUIPath(path.toLocal8Bit().data());

    Logger::log("Trying start proxy","debug");
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
    ApiRequest::requestConfigUpdate();
    syncConfig();
    // check config vaild via api
    ConfigManager::checkFinalRuleAndShowAlert();
}

void AppDelegate::syncConfig()
{
    ApiRequest::requestConfig();
}
