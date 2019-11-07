#ifndef REMOTECONFIGWINDOW_H
#define REMOTECONFIGWINDOW_H

#include <QDialog>

namespace Ui {
class RemoteConfigWindow;
}

class RemoteConfigWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RemoteConfigWindow(QWidget *parent = nullptr);
    ~RemoteConfigWindow();

private:
    Ui::RemoteConfigWindow *ui;
};

#endif // REMOTECONFIGWINDOW_H
