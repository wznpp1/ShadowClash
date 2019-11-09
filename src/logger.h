#ifndef LOGGER_H
#define LOGGER_H

#include <QStringList>

class Logger
{
public:
    static QStringList logLevel;
    static void init();
    static void log(QString msg, QString level);
};

#endif // LOGGER_H
