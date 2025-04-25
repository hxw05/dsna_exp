#ifndef SCOREBOARDWINDOW_H
#define SCOREBOARDWINDOW_H

#include <QWidget>

#include "RecordManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ScoreboardWindow; }
QT_END_NAMESPACE

class ScoreboardWindow : public QWidget {
Q_OBJECT

public:
    explicit ScoreboardWindow(QWidget *parent = nullptr);
    ~ScoreboardWindow() override;

    void addTableRow(const Record &record) const;

    void refreshTableData() const;

    void showEvent(QShowEvent *event) override;

private:
    Ui::ScoreboardWindow *ui;
};


#endif
