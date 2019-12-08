//
//  apirequest.h
//  ShadowClash
//
//  Created by TheWanderingCoel on 2018/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#ifndef APIREQUEST_H
#define APIREQUEST_H

#include <QNetworkReply>

class ApiRequest: public QObject
{
public:
    static QNetworkReply* req(QString url, QString method, QByteArray data);
    static void requestConfig();
    static void requestConfigUpdate(bool showNotification);
    void updateOutBoundMode(QString mode);
    void updateLogLevel(QString logLevel);
    void requestProxyGroupList();
    void updateAllowLan(bool allow);
    int getProxyDelay(QString proxyName);
    static QJsonObject getRules();
};

#endif // APIREQUEST_H
