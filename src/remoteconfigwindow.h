#ifndef REMOTECONFIGWINDOW_H
#define REMOTECONFIGWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include "addremoteconfigwindow.h"

namespace Ui {
class RemoteConfigWindow;
}

class RemoteConfigWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RemoteConfigWindow(QWidget *parent = nullptr);
    ~RemoteConfigWindow();
    QStandardItemModel *model;
    void showAdd();
    bool requestUpdate(QString url, QString configName);
    bool isDup(QString configName);
    AddRemoteConfigWindow *arcw;

private:
    Ui::RemoteConfigWindow *ui;

private slots:
    void actionAdd();
    void actionDelete();
    void actionUpdate();
    void receiveData(QString url, QString configName);
};

#endif // REMOTECONFIGWINDOW_H
