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
