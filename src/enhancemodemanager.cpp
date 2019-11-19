#include "appversionutil.h"
#include "clashconfig.h"
#include "enhancemodemanager.h"
#include "logger.h"
#include "paths.h"
#include "yaml-cpp/yaml.h"

#include <iostream>
#include <QFile>
#include <QMessageBox>
#include <QProcess>
#include <QStandardPaths>


using namespace std;

QString EnhanceModeManager::gateway;

void EnhanceModeManager::install()
{
    QString dir = Paths::configFolderPath;
    QProcess *task;
    QString temp = QStandardPaths::writableLocation(QStandardPaths::TempLocation);

#ifdef Q_OS_WIN
    if (!QFile::exists(dir + "tun2socks.exe")) {
        QFile::copy(":/tun2socks.exe",dir + "tun2socks.exe");
    }

    if (AppVersionUtil::isFirstLaunch) {
        // Install Tap Driver
        QFile::copy(":/tap-windows-9.22.1-I602.exe", temp+ "tap-windows-9.22.1-I602.exe");
        task->start(temp+ "tap-windows-9.22.1-I602.exe");
    }

#elif defined(Q_OS_MAC)
    if (!QFile::exists(dir + "tun2socks")) {
        QFile::copy(":/tun2socks",dir + "tun2socks");
    }

    if (!QFile::exists(dir + "tun2socks.sh")) {
        QFile::copy(":/tun2socks.sh",dir + "tun2socks.sh");
    }

#elif defined(Q_OS_LINUX)
    if (!QFile::exists(dir + "tun2socks")) {
        QFile::copy(":/tun2socksLinux",dir + "tun2socks");
    }
#endif
}

void EnhanceModeManager::getDefaultGateway()
{
    QProcess *task = new QProcess;
    QStringList param;
#if defined (Q_OS_MAC) || defined (Q_OS_LINUX)
    param << "-c" << "route get default | grep gateway | awk '{print $2}'";
    task->start("bash", param);
    task->waitForFinished();
    EnhanceModeManager::gateway = task->readAllStandardOutput();
    EnhanceModeManager::gateway = EnhanceModeManager::gateway.remove("\n");
#endif

}

void EnhanceModeManager::startTun2socks()
{
    getDefaultGateway();

    QProcess *task = new QProcess;
    QStringList param;

    YAML::Node config = YAML::LoadFile(Paths::defaultConfigFilePath.toStdString());
    const YAML::Node& proxies = config["Proxy"];
    QFile file(Paths::configFolderPath + "ip.txt");
    file.open(QIODevice::ReadWrite|QIODevice::Truncate);
    for (std::size_t i = 0; i < proxies.size(); i++) {
        const YAML::Node& proxy = proxies[i];
        file.write(QString::fromStdString(proxy["server"].as<string>()).toUtf8());
        file.write("\n");
    }
    file.close();

#if defined(Q_OS_WIN)
    Logger::log("startTun2socks", "debug");
    param << "-tunName" <<  "tun1" << "-tunAddr" << "240.0.0.2" << "-tunGw" << "240.0.0.1" << "-proxyType" << "socks" << "-proxyServer" << "127.0.0.1" + QString::number(ClashConfig::socketPort);
    task->startDetached(Paths::configFolderPath + "tun2socks.exe", param);
#elif defined(Q_OS_MAC)
    Logger::log("startTun2socks", "debug");
    param << "-tunName" <<  "utun1" << "-tunAddr" << "240.0.0.2" << "-tunGw" << "240.0.0.1" << "-proxyType" << "socks" << "-proxyServer" << "127.0.0.1:" + QString::number(ClashConfig::socketPort);
    task->startDetached(Paths::configFolderPath + "tun2socks", param);
    QString script = QString("do shell script \"bash %1 \\\"%2\\\" \\\"%3\\\" \\\"%4\\\"\" with administrator privileges").arg(Paths::configFolderPath + "tun2socks.sh").arg(Paths::configFolderPath).arg(EnhanceModeManager::gateway).arg("start");
    param.clear();
    param << "-l" << "AppleScript";
    task->start("/usr/bin/osascript", param);
    task->write(script.toUtf8());
    task->closeWriteChannel();
    task->waitForFinished();
#elif defined(Q_OS_LINUX)
    param << "-tunName" <<  "tun1" << "-tunAddr" << "240.0.0.2" << "-tunGw" << "240.0.0.1" << "-proxyType" << "socks" << "-proxyServer" << "127.0.0.1:" + QString::number(ClashConfig::socketPort);
    task->startDetached(Paths::configFolderPath + "tun2socks", param);
    param << "bash" << Paths::configFolderPath + "tun2socks.sh" << Paths::configFolderPath << EnhanceModeManager::gateway << "start";
    task->start("kdesu", param);
    task->waitForFinished();
#endif
    QFile::remove(Paths::configFolderPath + "ip.txt");

}

void EnhanceModeManager::stopTun2socks()
{
    QProcess *task = new QProcess;
    QStringList param;
    YAML::Node config = YAML::LoadFile(Paths::defaultConfigFilePath.toStdString());
    const YAML::Node& proxies = config["Proxy"];
    QFile file(Paths::configFolderPath + "ip.txt");
    file.open(QIODevice::ReadWrite|QIODevice::Truncate);
    for (std::size_t i = 0; i < proxies.size(); i++) {
        const YAML::Node& proxy = proxies[i];
        file.write(QString::fromStdString(proxy["server"].as<string>()).toUtf8());
        file.write("\n");
    }
    file.close();
#if defined (Q_OS_WIN)
#elif defined(Q_OS_MAC)
    QString script = QString("do shell script \"bash %1 \\\"%2\\\" \\\"%3\\\" \\\"%4\\\"\" with administrator privileges").arg(Paths::configFolderPath + "tun2socks.sh").arg(Paths::configFolderPath).arg(EnhanceModeManager::gateway).arg("stop");
    param << "-l" << "AppleScript";
    task->start("/usr/bin/osascript", param);
    task->write(script.toUtf8());
    task->closeWriteChannel();
    task->waitForFinished();
#elif defined(Q_OS_LINUX)
    param << "bash" << Paths::configFolderPath + "tun2socks.sh" << Paths::configFolderPath << EnhanceModeManager::gateway << "stop";
    task->start("kdesu", param);
    task->waitForFinished();
#endif
    QFile::remove(Paths::configFolderPath + "ip.txt");
}

