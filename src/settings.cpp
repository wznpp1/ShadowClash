#include "settings.h"
#include "configmanager.h"

#include <QApplication>
#include <QDebug>

QSettings Settings::settings(QApplication::organizationName(), QApplication::applicationName());

void Settings::loadAll()
{
    ConfigManager::selectConfigName = Settings::settings.value("config").toString();
    if (Settings::settings.value("dashboard").toString() == "clashx") {
        ConfigManager::selectDashBoard = "clashxdashboard";
    } else if (Settings::settings.value("dashboard").toString() == "yacd") {
        ConfigManager::selectDashBoard = "yacddashboard";
    }

}

void Settings::setConfig(QString value)
{
    Settings::settings.setValue("config", value);
}

void Settings::setDashboard(QString value)
{
    Settings::settings.setValue("dashboard", value);
}
