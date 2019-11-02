#include "clashconfig.h"
#include "enhancemodemanager.h"
#include "paths.h"
#include "yaml-cpp/yaml.h"

#include <iostream>
#include <QFile>
#include <QMessageBox>
#include <QProcess>


using namespace std;

QString EnhanceModeManager::gateway;

void EnhanceModeManager::install()
{
    QString dir = Paths::configFolderPath;

#ifdef Q_OS_WIN
    if (!QFile::exists(dir + "tun2socks.exe")) {
        QFile::copy(":/tun2socks.exe",dir + "tun2socks.exe");
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

void EnhanceModeManager::setupRoute()
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
    QString script = QString("do shell script \"bash %1 \\\"%2\\\" \\\"%3\\\" \\\"%4\\\"\" with administrator privileges").arg(Paths::configFolderPath + "tun2socks.sh").arg(Paths::configFolderPath).arg(EnhanceModeManager::gateway).arg("start");
    param << "-l" << "AppleScript";
    task->start("/usr/bin/osascript", param);
    task->write(script.toUtf8());
    task->closeWriteChannel();
    task->waitForFinished();
    file.remove();
}

void EnhanceModeManager::startTun2socks()
{
    getDefaultGateway();

    QProcess *task = new QProcess;
    QStringList param;

#if defined (Q_OS_WIN)
    param << "-tunName" <<  "utun1" << "-tunAddr" << "240.0.0.2" << "-tunGw" << "240.0.0.1" << "-proxyType" << "socks" << "-proxyServer" << "127.0.0.1" + QString::number(ClashConfig::socketPort);
    task->startDetached("tun2socks.exe", param);

#elif defined (Q_OS_MAC) || defined (Q_OS_LINUX)
    param << "-tunName" <<  "utun1" << "-tunAddr" << "240.0.0.2" << "-tunGw" << "240.0.0.1" << "-proxyType" << "socks" << "-proxyServer" << "127.0.0.1:" + QString::number(ClashConfig::socketPort);
    task->startDetached(Paths::configFolderPath + "tun2socks", param);
#endif

    setupRoute();

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
    QString script = QString("do shell script \"bash %1 \\\"%2\\\" \\\"%3\\\" \\\"%4\\\"\" with administrator privileges").arg(Paths::configFolderPath + "tun2socks.sh").arg(Paths::configFolderPath).arg(EnhanceModeManager::gateway).arg("stop");
    param << "-l" << "AppleScript";
    task->start("/usr/bin/osascript", param);
    task->write(script.toUtf8());
    task->closeWriteChannel();
    task->waitForFinished();
}

