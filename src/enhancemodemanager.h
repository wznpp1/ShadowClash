//
//  enhancemodemanager.h
//  ShadowClash
//
//  Created by TheWanderingCoel on 2018/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#ifndef ENHANCEMODEMANAGER_H
#define ENHANCEMODEMANAGER_H

#include <QString>
#include <QObject>

class EnhanceModeManager: public QObject
{
public:
    static QString gateway;

    static void install();
    static void getDefaultGateway();
    static void setupRoute();
    static void restoreRoute();
    static void startTun2socks();
    static void stopTun2socks();
    static void startLog();
};

#endif // ENHANCEMODEMANAGER_H
