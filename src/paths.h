#ifndef PATHS_H
#define PATHS_H

#include <QString>

class Paths
{
public:
    static const QString configFolderPath;
    static const QString defaultConfigFilePath;
    static QString currentConfigPath;
    static QString tempPath;
    static const QString logsPath;
    static const QString logFilePath;
};

#endif // PATHS_H
