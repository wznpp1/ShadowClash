#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "framelesswindow.h"
#include <QUrl>
#include <QMainWindow>
#include <QWebEngineView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public CFramelessWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setupButton();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWebEngineView* m_pWebView;
};
#endif // MAINWINDOW_H
