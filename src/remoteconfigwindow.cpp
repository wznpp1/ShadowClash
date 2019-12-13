//
//  remoteconfigwindow.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2019/12/4.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include <QStandardItem>

#include "remoteconfigwindow.h"
#include "remoteconfigmanager.h"
#include "ui_remoteconfigwindow.h"
#include "paths.h"
#include "addremoteconfigwindow.h"
#include "logger.h"
#include "addremoteconfigwindow.h"

#include <QDebug>
#include <QFile>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include <QUrl>
#include <QDateTime>

RemoteConfigWindow::RemoteConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoteConfigWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Remote Configs"));

    model = new QStandardItemModel();
    // set column number
    model->setColumnCount(3);
    // set up horizontal headers
    model->setHeaderData(0,Qt::Horizontal,tr("Url"));
    model->setHeaderData(1,Qt::Horizontal,tr("Config Name"));
    model->setHeaderData(2,Qt::Horizontal,tr("Update Time"));
    // have to be before other settings
    ui->tableView->setModel(model);
    // disable showing grid
    ui->tableView->setShowGrid(false);
    // disable auto sort
    ui->tableView->setSortingEnabled(false);
    // hide vertical header
    ui->tableView->verticalHeader()->hide();
    // set the whole row instead one section
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Set url column width to be larger
    ui->tableView->setColumnWidth(0,150);

    arcw = new AddRemoteConfigWindow();

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(actionAdd()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(actionDelete()));
    connect(ui->updateButton, SIGNAL(clicked()), this, SLOT(actionUpdate()));
    connect(arcw, &AddRemoteConfigWindow::sendData, this, &RemoteConfigWindow::receiveData);
}

RemoteConfigWindow::~RemoteConfigWindow()
{
    delete ui;
}

void RemoteConfigWindow::actionAdd()
{
    showAdd();
}

void RemoteConfigWindow::actionDelete()
{
    // get row index first
    QModelIndex index = ui->tableView->currentIndex();
    // and then we delete the config file
    QFile::remove(Paths::configFolderPath + index.siblingAtColumn(1).data().toString() + ".yaml");
    // finally, we delete the row by index
    model->removeRow(index.row());
}

void RemoteConfigWindow::actionUpdate()
{
    QModelIndex index = ui->tableView->currentIndex();
    QString url = index.siblingAtColumn(0).data().toString();
    QString configName = index.siblingAtColumn(1).data().toString();
    requestUpdate(url, configName);
}

void RemoteConfigWindow::showAdd()
{
    arcw->exec();
}

bool RemoteConfigWindow::requestUpdate(QString url, QString configName)
{
    return RemoteConfigManager::updateConfig(url, configName);
}

void RemoteConfigWindow::receiveData(QString url, QString configName)
{
    QRegExp pattern("[a-zA-z]+://[^\\s]*");
    if (!pattern.exactMatch(url)) {
        QMessageBox alert;
        alert.setWindowTitle("ShadowClash");
        alert.setText(tr("Invalid input"));
        alert.addButton(tr("OK"), QMessageBox::YesRole);
        alert.exec();
        Logger::log(tr("Invalid input"), "error");
        return;
    }

    if (isDup(configName)) {
        QMessageBox alert;
        alert.setWindowTitle("ShadowClash");
        alert.setText(tr("The remote config name is duplicated"));
        alert.addButton(tr("OK"), QMessageBox::YesRole);
        alert.exec();
        Logger::log(tr("The remote config name is duplicated"), "error");
        return;
    }

    int rowCount = model->rowCount();
    model->setItem(rowCount, 0, new QStandardItem(url));
    model->setItem(rowCount, 1, new QStandardItem(configName));
    model->setItem(rowCount, 2, new QStandardItem(tr("Updating...")));

    bool status = requestUpdate(url, configName);
    if (status) {
        QDateTime time(QDateTime::currentDateTime());
        QString local_time = time.toString("MM-dd hh:mm");
        model->setItem(rowCount, 2, new QStandardItem(local_time));
    } else {
        model->setItem(rowCount, 2, new QStandardItem(tr("Never")));
    }
}

// check whether config name is duplicated
bool RemoteConfigWindow::isDup(QString configName)
{
    QSortFilterProxyModel proxy;
    proxy.setSourceModel(model);
    proxy.setFilterKeyColumn(1);
    proxy.setFilterFixedString(configName);
    QModelIndex matchingIndex = proxy.mapToSource(proxy.index(0,0));
    if (matchingIndex.isValid()) {
        return true;
    } else {
        return false;
    }
}
