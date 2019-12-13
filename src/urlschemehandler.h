#ifndef URLSCHEMEHANDLER_H
#define URLSCHEMEHANDLER_H

#include "addremoteconfigwindow.h"

#include <QObject>

class UrlSchemeHandler: public QObject
{
public:
    bool eventFilter(QObject* obj, QEvent* event);
    AddRemoteConfigWindow *arcw;
};

#endif // URLSCHEMEHANDLER_H
