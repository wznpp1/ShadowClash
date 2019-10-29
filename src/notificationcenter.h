#ifndef NSUSERNOTIFICATIONCENTER_H
#define NSUSERNOTIFICATIONCENTER_H

#include <QString>

class NotificationCenter
{
public:
    static void postNotifiacation(QString title, QString info);
    static void postConfigErrorNotice(QString message);
    void postGenerateSimpleConfigNotice();
    static void postConfigFileChangeDetectionNotice();
    void postImportConfigFromUrlFailNotice(QString url);
    void postProxyRemarkDupNotice(QString name);
    void postSpeedTestBeginNotice();
    void postSpeedTestingNotice();
    void postSpeedTestFinishNotice();
};

#endif // NSUSERNOTIFICATIONCENTER_H
