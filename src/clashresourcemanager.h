#ifndef CLASHRESOURCEMANAGER_H
#define CLASHRESOURCEMANAGER_H

#include <QObject>

class ClashResourceManager: public QObject
{
public:
    static void check();
    static void checkConfigDir();
    static void upgardeYmlExtensionName();
    static void checkMMDB();
    static void installHelper();
    static void showCreateConfigDirFailAlert();
    static bool showInstallHelperAlert();
};

#endif // CLASHRESOURCEMANAGER_H
