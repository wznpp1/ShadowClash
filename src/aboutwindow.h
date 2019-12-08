//
//  aboutwindow.h
//  ShadowClash
//
//  Created by TheWanderingCoel on 2018/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = nullptr);
    ~AboutWindow();

private slots:

    void on_aboutQtBtn_clicked();

private:
    Ui::AboutWindow *ui;
    AboutWindow *view;
    void setupVersion();
    void setupBuildDate();
    void setupHyperLink();
};

#endif // ABOUTWINDOW_H
