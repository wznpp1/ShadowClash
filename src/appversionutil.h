//
//  appversionutil.h
//  ShadowClash
//
//  Created by TheWanderingCoel on 2018/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#ifndef APPVERSIONUTIL_H
#define APPVERSIONUTIL_H


class AppVersionUtil
{
public:
    static void init();
    static bool isFirstLaunch();
    static bool hasVersionChanged();
};

#endif // APPVERSIONUTIL_H
