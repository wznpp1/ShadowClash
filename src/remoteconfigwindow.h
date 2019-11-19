#ifndef REMOTECONFIGWINDOW_H
#define REMOTECONFIGWINDOW_H

#include <QDialog>
#include <QStandardItemModel>

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

private:
    Ui::RemoteConfigWindow *ui;

private slots:
    void actionAdd();
    void actionDelete();
    void actionUpdate();
};

#endif // REMOTECONFIGWINDOW_H
