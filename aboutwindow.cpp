#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include "configmanager.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    setupIcon();
    setupVersion();
    setupCompileDate();
    setupHyperLink();
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::setupIcon()
{
    QImage image(":/resources/icons/Icon_102.png");
    ui->icon->setPixmap(QPixmap::fromImage(image));
    ui->icon->show();
}

void AboutWindow::setupVersion()
{
    ui->version->setText(ConfigManager::version);
}

void AboutWindow::setupCompileDate()
{
    ui->compileTime->setText(ConfigManager::buildDate.toString() + " " + ConfigManager::buildTime.toString());
}

void AboutWindow::setupHyperLink()
{
    ui->clashLink->setOpenExternalLinks(true);
    ui->clashLink->setText("<a href=\"https://github.com/Dreamacro/clash\">https://github.com/Dreamacro/clash");
    ui->shadowcoelLink->setOpenExternalLinks(true);
    ui->shadowcoelLink->setText("<a href=\"https://github.com/TheWanderingCoel/ShadowCoel-clash-ui\">https://github.com/TheWanderingCoel/ShadowCoel-clash-ui");
}
