#include "paths.h"

#include <QDir>
#include <QString>

const QString Paths::configFolderPath = "file://" + QDir::homePath() + "/.config/clash";

const QString Paths::defaultConfigFilePath = configFolderPath + "config.yaml";

QString Paths::currentConfigPath = configFolderPath + ".yaml";

Paths::Paths()
{

}
