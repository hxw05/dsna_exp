#ifndef DSNA_3_QT_FRUIT_H
#define DSNA_3_QT_FRUIT_H

#include <QPushButton>

class Fruit : public QPushButton {
public:
    int x;
    int y;
    int kind;
    bool isClicked;

    explicit Fruit(QWidget *parent = nullptr) : QPushButton(parent), x(-1), y(-1), kind(-1), isClicked(false) {};

    explicit Fruit(QWidget *parent = nullptr, int xx = -1, int yy = -1, int kindd = -1) : QPushButton(parent), x(xx),
                                                                                          y(yy), kind(kindd),
                                                                                          isClicked(false) {};

    void onClick();

    void setClicked(bool val);
};

#endif //DSNA_3_QT_FRUIT_H
