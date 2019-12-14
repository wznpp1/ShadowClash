//
//  urlschemehandler.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2019/12/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "urlschemehandler.h"
#include "addremoteconfigwindow.h"

#include <QDebug>
#include <QDir>
#include <QUrl>
#include <QFileOpenEvent>
#include <QRegularExpression>
#include <QSettings>

/*
void UrlSchemeHandler::installHandler()
{
// https://docs.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/aa767914(v=vs.85)?redirectedfrom=MSDN
#if defined (Q_OS_WIN)
    QSettings reg("HKEY_CLASSES_ROOT", QSettings::NativeFormat);
    reg.setValue("clash", "");
    delete reg;
    QSettings reg("HKEY_CLASSES_ROOT\\clash", QSettings::NativeFormat);
    reg.setValue("URL protocol", "");
    delete reg;
    QSettings reg("HKEY_CLASSES_ROOT\\shell\\open\\command", QSettings::NativeFormat);
    QString value = "\"" + QDir::toNativeSeparators(QCoreApplication::applicationFilePath())  + "\"" + " \"%1\"";
    reg.setValue("", value);
    delete reg;
#endif
}
*/

bool UrlSchemeHandler::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::FileOpen)
    {
        QFileOpenEvent* fileEvent = static_cast<QFileOpenEvent*>(event);
        if (!fileEvent->url().isEmpty())
        {
            // Not call directly .toString to avoid getting strange data like: clash://0.1.226.63
            QString data = QString::fromLatin1(fileEvent->url().toEncoded().data());
            QString splitData = data.split("install-config?url=")[1];
            QString url = QUrl::fromPercentEncoding(splitData.toLatin1());
            QRegularExpression pattern("(([\\w-]+\\.)+\\w+(:\\d{1,5})?)");
            QRegularExpressionMatch match = pattern.match(url);
            QString configName = match.captured(0);
            arcw = new AddRemoteConfigWindow();
            arcw->setData(url, configName);
            arcw->exec();
        }

        return false;

    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
