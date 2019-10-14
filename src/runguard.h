/*
 * Come From https://github.com/lhy0403/Qv2ray
 * I'm too lazy to write a guard, so I decided to just copy this code
*/

#ifndef RUNGUARD_H
#define RUNGUARD_H

#include <QObject>
#include <QSharedMemory>
#include <QSystemSemaphore>

class RunGuard
{
public:
    explicit RunGuard(const QString &key);
    ~RunGuard();

    bool isAnotherRunning();
    bool isSingleInstance();
    void release();

private:
    QString generateKeyHash(const QString &key, const QString &salt);
    const QString key;
    const QString memLockKey;
    const QString sharedmemKey;

    QSharedMemory sharedMem;
    QSystemSemaphore memLock;

    Q_DISABLE_COPY(RunGuard)
};

#endif // RUNGUARD_H
