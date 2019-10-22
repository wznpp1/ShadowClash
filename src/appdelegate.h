#ifndef APPDELEGATE_H
#define APPDELEGATE_H

#include <QObject>

class AppDelegate: public QObject
{
public:
    static void startProxy();
    static void updateConfig();
    static void syncConfig();

public slots:
    void applicationWillTerminate();
};

#endif // APPDELEGATE_H
