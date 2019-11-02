#ifndef ENHANCEMODEMANAGER_H
#define ENHANCEMODEMANAGER_H

#include <QString>
#include <QObject>

class EnhanceModeManager: public QObject
{
public:
    static QString gateway;

    static void install();
    static void getDefaultGateway();
    static void setupRoute();
    static void restoreRoute();
    static void startTun2socks();
    static void stopTun2socks();
    static void startLog();
};

#endif // ENHANCEMODEMANAGER_H
