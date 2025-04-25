#ifndef DSNA_3_QT_BASICMODEWINDOW_H
#define DSNA_3_QT_BASICMODEWINDOW_H

#include "TimerText.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui {
    class BasicModeWindow;
}

QT_END_NAMESPACE

class BasicModeWindow : public QMainWindow {
    Q_OBJECT

public:
    TimerText *timerText;
    Ui::BasicModeWindow *ui;

    explicit BasicModeWindow(QMainWindow *parent = nullptr);

    ~BasicModeWindow() override;

public slots:
    void on_startGameBtn_clicked() const;

    void on_rearrangeBtn_clicked() const;

    void on_pauseGameBtn_clicked() const;

    void on_hintBtn_clicked();

private:
    void paintEvent(QPaintEvent *event) override;
};


#endif //DSNA_3_QT_BASICMODEWINDOW_H
