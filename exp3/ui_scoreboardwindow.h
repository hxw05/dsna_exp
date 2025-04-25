/********************************************************************************
** Form generated from reading UI file 'scoreboardwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCOREBOARDWINDOW_H
#define UI_SCOREBOARDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScoreboardWindow
{
public:
    QTableWidget *tableWidget;

    void setupUi(QWidget *ScoreboardWindow)
    {
        if (ScoreboardWindow->objectName().isEmpty())
            ScoreboardWindow->setObjectName("ScoreboardWindow");
        ScoreboardWindow->resize(400, 300);
        tableWidget = new QTableWidget(ScoreboardWindow);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 403, 300));
        tableWidget->setMaximumSize(QSize(403, 300));
        tableWidget->setProperty("showDropIndicator", QVariant(false));
        tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
        tableWidget->setSortingEnabled(false);
        tableWidget->setColumnCount(4);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->horizontalHeader()->setStretchLastSection(true);

        retranslateUi(ScoreboardWindow);

        QMetaObject::connectSlotsByName(ScoreboardWindow);
    } // setupUi

    void retranslateUi(QWidget *ScoreboardWindow)
    {
        ScoreboardWindow->setWindowTitle(QCoreApplication::translate("ScoreboardWindow", "\346\216\222\350\241\214\346\246\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScoreboardWindow: public Ui_ScoreboardWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCOREBOARDWINDOW_H
