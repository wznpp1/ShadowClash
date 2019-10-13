#ifndef NSUSERNOTIFICATIONCENTER_H
#define NSUSERNOTIFICATIONCENTER_H

#include <QString>

class NotificationCenter
{
public:
    NotificationCenter();
    void postNotifiacation(QString title, QString info);
    void postGenerateSimpleConfigNotice();
    void postConfigFileChangeDetectionNotice();
    void postImportConfigFromUrlFailNotice(QString url);
    void postProxyRemarkDupNotice(QString name);
    void postSpeedTestBeginNotice();
    void postSpeedTestingNotice();
    void postSpeedTestFinishNotice();
};

#endif // NSUSERNOTIFICATIONCENTER_H
