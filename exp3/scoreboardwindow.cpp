#include "scoreboardwindow.h"

#include "GlobalData.h"
#include "TimerText.h"
#include "ui_ScoreboardWindow.h"

typedef QTableWidgetItem item;

ScoreboardWindow::ScoreboardWindow(QWidget *parent) : QWidget(parent), ui(new Ui::ScoreboardWindow) {
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(0, 70);
    ui->tableWidget->setColumnWidth(1, 40);
    ui->tableWidget->setColumnWidth(2, 65);
}

ScoreboardWindow::~ScoreboardWindow() {
    delete ui;
}

void ScoreboardWindow::addTableRow(const Record &record) const {
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    int currentRow = ui->tableWidget->rowCount() - 1;

    const auto timeWidget = new item(QTime(0, 0, 0).addSecs(record.time).toString("hh:mm:ss"));
    timeWidget->setData(Qt::UserRole, QVariant::fromValue(record.time)); // for sort

    ui->tableWidget->setItem(currentRow, 0, timeWidget);

    ui->tableWidget->setItem(currentRow, 1, new item(record.name.data()));
    ui->tableWidget->setItem(currentRow, 2,
                             new item(Game::translateModeName(record.mode)));

    const auto finishedAtWidget = new item(
        QDateTime::fromMSecsSinceEpoch(record.finishedAt).toString("yyyy-MM-dd hh:mm:ss"));
    finishedAtWidget->setData(Qt::UserRole, QVariant::fromValue(record.finishedAt)); // for sort

    ui->tableWidget->setItem(currentRow, 3, finishedAtWidget);
}

void ScoreboardWindow::refreshTableData() const {
    ui->tableWidget->clear();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    auto records = global.recordManager->getRecords();
    for (const auto &record: records) {
        addTableRow(record);
    }
}

void ScoreboardWindow::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);

    ui->tableWidget->setSortingEnabled(false);
    refreshTableData();
    ui->tableWidget->setHorizontalHeaderLabels({"总用时", "昵称", "模式", "完成时间"});
    ui->tableWidget->sortItems(0);
    ui->tableWidget->setSortingEnabled(true);
}
