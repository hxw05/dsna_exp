#include "TimerText.h"

TimerText::TimerText(QLabel *target) : targetLabel(target) {
    timerTime = QTime(0, 0, 0, 0);
    timer = new QTimer();
    timer->connect(timer, &QTimer::timeout, timer, [this]() { this->main(); });
}

void TimerText::start() const {
    timer->start(1000);
}

void TimerText::end() const {
    timer->stop();
}

void TimerText::main() {
    timerTime = timerTime.addSecs(1);
    targetLabel->setText(timerTime.toString("hh:mm:ss"));
}

void TimerText::reset() {
    this->timerTime.setHMS(0, 0, 0, 0);
    targetLabel->setText(timerTime.toString("hh:mm:ss"));
}
