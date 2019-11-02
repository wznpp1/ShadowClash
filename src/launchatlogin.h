#ifndef LAUNCHATLOGIN_H
#define LAUNCHATLOGIN_H

#include <QObject>

class LaunchAtLogin: public QObject
{
Q_OBJECT
public:
    QString getUserAutostartDir_private();
    bool isAutoStart();
    void setupAutoStart(bool enable);
};

#endif // LAUNCHATLOGIN_H
