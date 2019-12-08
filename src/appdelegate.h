//
//  appdelegate.h
//  ShadowClash
//
//  Created by TheWanderingCoel on 2018/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#ifndef APPDELEGATE_H
#define APPDELEGATE_H

#include <QObject>

class AppDelegate: public QObject
{
public:
    static void applicationWillTerminate();
    static void startProxy();
    static void updateConfig();
    static void syncConfig();
};

#endif // APPDELEGATE_H
