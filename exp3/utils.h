#ifndef DSNA_3_QT_UTILS_H
#define DSNA_3_QT_UTILS_H

#include <random>
#include <QWidget>

struct GenMapResult {
    std::vector<int> map;
    double neighborRate;
};

QPixmap getBackground(QWidget* window, const char* filename);
void setBackground(QWidget* window, const char* filename);
int randInt(int start, int end);
GenMapResult genMap(int width, int height, int fruitTypeCount, double neighborRate);
#endif //DSNA_3_QT_UTILS_H
