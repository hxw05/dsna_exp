#include "Game.h"

#include <QMessageBox>
#include "BasicModeWindow.h"
#include "GlobalData.h"
#include "qglobal.h"

Game::Game(int mode, int w, int h, const GameControl &controlObject): width(w), height(h), control(controlObject), mode(mode) {
    cleared = std::vector(w * h, false);
}

void Game::initFruits() {
    const QImage elementImage("resources/fruit_element.bmp");
    const QImage maskImage("resources/fruit_mask.bmp");
    this->fruitImages.reserve(10);

    for (int i = 0; i < 10; i++) {
        QRect region(0, i * 40, 40, 40);
        QImage element = elementImage.copy(region);
        QImage mask = maskImage.copy(region);

        QImage mixed(40, 40, QImage::Format_ARGB32);

        for (int x = 0; x < 40; x++) {
            for (int y = 0; y < 40; y++) {
                int alpha = qGray(mask.pixel(x, y));
                QColor color = element.pixelColor(x, y);
                color.setAlpha(alpha);
                mixed.setPixelColor(x, y, color);
            }
        }

        fruitImages.push_back(QPixmap::fromImage(mixed));
    }
}

void Game::refreshMap() {
    this->clearMap();
    this->initMap();
    this->updateMap();
    this->control.timerText->reset();
    this->setPaused(false);
}

void Game::initMap() {
    auto fruitMapResult = genMap(width, height, 10, 0.1);

    auto fruitMap = fruitMapResult.map;
    qDebug() << "neighbor rate: " << fruitMapResult.neighborRate;

    int cursor = 0;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            auto fruit = new Fruit(nullptr, i, j, fruitMap[cursor]);
            fruit->setStyleSheet("border: none; background: transparent");
            fruit->setFixedSize(40, 40);
            fruit->setIcon(QIcon(fruitImages[fruitMap[cursor]]));
            fruit->setIconSize(QSize(40, 40));
            fruit->setCursor(QCursor(Qt::PointingHandCursor));
            auto sp_retain = fruit->sizePolicy();
            sp_retain.setRetainSizeWhenHidden(true);
            fruit->setSizePolicy(sp_retain);
            Fruit::connect(fruit, &QPushButton::clicked, fruit, &Fruit::onClick); // NOLINT(*-unused-return-value)
            gridItems.push_back(fruit);
            cursor++;
        }
    }
}

void Game::clearMap() {
    for (const auto &item: gridItems) {
        this->control.layout->removeWidget(item);
        item->setVisible(false);
        delete item;
    };

    cleared = std::vector(width * height, false);
    gridItems.clear();
}

void Game::updateMap() const {
    for (const auto &item: gridItems)
        this->control.layout->addWidget(item, item->y, item->x, Qt::AlignCenter);
}

void Game::setPaused(bool isPaused) {
    this->paused = isPaused;

    for (const auto &item: gridItems) {
        item->setDisabled(isPaused);
    }

    if (paused) this->control.timerText->end();
    else this->control.timerText->start();

    this->control.hintBtn->setDisabled(isPaused);

    this->control.pauseGameBtn->setText(paused ? "继续游戏" : "暂停游戏");
}

bool Game::isCleared(int x, int y) {
    return cleared[width * y + x];
}

void Game::setCleared(int x, int y, bool isCleared) {
    cleared[width * y + x] = isCleared;
}

void Game::setCleared(int x, int y) {
    setCleared(x, y, true);
}

void Game::setCleared(Fruit *fruit) {
    setCleared(fruit->x, fruit->y);
    fruit->setVisible(false);
}

bool Game::canLinkCorner0(int x0, int y0, int x1, int y1, bool drawLine) {
    if (x0 == x1) {
        if (y0 > y1) std::swap(y0, y1);

        for (int y = y0 + 1; y < y1; y++) {
            if (!isCleared(x0, y)) return false;
        }

        if (drawLine) {
            paintPoints.clear();
            paintPoints.emplace_back(x0, y0);
            paintPoints.emplace_back(x1, y1);
        }
        return true;
    }

    if (y0 == y1) {
        if (x0 > x1) std::swap(x0, x1);

        for (int x = x0 + 1; x < x1; x++) {
            if (!isCleared(x, y0)) return false;
        }

        if (drawLine) {
            paintPoints.clear();
            paintPoints.emplace_back(x0, y0);
            paintPoints.emplace_back(x1, y1);
        }
        return true;
    }

    return false;
}

bool Game::canLinkCorner1(int x0, int y0, int x1, int y1, bool drawLine) {
    if (isCleared(x1, y0)) {
        if (canLinkCorner0(x0, y0, x1, y0, drawLine) && canLinkCorner0(x1, y0, x1, y1, drawLine)) {
            if (drawLine) {
                paintPoints.clear();
                paintPoints.emplace_back(x0, y0);
                paintPoints.emplace_back(x1, y0);
                paintPoints.emplace_back(x1, y1);
            }
            return true;
        }
    }

    if (isCleared(x0, y1)) {
        if (canLinkCorner0(x0, y0, x0, y1, drawLine) && canLinkCorner0(x0, y1, x1, y1, drawLine)) {
            if (drawLine) {
                paintPoints.clear();
                paintPoints.emplace_back(x0, y0);
                paintPoints.emplace_back(x0, y1);
                paintPoints.emplace_back(x1, y1);
            }
            return true;
        }
    }

    return false;
}

bool Game::canLinkCorner2(int x0, int y0, int x1, int y1, bool drawLine) {
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    /**
         * 下面两个循环中，x和y都是从0开始的，这代表着判定时将优先从偏左、偏上的位置开始
         * 假设如下情形
         * L1| a b a    L1| a b a
         * L2| 0 0 0    L2| ↓→→→↑
         * L3| 0 0 0    L3| 0 0 0
         * 将两个a连在一起的线条的水平部分只会经过L2而不会经过L3
         * 如果将以上情形倒置
         * L1| 0 0 0    L1| ↑→→→↓
         * L2| 0 0 0    L2| ↑ 0 ↓
         * L3| a b a    L3| a b a
         * 由于y是从0开始的，将优先发现L1中的连通可行性，于是将两个a连在一起的线条的水平部分只会经过L1而不会经过L2
         *
         * 上述情况不会导致Bug，但可能导致观感/用户体验上的问题。
         */

    for (int y = 0; y < height; y++) {
        if (y == y0 || y == y1) continue;
        if (isCleared(x0, y) && canLinkCorner0(x0, y0, x0, y, drawLine) &&
            canLinkCorner1(x0, y, x1, y1, drawLine)) {
            if (drawLine) {
                paintPoints.clear();
                paintPoints.emplace_back(x0, y0);
                paintPoints.emplace_back(x0, y);
                paintPoints.emplace_back(x1, y);
                paintPoints.emplace_back(x1, y1);
            }
            return true;
        }
    }

    for (int x = 0; x < width; x++) {
        if (x == x0 || x == x1) continue;
        if (isCleared(x, y0) && canLinkCorner0(x0, y0, x, y0, drawLine) &&
            canLinkCorner1(x, y0, x1, y1, drawLine)) {
            if (drawLine) {
                paintPoints.clear();
                paintPoints.emplace_back(x0, y0);
                paintPoints.emplace_back(x, y0);
                paintPoints.emplace_back(x, y1);
                paintPoints.emplace_back(x1, y1);
            }
            return true;
        }
    }

    return false;
}

int Game::canLink(int x0, int y0, int x1, int y1, bool drawLine) {
    if (canLinkCorner0(x0, y0, x1, y1, drawLine)) return LINK_CORNER1;
    if (canLinkCorner1(x0, y0, x1, y1, drawLine)) return LINK_CORNER2;
    if (canLinkCorner2(x0, y0, x1, y1, drawLine)) return LINK_CORNER3;
    return 0;
}

int Game::canLink(int x0, int y0, int x1, int y1) {
    return canLink(x0, y0, x1, y1, true);
}

void Game::setClicked(Fruit *target, bool isClicked) {
    if (isClicked) clicked.push_back(target);
    else std::erase(clicked, target);
    // else clicked.erase(std::remove(clicked.begin(), clicked.end(), target), clicked.end());
}

std::pair<Fruit *, Fruit *> Game::getClickedPair() {
    if (hasClickedPair()) return {clicked[0], clicked[1]};
    return {nullptr, nullptr};
}

bool Game::hasClickedPair() const {
    return clicked.size() == 2;
}

void Game::clearClicked() {
    for (const auto &c: clicked) {
        c->setClicked(false);
    }
    clicked.clear();
}

void Game::onPairCleared() {
    QString title;
    QString text;

    if (allClear()) {
        title = "游戏胜利";
        text += "恭喜，你已经消除了所有水果！";
        global.recordManager->addRecord({
            global.getUsername(),
            1,
            QTime(0, 0, 0).secsTo(this->control.timerText->timerTime),
            QDateTime::currentMSecsSinceEpoch()
        });
    } else if (getHint().first == nullptr) {
        title = "游戏僵局";
        text += "游戏似乎陷入了僵局，即将重置";
    }

    if (allClear() || getHint().first == nullptr) {
        text += "\n你的游戏总用时为 ";
        QString pattern = "h 小时 m 分钟 s 秒";
        if (this->control.timerText->timerTime.hour() == 0) {
            pattern = "m 分钟 s 秒";
            if (this->control.timerText->timerTime.minute() == 0) {
                pattern = "s 秒";
            }
        }
        text += this->control.timerText->timerTime.toString(pattern);
        this->control.timerText->end();
        QMessageBox::information(nullptr, title, text, QMessageBox::Ok, QMessageBox::Ok);
        this->setPaused(true);
        this->refreshMap();
    }
}

bool Game::allClear() {
    for (const auto &item: cleared) {
        if (!item) return false;
    }

    return true;
}

std::pair<Fruit *, Fruit *> Game::getHint() {
    for (const auto &item1: gridItems) {
        if (isCleared(item1->x, item1->y)) continue;

        for (const auto &item2: gridItems) {
            if (isCleared(item2->x, item2->y)) continue;

            if (item2->x == item1->x && item2->y == item1->y) continue;

            if (item1->kind == item2->kind && canLink(item1->x, item1->y, item2->x, item2->y, false))
                return {item1, item2};
        }
    }

    return {nullptr, nullptr};
}

QPoint Game::mapFromGameGrid(int x, int y) {
    return {
        20 + x * 40 + 20,
        20 + y * 40 + 20
    };
}

QString Game::translateModeName(int mode) {
    switch (mode) {
        case BASIC_MODE: return "基本模式";
        case CASUAL_MODE: return "休闲模式";
        case LEVEL_MODE: return "关卡模式";
        default: return "";
    }
}
