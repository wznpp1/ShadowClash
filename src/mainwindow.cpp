#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configmanager.h"
#include "systemtray.h"
#include "apirequest.h"
#include "proxyconfighelpermanager.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : CFramelessWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

// Mac Os Only
#if defined(Q_OS_MACOS) || defined(Q_OS_MAC)
    // Hide Min Button
    this->setMinBtnEnabled(false);
    // Hide Max Button
    this->setZoomBtnEnabled(false);
    // Close Button Do not quit
    this->setCloseBtnQuit(false);
#endif

    m_pWebView = new QWebEngineView(this);
    // Set WebView Size
    m_pWebView->setGeometry(0,0,920,580);
    // Disable Right Click
    m_pWebView->setContextMenuPolicy(Qt::NoContextMenu);
    m_pWebView->load(QUrl(ConfigManager::apiUrl + "/ui"));

}

MainWindow::~MainWindow()
{
    delete ui;
}
