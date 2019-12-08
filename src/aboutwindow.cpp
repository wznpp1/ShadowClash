//
//  aboutwindow.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2019/12/4.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "aboutwindow.h"
#include "configmanager.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    setupVersion();
    setupBuildDate();
    setupHyperLink();
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::setupVersion()
{
    ui->version->setText(ConfigManager::version);
}

void AboutWindow::setupBuildDate()
{
    ui->compileTime->setText(ConfigManager::buildDate.toString() + " " + ConfigManager::buildTime.toString());
}

void AboutWindow::setupHyperLink()
{
    ui->clashLink->setOpenExternalLinks(true);
    ui->clashLink->setText("<a href=\"https://github.com/Dreamacro/clash\">https://github.com/Dreamacro/clash");
    ui->shadowClashLink->setOpenExternalLinks(true);
    ui->shadowClashLink->setText("<a href=\"https://github.com/TheWanderingCoel/ShadowClash\">https://github.com/TheWanderingCoel/ShadowClash");
    ui->licenseLink->setOpenExternalLinks(true);
    ui->licenseLink->setText("<a href=\"https://www.gnu.org/licenses/gpl-3.0.txt\">GPL V3 (https://www.gnu.org/licenses/gpl-3.0.txt)");
}

void AboutWindow::on_aboutQtBtn_clicked()
{
    QApplication::aboutQt();
}
