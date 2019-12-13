//
//  notificationcenter.mm
//  ShadowClash
//
//  Created by TheWanderingCoel on 2018/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "notificationcenter.h"

#include <QString>

#import <Foundation/Foundation.h>

void NotificationCenter::postNotifiacation(QString title, QString info, QString identifier)
{
    NSUserNotification* notification = [[NSUserNotification alloc] init];
    notification.title = title.toNSString();
    notification.informativeText = info.toNSString();
    notification.soundName = NSUserNotificationDefaultSoundName;
    if (identifier != "") {
        //notification.userInfo = ["identifier": identifier];
    }
    [[NSUserNotificationCenter defaultUserNotificationCenter] deliverNotification: notification];
    [notification autorelease];
}

void NotificationCenter::postConfigErrorNotice(QString message)
{
    postNotifiacation(tr("Config loading Fail!"), message);
}

void NotificationCenter::postGenerateSimpleConfigNotice()
{
    postNotifiacation(tr("No External-controller specified in config file!"), tr("We have replace current config with a simple config with external-controller specified!"));
}

void NotificationCenter::postConfigFileChangeDetectionNotice()
{
    postNotifiacation(tr("Config file have been changed"), tr("Tap to reload config"));
}

void NotificationCenter::postImportConfigFromUrlFailNotice(QString url)
{
    postNotifiacation(tr("Import config from url fail"), QString("Unrecongized Url:%1").arg(url));
}

void NotificationCenter::postProxyRemarkDupNotice(QString name)
{
    postNotifiacation(tr("Proxy Remark duplicated"), QString("Name:%1").arg(name));
}

void NotificationCenter::postSpeedTestBeginNotice()
{
    postNotifiacation(tr("SpeedTest"), tr("SpeedTest has begun, please wait."));
}

void NotificationCenter::postSpeedTestingNotice()
{
    postNotifiacation(tr("SpeedTest"), tr("SpeedTest is processing, please wait."));
}

void NotificationCenter::postSpeedTestFinishNotice()
{
    postNotifiacation(tr("SpeedTest"), tr("SpeedTest Finished!"));
}

