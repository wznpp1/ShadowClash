#include "apirequest.h"
#include "configmanager.h"
#include "paths.h"
#include "notificationcenter.h"

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include "clashconfig.h"

#include <QUrl>

QNetworkReply* ApiRequest::req(QString url, QString method, QByteArray data) {
    QByteArray version = ("ShadowClash/" + ConfigManager::version).toUtf8();
    QByteArray request_method = method.toUtf8();
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request(ConfigManager::apiUrl + url);
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("User-Agent", version);
    QNetworkReply* reply = manager->sendCustomRequest(request, request_method, data);
    // Come from https://stackoverflow.com/a/58403924/11802671
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    return reply;
}

void ApiRequest::requestConfig()
{
    QNetworkReply *reply = req("/configs",
        "GET",
        "");
    try {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj = jsonResponse.object();
        ClashConfig::port = obj["port"].toInt();
        ClashConfig::socketPort = obj["socks-port"].toInt();
        ClashConfig::allowLan = obj["allow-lan"].toBool();
        ClashConfig::mode = obj["mode"].toString();
    } catch (...) {
        NotificationCenter::postNotifiacation("Error", "Get clash config failed. Try Fix your config file then reload config or restart ShadowClah.");
    }
    reply->deleteLater();
}

void ApiRequest::requestConfigUpdate(bool showNotification)
{
    QString filePath = Paths::configFolderPath + "config" + ".yaml";
    QByteArray data = (QString("{\"Path\":\"%1\"}").arg(filePath)).toUtf8();
    QNetworkReply *reply = req("/configs",
        "PUT",
        data);
    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 204) {
        if (showNotification) {
            NotificationCenter::postNotifiacation("Reload Config Succeed","Succees");
        }
    } else {
        if (showNotification) {
            NotificationCenter::postNotifiacation("Reload Config Fail", reply->readAll());
        }
    }
    reply->deleteLater();
}

void ApiRequest::updateOutBoundMode(QString mode)
{
    QByteArray data = (QString("{\"mode\":\"%1\"}").arg(mode)).toUtf8();
    req("/configs",
        "PATCH",
        data);
}

void ApiRequest::requestProxyGroupList()
{
    req("/proxies",
        "GET",
        "");
}

void ApiRequest::updateAllowLan(bool allow)
{
    QByteArray data = (QString("{\"allow-lan\":%1}").arg(QVariant(allow).toString())).toUtf8();
    req("/configs",
        "PATCH",
        data);
}

void ApiRequest::getProxyDelay()
{
    req("/proxies/%1/delay",
        "GET",
        "{\"timeout\":5000,\"url\":\"http://www.gstatic.com/generate_204\"");
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
