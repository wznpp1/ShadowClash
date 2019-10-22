#include "configmanager.h"
#include "apirequest.h"

#include <QDir>
#include <QLocale>
#include <QDebug>
#include <QTime>
#include <QString>
#include <QApplication>
#include <QFileInfoList>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include "paths.h"
#include <QSettings>

#include <QFileSystemWatcher>
#include "notificationcenter.h"
#include <QJsonDocument>

const QString ConfigManager::version = QString("0.0.1");

QString ConfigManager::apiPort = QString("9090");

QString ConfigManager::apiSecret;

QString ConfigManager::apiUrl = QString("http://127.0.0.1:") + apiPort;

const QDate ConfigManager::buildDate = QLocale( QLocale::English ).toDate( QString( __DATE__ ).replace( "  ", " 0" ), "MMM dd yyyy");

const QTime ConfigManager::buildTime = QTime::fromString( __TIME__, "hh:mm:ss");

bool ConfigManager::startAtLogin;

QString ConfigManager::selectConfigName;

bool ConfigManager::proxyPortAutoSet;

QSettings ConfigManager::settings(QApplication::organizationName(), QApplication::applicationName());

void ConfigManager::watchConfigFile(QString configName)
{
    ConfigManager cm;
    QFileSystemWatcher *watcher = new QFileSystemWatcher();
    QString path = Paths::configFolderPath + "/" + configName + ".yaml";
    connect(watcher, SIGNAL(fileChanged()), &cm, SLOT(fileChanged()));
    watcher->addPath(path);
}

void ConfigManager::copySampleConfigIfNeed()
{
    if (!QFile::exists(Paths::defaultConfigFilePath)) {
        QFile::copy(":/sampleConfig.yaml", Paths::configFolderPath);
    }
}

void ConfigManager::fileChanged()
{
    NotificationCenter::postConfigFileChangeDetectionNotice();
}

void ConfigManager::checkFinalRuleAndShowAlert()
{
    QJsonObject obj = ApiRequest::getRules();
    QJsonArray array = obj["rules"].toArray();
    bool hasFinalRule = false;

    for (int i=0; i<array.size(); i++) {
        QJsonObject each = array[i].toObject();
        if (each.value("type") == "MATCH") {
            hasFinalRule = true;
            break;
        } else {
            continue;
        }
    }

    if (!hasFinalRule) {
        showNoFinalRuleAlert();
    }
}

void ConfigManager::showNoFinalRuleAlert()
{
    QMessageBox alert;
    alert.setWindowTitle("ShadowClash");
    alert.setText("No FINAL rule were found in clash configs,This might caused by incorrect upgradation during earily version of ShadowClash or error setting of FINAL rule.Please check your config file.\n\nNO FINAL rule would cause traffic send to DIRECT which no match any rules.");
    alert.addButton(tr("OK"), QMessageBox::YesRole);
    alert.exec();
}

QByteArray ConfigManager::getConfigFilesList()
{
    QByteArray result;
    QDir dir(Paths::configFolderPath);
    QFileInfoList list = dir.entryInfoList();
    for (int i=0;i<list.size();++i) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.suffix() == "yaml") {
            result.append(fileInfo.fileName().split(".")[0]);
        }
    }
    return result;
}
