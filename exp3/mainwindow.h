//
// Created by 哈哈了 on 2025/3/20.
//

#ifndef DSNA_3_QT_MAINWINDOW_H
#define DSNA_3_QT_MAINWINDOW_H

#include <QWidget>
#include <QMessageBox>


QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QWidget {
    Q_OBJECT

public:
    Ui::MainWindow *ui;

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

public slots:
    void on_basicModeBtn_clicked();

    void on_levelModeBtn_clicked();

    void on_casualModeBtn_clicked();

    void on_boardBtn_clicked();

    void on_settingsBtn_clicked();

    void on_helpBtn_clicked();
};

#endif //DSNA_3_QT_MAINWINDOW_H
