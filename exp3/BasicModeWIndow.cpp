#include <QPen>
#include <QPainter>
#include <QPaintEvent>
#include "BasicModeWindow.h"
#include "ui_BasicModeWindow.h"
#include "utils.h"
#include "GlobalData.h"
#include <iostream>
#include <QMessageBox>

using namespace std;

BasicModeWindow::BasicModeWindow(QMainWindow *parent) : QMainWindow(parent), ui(new Ui::BasicModeWindow) {
    ui->setupUi(this);
    ui->gridLayout->setSpacing(0);
    this->timerText = new TimerText(this->ui->timerLabel);
    setAutoFillBackground(true);
    setBackground(this, BG_FILE);

    global.basicModeGame = new Game(Game::BASIC_MODE, 16, 10, {this->ui->gridLayout, this->timerText, this->ui->pauseGameBtn, this->ui->hintBtn});
}

BasicModeWindow::~BasicModeWindow() {
    delete ui;
}

void BasicModeWindow::on_startGameBtn_clicked() const {
    global.basicModeGame->initFruits();
    global.basicModeGame->refreshMap();
    ui->startGameBtn->setDisabled(true);
    global.basicModeGame->setPaused(false);
    timerText->start();
}

void BasicModeWindow::on_rearrangeBtn_clicked() const {
    auto reply = QMessageBox::question(this->centralWidget(), "重排确认", "确定要重排吗？这会清空当前的进度",
                                       QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        global.basicModeGame->refreshMap();
        global.basicModeGame->setPaused(true);
    }
}

void BasicModeWindow::on_pauseGameBtn_clicked() const {
    global.basicModeGame->setPaused(!global.basicModeGame->paused);
}

void BasicModeWindow::on_hintBtn_clicked() {
    const auto hint = global.basicModeGame->getHint();

    if (hint.first == nullptr) return;

    hint.first->setStyleSheet("border: 2px dashed red; background: transparent");
    hint.second->setStyleSheet("border: 2px dashed red; background: transparent");
}

void BasicModeWindow::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    if (global.basicModeGame->paintPoints.empty()) return;

    QPainter painter(this);
    QPen pen;
    pen.setWidth(5);
    pen.setColor(QColor(0, 102, 0));
    painter.setPen(pen);

    for (int i = 0; i < int(global.basicModeGame->paintPoints.size()) - 1; i++) {
        auto p1 = global.basicModeGame->paintPoints[i];
        auto p2 = global.basicModeGame->paintPoints[i + 1];

        auto pos1 = Game::mapFromGameGrid(p1.first, p1.second);
        auto pos2 = Game::mapFromGameGrid(p2.first, p2.second);

        cout << pos1.x() << ", " << pos1.y() << "; " << pos2.x() << ", " << pos2.y() << endl;

        painter.drawLine(pos1, pos2);
    }

    global.basicModeGame->paintPoints.clear();

    painter.end();

    //    for (int x = 0; x < global.game->width - 1; x++) {
    //        for (int y = 0; y < global.game->height - 1; y++) {
    //            auto p1 = Game::mapFromGameGrid(x, y);
    //            auto p2 = Game::mapFromGameGrid(x+1, y);
    //            auto p3 = Game::mapFromGameGrid(x, y+1);
    //            painter.drawLine(p1, p2);
    //            painter.drawLine(p1, p3);
    //        }
    //    }
}
