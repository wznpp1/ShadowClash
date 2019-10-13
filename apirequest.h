#ifndef APIREQUEST_H
#define APIREQUEST_H

#include <QString>
#include <QNetworkReply>

class ApiRequest
{
public:
    ApiRequest();
    QNetworkReply* req(QString url, QString method, QByteArray data);
    void requestConfig();
    void requestConfigUpdate(QString path);
    void updateOutBoundMode(QString mode);
    void requestProxyGroupList();
    void updateAllowLan(bool allow);
};

#endif // APIREQUEST_H
