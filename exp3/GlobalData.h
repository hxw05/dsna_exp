#ifndef DSNA_3_QT_QGLOBAL_H
#define DSNA_3_QT_QGLOBAL_H

#include <map>
#include <string>
#include "Game.h"

#define BG_FILE "resources/fruit_bg.bmp"

class GlobalData {
public:
    std::map<std::string, QWidget *> windows;
    Game *basicModeGame;
    QString username;
    RecordManager* recordManager;

    GlobalData();

    void addWindow(const std::string &key, QWidget *window);

    QWidget *getWindow(const std::string &key);

    std::string getUsername() const;
};

extern GlobalData global;

#endif
