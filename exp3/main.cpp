#include <QApplication>
#include "mainwindow.h"
#include "BasicModeWindow.h"
#include "GlobalData.h"
#include <QInputDialog>

#include "scoreboardwindow.h"
#include "ui_MainWindow.h"

class GlobalData global;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    BasicModeWindow basicModeWindow;
    MainWindow mainWindow;
    ScoreboardWindow scoreboardWindow;
    global.addWindow("basicModeWindow", &basicModeWindow);
    global.addWindow("mainWindow", &mainWindow);
    global.addWindow("scoreboardWindow", &scoreboardWindow);

    global.username = QInputDialog::getText(nullptr, "取名", "给自己起个昵称：", QLineEdit::Normal, "User");

    mainWindow.show();
    return QApplication::exec();
}
