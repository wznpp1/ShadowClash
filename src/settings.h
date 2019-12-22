#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings
{
public:
    static QSettings settings;
    static void loadAll();
    static void setConfig(QString value);
    static void setDashboard(QString value);
};

#endif // SETTINGS_H
