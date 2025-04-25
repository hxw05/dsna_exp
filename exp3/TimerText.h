#ifndef DSNA_3_QT_TIMERTEXT_H
#define DSNA_3_QT_TIMERTEXT_H

#include <QTime>
#include <QTimer>
#include <QLabel>

class TimerText {
public:
    QTime timerTime;
    QLabel *targetLabel;
    QTimer *timer;

    bool resetMark = false;

    explicit TimerText(QLabel *target);

    void main();

    void start() const;

    void end() const;

    void reset();
};


#endif //DSNA_3_QT_TIMERTEXT_H
