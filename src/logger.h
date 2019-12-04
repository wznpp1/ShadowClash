#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QStringList>

class Logger: public QObject
{
public:
    static QStringList logLevel;
    static void init();
    static void log(QString msg, QString level);
    static void showCreateLogDirFailAlert();
};

#endif // LOGGER_H
