//
//  launchatlogin.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2019/11/7.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "paths.h"
#include "plog/Log.h"
#include "logger.h"

void Logger::init()
{
    plog::init(plog::error,Paths::logsPath.toLocal8Bit().data());
    Logger::logLevel << "silent" << "debug" << "info" << "warning" << "error";
}

void Logger::log(QString msg, QString level)
{
    switch(logLevel.indexOf(level)) {
        case 0 | 1:
            PLOG_DEBUG << msg;
        case 2:
            PLOG_INFO << msg;
        case 3:
            PLOG_WARNING << msg;
        case 4:
            PLOG_ERROR << msg;
    }
}
