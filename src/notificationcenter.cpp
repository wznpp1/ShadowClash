//
//  notificationcenter.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2018/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "notificationcenter.h"

#include <QString>

void NotificationCenter::postNotifiacation(QString title, QString info)
{

}

void NotificationCenter::postConfigErrorNotice(QString message)
{
    postNotifiacation("Config loading Fail!", message);
}

void NotificationCenter::postGenerateSimpleConfigNotice()
{
    postNotifiacation("No External-controller specified in config file!", "We have replace current config with a simple config with external-controller specified!");
}

void NotificationCenter::postConfigFileChangeDetectionNotice()
{
    postNotifiacation("Config file have been changed", "Tap to reload config");
}

void NotificationCenter::postImportConfigFromUrlFailNotice(QString url)
{
    postNotifiacation("Import config from url fail", QString("Unrecongized Url:%1").arg(url));
}

void NotificationCenter::postProxyRemarkDupNotice(QString name)
{
    postNotifiacation("Proxy Remark duplicated", QString("Name:%1").arg(name));
}

void NotificationCenter::postSpeedTestBeginNotice()
{
    postNotifiacation("SpeedTest", "SpeedTest has begun, please wait.");
}

void NotificationCenter::postSpeedTestingNotice()
{
    postNotifiacation("SpeedTest", "SpeedTest is processing, please wait.");
}

void NotificationCenter::postSpeedTestFinishNotice()
{
    postNotifiacation("SpeedTest", "SpeedTest Finished!");
}

