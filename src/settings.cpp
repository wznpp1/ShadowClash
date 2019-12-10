#include "settings.h"
#include "configmanager.h"

#include <QApplication>
#include <QDebug>

QSettings Settings::settings(QApplication::organizationName(), QApplication::applicationName());

void Settings::loadAll()
{
    if (Settings::settings.value("dashboard") == "clashx") {
        ConfigManager::selectDashBoard = "clashxdashboard";
    } else if (Settings::settings.value("dashboard") == "yacd") {
        ConfigManager::selectDashBoard = "yacddashboard";
    }
}


void Settings::setDashboard(QString value)
{
    Settings::settings.setValue("dashboard", value);
}
