//
//  remoteconfigwindow.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2019/12/4.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include <QStandardItem>

#include "remoteconfigwindow.h"
#include "ui_remoteconfigwindow.h"

#include <QDebug>

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
    model->setHeaderData(0,Qt::Horizontal,"Url");
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

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(actionAdd()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(actionDelete()));
    connect(ui->updateButton, SIGNAL(clicked()), this, SLOT(actionUpdate()));
}

RemoteConfigWindow::~RemoteConfigWindow()
{
    delete ui;
}

void RemoteConfigWindow::actionAdd()
{
    int rowCount = model->rowCount();
    model->setItem(rowCount, 0, new QStandardItem("张三"));
    model->setItem(rowCount, 1, new QStandardItem("李四"));
    model->setItem(rowCount, 2, new QStandardItem("王五"));
}

void RemoteConfigWindow::actionDelete()
{
    // get row index first
    QModelIndex index = ui->tableView->currentIndex();
    // and then we delete the config file
    // finally, we del2ete the row by index
    model->removeRow(index.row());
}

void RemoteConfigWindow::actionUpdate()
{
    requestUpdate();
}

void RemoteConfigWindow::showAdd()
{

}

void RemoteConfigWindow::requestUpdate()
{
}
