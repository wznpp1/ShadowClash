#include "appversionutil.h"
#include "configmanager.h"

#include <QSettings>
#include <QApplication>
#include <QDebug>

void AppVersionUtil::init()
{
    ConfigManager::settings.setValue("version", QApplication::applicationVersion());
}

bool AppVersionUtil::isFirstLaunch()
{
    return !ConfigManager::settings.contains("version");
}

bool AppVersionUtil::hasVersionChanged()
{
    return QApplication::applicationVersion() != ConfigManager::settings.value("settings");
}
