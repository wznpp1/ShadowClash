#ifndef LOGGER_H
#define LOGGER_H

#include <QStringList>

class Logger
{
public:
    QStringList logLevel;
    void init();
    void log(QString msg, QString level);
};

#endif // LOGGER_H
