#ifndef ADDREMOTECONFIGWINDOW_H
#define ADDREMOTECONFIGWINDOW_H

#include <QDialog>

namespace Ui {
class AddRemoteConfigWindow;
}

class AddRemoteConfigWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddRemoteConfigWindow(QWidget *parent = nullptr);
    ~AddRemoteConfigWindow();
    void setData(QString url, QString configName);

private slots:
    void on_buttonBox_accepted();

signals:
    void sendData(QString, QString);

private:
    Ui::AddRemoteConfigWindow *ui;
};

#endif // ADDREMOTECONFIGWINDOW_H
