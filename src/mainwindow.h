#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "framelesswindow.h"
#include <QUrl>
#include <QMainWindow>
#include <QWebEngineView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#if defined (Q_OS_MAC)
class MainWindow : public CFramelessWindow
{
#else
class MainWindow : public QMainWindow
{
#endif
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWebEngineView* m_pWebView;
};
#endif // MAINWINDOW_H
