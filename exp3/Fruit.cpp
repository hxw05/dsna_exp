#include "Fruit.h"
#include "iostream"
#include "GlobalData.h"
#include <QTimer>

using namespace std;

void Fruit::onClick() {
    auto *target = dynamic_cast<Fruit *>(sender());

    target->setClicked(!target->isClicked);
    global.basicModeGame->setClicked(target, target->isClicked);

    if (!global.basicModeGame->hasClickedPair()) return;
    auto clickedPair = global.basicModeGame->getClickedPair();
    global.basicModeGame->clearClicked();

    if (clickedPair.first == clickedPair.second) {
        cout << "debug: duplicate" << endl;
        return;
    }

    if (clickedPair.first->kind != clickedPair.second->kind) {
        cout << "debug: kind mismatch" << endl;
        return;
    }

    int linkState;

    if ((linkState = global.basicModeGame->canLink(clickedPair.first->x, clickedPair.first->y, clickedPair.second->x,
                                                    clickedPair.second->y))) {
        global.basicModeGame->setCleared(clickedPair.first);
        global.basicModeGame->setCleared(clickedPair.second);

        // 这两行花了三天才写出来
        // Cost me 3+ days' research in order to come up with these 2 lines.
        global.getWindow("basicModeWindow")->repaint();
        QTimer::singleShot(200, []() {
            global.getWindow("basicModeWindow")->repaint();
        });

        global.basicModeGame->onPairCleared();

        cout << "Link (" << clickedPair.first->x << ", " << clickedPair.first->y << ") and (" << clickedPair.second->x
                << ", " << clickedPair.second->y << "): typ " << linkState << endl;
    } else {
        cout << "Link (" << clickedPair.first->x << ", " << clickedPair.first->y << ") and (" << clickedPair.second->x
                << ", " << clickedPair.second->y << "): CANNOT " << endl;
    }
}

void Fruit::setClicked(bool val) {
    this->isClicked = val;

    if (val) {
        setStyleSheet("border: 2px dashed green; background: transparent");
    } else {
        setStyleSheet("border: none; background: transparent");
    }
}
