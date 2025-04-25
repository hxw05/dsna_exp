#include "GlobalData.h"

GlobalData::GlobalData() {
    recordManager = new RecordManager("records.txt");
}

void GlobalData::addWindow(const std::string &key, QWidget *window) {
    windows.insert({key, window});
}

QWidget *GlobalData::getWindow(const std::string &key) {
    return windows[key];
}

std::string GlobalData::getUsername() const {
    return username.isEmpty() ? "默认玩家" : username.toStdString();
}
