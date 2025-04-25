#ifndef DSNA_3_QT_GAME_H
#define DSNA_3_QT_GAME_H

#include <QGridLayout>
#include <vector>
#include "utils.h"
#include "Fruit.h"
#include <QMainWindow>

#include "RecordManager.h"
#include "TimerText.h"

struct GameControl {
    QGridLayout* layout;
    TimerText* timerText;
    QPushButton* pauseGameBtn;
    QPushButton* hintBtn;
};

class Game {
public:
    GameControl control;
    int width;
    int height;
    int mode;
    bool paused = false;
    std::vector<bool> cleared;
    std::vector<QPixmap> fruitImages;
    std::vector<Fruit *> gridItems;
    std::vector<Fruit *> clicked;
    std::vector<std::pair<int, int> > paintPoints;
    std::pair<Fruit *, Fruit *> currentHint;

    static constexpr int LINK_CORNER1 = 1;
    static constexpr int LINK_CORNER2 = 2;
    static constexpr int LINK_CORNER3 = 3;

    static constexpr int BASIC_MODE = 1;
    static constexpr int CASUAL_MODE = 2;
    static constexpr int LEVEL_MODE = 3;

    explicit Game(int mode, int w, int h, const GameControl &controlObject);

    void initFruits();

    void refreshMap();

    void setPaused(bool isPaused);

    bool isCleared(int x, int y);

    void setCleared(int x, int y, bool isCleared);

    void setCleared(int x, int y);

    void setCleared(Fruit *fruit);

    bool canLinkCorner0(int x0, int y0, int x1, int y1, bool drawLine);

    bool canLinkCorner1(int x0, int y0, int x1, int y1, bool drawLine);

    bool canLinkCorner2(int x0, int y0, int x1, int y1, bool drawLine);

    int canLink(int x0, int y0, int x1, int y1, bool drawLine);

    int canLink(int x0, int y0, int x1, int y1);

    void setClicked(Fruit *target, bool isClicked);

    std::pair<Fruit *, Fruit *> getClickedPair();

    [[nodiscard]] bool hasClickedPair() const;

    void clearClicked();

    void onPairCleared();

    bool allClear();

    std::pair<Fruit *, Fruit *> getHint();

    static QPoint mapFromGameGrid(int x, int y);

    static QString translateModeName(int mode);

private:
    void initMap();

    void clearMap();

    void updateMap() const;
};


#endif
