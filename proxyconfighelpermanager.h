#ifndef PROXYCONFIGHELPERMANAGER_H
#define PROXYCONFIGHELPERMANAGER_H

#include <QObject>

class ProxyConfigHelperManager: public QObject
{
public:
    ProxyConfigHelperManager();
    void checkMMDB();
    void setUpSystemProxy(int port, int socksPort);
    void showInstallHelperAlert();
    void showCreateConfigDirFailAlert();
};

#endif // PROXYCONFIGHELPERMANAGER_H
