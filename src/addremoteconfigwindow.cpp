//
//  addremoteconfigwindow.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2019/12/11.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "addremoteconfigwindow.h"
#include "ui_addremoteconfigwindow.h"

#include <QDebug>

AddRemoteConfigWindow::AddRemoteConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRemoteConfigWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("");

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

AddRemoteConfigWindow::~AddRemoteConfigWindow()
{
    delete ui;
}

void AddRemoteConfigWindow::on_buttonBox_accepted()
{
    emit sendData(ui->url->text(), ui->configName->text());
}

void AddRemoteConfigWindow::setData(QString url, QString configName)
{
    ui->url->setText(url);
    ui->configName->setText(configName);
}
