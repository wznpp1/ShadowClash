#include "notificationcenter.h"

#include <KNotification>

NotificationCenter::NotificationCenter()
{

}

void NotificationCenter::postNotifiacation(QString title, QString info)
{
    KNotification *notification = new KNotification();
}
