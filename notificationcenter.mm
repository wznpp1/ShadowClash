#include "notificationcenter.h"

#include <QString>

#import <Foundation/Foundation.h>

NotificationCenter::NotificationCenter()
{

}

void NotificationCenter::postNotifiacation(QString title, QString info)
{
    NSUserNotification* notification = [[NSUserNotification alloc] init];
    notification.title = title.toNSString();
    notification.informativeText = info.toNSString();
    notification.soundName = NSUserNotificationDefaultSoundName;
    [[NSUserNotificationCenter defaultUserNotificationCenter] deliverNotification: notification];
    [notification autorelease];
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

