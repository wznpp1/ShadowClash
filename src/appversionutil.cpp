//
//  appversionutil.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2018/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "appversionutil.h"
#include "settings.h"

#include <QApplication>
#include <QSettings>

void AppVersionUtil::init()
{
    Settings::settings.setValue("version", QApplication::applicationVersion());
}

bool AppVersionUtil::isFirstLaunch()
{
    return !Settings::settings.contains("version");
}

bool AppVersionUtil::hasVersionChanged()
{
    return QApplication::applicationVersion() != Settings::settings.value("version");
}
