#include "configmanager.h"

#include <QLocale>
#include <QTime>
#include <QString>

const QString ConfigManager::version = QString("0.0.1");

QString ConfigManager::apiPort = QString("9090");

QString ConfigManager::apiSecret;

QString ConfigManager::apiUrl = QString("http://127.0.0.1:") + apiPort;

const QDate ConfigManager::buildDate = QLocale( QLocale::English ).toDate( QString( __DATE__ ).replace( "  ", " 0" ), "MMM dd yyyy");

const QTime ConfigManager::buildTime = QTime::fromString( __TIME__, "hh:mm:ss" );

ConfigManager::ConfigManager()
{

}

void ConfigManager::checkFinalRuleAndShowAlert()
{

}
