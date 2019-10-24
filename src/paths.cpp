#include "paths.h"

#include <QDir>
#include <QString>

const QString Paths::configFolderPath = QDir::homePath() + "/.config/clash/";

const QString Paths::defaultConfigFilePath = configFolderPath + "config.yaml";

QString Paths::currentConfigPath = configFolderPath + ".yaml";

#if defined (Q_OS_MAC)
const QString Paths::logsPath = QDir::homePath() + "/Library/Logs/ShadowClash/";
#endif
