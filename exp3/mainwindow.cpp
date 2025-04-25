#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "GlobalData.h"
#include "utils.h"

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setBackground(this, "resources/llk_main.bmp");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_basicModeBtn_clicked() {
    this->hide();
    global.getWindow("basicModeWindow")->show();
}

void MainWindow::on_casualModeBtn_clicked() {

}

void MainWindow::on_boardBtn_clicked() {
    global.getWindow("scoreboardWindow")->show();
}

void MainWindow::on_settingsBtn_clicked() {
}

void MainWindow::on_helpBtn_clicked() {
}

void MainWindow::on_levelModeBtn_clicked() {

}
