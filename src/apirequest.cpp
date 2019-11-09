#include "apirequest.h"
#include "clashconfig.h"
#include "configmanager.h"
#include "notificationcenter.h"
#include "paths.h"
#include "shadowclash.h"

#include <QDir>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QUrl>

QNetworkReply* ApiRequest::req(QString url, QString method, QByteArray data) {
    QByteArray version = ("ShadowClash/" + ConfigManager::version).toUtf8();
    QByteArray request_method = method.toUtf8();
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request(ConfigManager::apiUrl + url);
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("User-Agent", version);
    if (ConfigManager::apiSecret.length() > 0) {
        request.setRawHeader("Authorization", QString("Bearer %1").arg(ConfigManager::apiSecret).toUtf8());
    }
    QNetworkReply* reply = manager->sendCustomRequest(request, request_method, data);
    // Come from https://stackoverflow.com/a/58403924/11802671
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    return reply;
}

void ApiRequest::requestConfig()
{
    // DEV MODE: Use API
    if (!ConfigManager::buildInApiMode) {
        QNetworkReply *reply = req("/configs", "GET", "");
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj = jsonResponse.object();
        if (!obj.isEmpty()) {
            ClashConfig::port = obj["port"].toInt();
            ClashConfig::socketPort = obj["socks-port"].toInt();
            ClashConfig::allowLan = obj["allow-lan"].toBool();
            ClashConfig::mode = obj["mode"].toString();
            ClashConfig::logLevel = obj["log-level"].toString();
        } else {
            NotificationCenter::postNotifiacation("Error", "Get clash config failed. Try Fix your config file then reload config or restart ShadowClah.");
        }
        reply->deleteLater();
        return;
    }

    // NORMAL MODE: Use internal api
    char* data = clashGetConfigs();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(data);
    QJsonObject obj = jsonResponse.object();
    if (!obj.isEmpty()) {
        ClashConfig::port = obj["port"].toInt();
        ClashConfig::socketPort = obj["socks-port"].toInt();
        ClashConfig::allowLan = obj["allow-lan"].toBool();
        ClashConfig::mode = obj["mode"].toString();
        ClashConfig::logLevel = obj["log-level"].toString();
    } else  {
        NotificationCenter::postNotifiacation("Error", "Get clash config failed. Try Fix your config file then reload config or restart ShadowClah.");
    }

}

void ApiRequest::requestConfigUpdate(bool showNotification)
{
    QString filePath = Paths::configFolderPath + ConfigManager::selectConfigName + ".yaml";

    // DEV MODE: Use API
    if (!ConfigManager::buildInApiMode) {
        QByteArray data = (QString("{\"Path\":\"%1\"}").arg(filePath)).toUtf8();
        QNetworkReply *reply = req("/configs", "PUT", data);
        if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 204) {
            if (showNotification) {
                NotificationCenter::postNotifiacation("Reload Config Succeed","Succees");
            }
        } else {
            if (showNotification) {
                QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
                QJsonObject obj = jsonResponse.object();
                NotificationCenter::postNotifiacation("Reload Config Fail", obj["message"].toString());
            }
        }
        reply->deleteLater();
        return;
    }

    // NORMAL MODE: Use internal api
    char* result = clashUpdateConfig(filePath.toLatin1().data());
    if (QString::fromUtf8(result) == "success") {
        if (showNotification) {
            NotificationCenter::postNotifiacation("Reload Config Succeed","Succees");
        }
    } else {
        if (showNotification) {
            NotificationCenter::postNotifiacation("Reload Config Fail",QString::fromUtf8(result));
        }
    }

}

void ApiRequest::updateOutBoundMode(QString mode)
{
    QByteArray data = (QString("{\"mode\":\"%1\"}").arg(mode)).toUtf8();
    req("/configs",
        "PATCH",
        data);
}

void ApiRequest::updateLogLevel(QString logLevel)
{
    QByteArray data = (QString("{\"log-level\":\"%1\"}").arg(logLevel)).toUtf8();
    req("/configs",
        "PATCH",
        data);
}

void ApiRequest::requestProxyGroupList()
{
    if (!ConfigManager::buildInApiMode) {
        QNetworkReply *reply = req("/proxies",
            "GET",
            "");
    }

    QJsonDocument jsonResponse = QJsonDocument::fromJson(clashGetProxies());
}

void ApiRequest::updateAllowLan(bool allow)
{
    QByteArray data = (QString("{\"allow-lan\":%1}").arg(QVariant(allow).toString())).toUtf8();
    req("/configs",
        "PATCH",
        data);
}

int ApiRequest::getProxyDelay(QString proxyName)
{
    QString proxyNameEncoded = QUrl::toPercentEncoding(proxyName);
    QNetworkReply *reply = req(QString("/proxies/%1/delay").arg(proxyNameEncoded),
        "GET",
        "{\"timeout\":5000,\"url\":\"http://www.gstatic.com/generate_204\"");
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = jsonResponse.object();
    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 504) {
        return obj["delay"].toInt();
    } else {
        return -1;
    }

}

QJsonObject ApiRequest::getRules()
{
    QNetworkReply *reply = req("/rules",
        "GET",
        "");
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = jsonResponse.object();
    return obj;
}

/*
void ApiRequest::requestTrafficInfo()
{
    QByteArray version = ("ShadowClash/" + ConfigManager::version).toUtf8();
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request(ConfigManager::apiUrl + "/traffic");
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("User-Agent", version);
    if (ConfigManager::apiSecret.length() > 0) {
        request.setRawHeader("Authorization", QString("Bearer %1").arg(ConfigManager::apiSecret).toUtf8());
    }
    QNetworkReply* reply = manager->sendCustomRequest(request, "GET", "");
    reply->read();
}*/
