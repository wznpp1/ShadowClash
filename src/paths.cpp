//
//  paths.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2018/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "paths.h"

#include <QDir>
#include <QString>

const QString Paths::configFolderPath = QDir::homePath() + "/.config/clash/";

const QString Paths::defaultConfigFilePath = configFolderPath + "config.yaml";

QString Paths::currentConfigPath = configFolderPath + ".yaml";

#if defined (Q_OS_MAC)
const QString Paths::logsPath = QDir::homePath() + "/Library/Logs/ShadowClash/";
#endif
