#ifndef CLASHCONFIG_H
#define CLASHCONFIG_H

#include <QString>

class ClashConfig
{
public:
    static int port;
    static int socketPort;
    static int redirPort;
    static bool allowLan;
    static QString mode;
    static QString logLevel;
};

#endif // CLASHCONFIG_H
