//
//  paths.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2018/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "paths.h"

#include <QDir>
#include <QStandardPaths>
#include <QString>


const QString Paths::configFolderPath = QDir::homePath() + "/.config/clash/";

const QString Paths::defaultConfigFilePath = configFolderPath + "config.yaml";

QString Paths::currentConfigPath = configFolderPath + ".yaml";

QString Paths::tempPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation);

const QString Paths::logsPath = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);

const QString Paths::logFilePath = configFolderPath + "ShadowClash/ShadowClash.log";
