#include "apirequest.h"
#include "configmanager.h"

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

ApiRequest::ApiRequest()
{

}

QNetworkReply* ApiRequest::req(QString url, QString method, QByteArray data) {
    QByteArray version = ("ShadowCoel/" + ConfigManager::version).toUtf8();
    QByteArray request_method = method.toUtf8();
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request(ConfigManager::apiUrl + url);
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("User-Agent", version);
    QNetworkReply* reply = manager->sendCustomRequest(request, request_method, data);
    return reply;
}

void ApiRequest::requestConfig()
{
    req("/configs",
        "GET",
        "");
}

void ApiRequest::requestConfigUpdate(QString path)
{
    QByteArray data = (QString("{\"Path\":\"%1\"}").arg(path)).toUtf8();
    req("/configs",
        "PUT",
        data);
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
