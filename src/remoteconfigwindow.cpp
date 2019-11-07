#include <QStandardItem>

#include "remoteconfigwindow.h"
#include "ui_remoteconfigwindow.h"

RemoteConfigWindow::RemoteConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoteConfigWindow)
{
    ui->setupUi(this);

    QStandardItemModel *model = new QStandardItemModel();
    // set column number
    model->setColumnCount(3);
    // set up horizontal headers
    model->setHeaderData(0,Qt::Horizontal,"Url");
    model->setHeaderData(1,Qt::Horizontal,"Config Name");
    model->setHeaderData(2,Qt::Horizontal,"Update Time");
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

}

RemoteConfigWindow::~RemoteConfigWindow()
{
    delete ui;
}

/*
RemoteConfigWindow::actionAdd()
{

}

RemoteConfigWindow::actionDelete()
{

}

RemoteConfigWindow::actionUpdate()
{

}
*/
