QT       += core gui network webenginewidgets
ICON      = resources/icons/icon.icns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += sdk_no_version_check

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32 {
    SOURCES += \
        src/framelesswindow.cpp
}

macx {
    OBJECTIVE_SOURCES += \
        src/framelesswindow.mm \
        src/notificationcenter.mm
    LIBS += -framework Cocoa
}

SOURCES += \
    src/aboutwindow.cpp \
    src/apirequest.cpp \
    src/configmanager.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/paths.cpp \
    src/proxyconfighelpermanager.cpp \
    src/systemtray.cpp

HEADERS += \
    src/framelesswindow.h \
    src/aboutwindow.h \
    src/apirequest.h \
    src/configmanager.h \
    src/mainwindow.h \
    src/notificationcenter.h \
    src/paths.h \
    src/proxyconfighelpermanager.h \
    src/systemtray.h

FORMS += \
    ui/mainwindow.ui \
    ui/aboutwindow.ui

TRANSLATIONS += \
    translations/shadowcoel_en.ts

!include("src/fervor/Fervor.pri") {
    error("Unable to include Fervor autoupdater.")
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/shadowcoel.qrc
