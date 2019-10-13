#ifndef PATHS_H
#define PATHS_H

#include <QString>

class Paths
{
public:
    Paths();
    static const QString configFolderPath;
    static const QString defaultConfigFilePath;
    static QString currentConfigPath;
};

#endif // PATHS_H
