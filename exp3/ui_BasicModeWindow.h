/********************************************************************************
** Form generated from reading UI file 'BasicModeWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASICMODEWINDOW_H
#define UI_BASICMODEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BasicModeWindow
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *startGameBtn;
    QPushButton *pauseGameBtn;
    QPushButton *hintBtn;
    QPushButton *rearrangeBtn;
    QLabel *timerLabel;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;

    void setupUi(QWidget *BasicModeWindow)
    {
        if (BasicModeWindow->objectName().isEmpty())
            BasicModeWindow->setObjectName("BasicModeWindow");
        BasicModeWindow->resize(800, 600);
        BasicModeWindow->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"background-color: white;\n"
"border: 1px solid black;\n"
"color: black;\n"
"border-radius: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"background-color: #eee;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"background-color:#ccc;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"background-color: #ddd;\n"
"color: #aaa;\n"
"border-color: #aaa;\n"
"}"));
        verticalLayoutWidget = new QWidget(BasicModeWindow);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(669, 20, 111, 251));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        startGameBtn = new QPushButton(verticalLayoutWidget);
        startGameBtn->setObjectName("startGameBtn");
        startGameBtn->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(startGameBtn);

        pauseGameBtn = new QPushButton(verticalLayoutWidget);
        pauseGameBtn->setObjectName("pauseGameBtn");
        pauseGameBtn->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(pauseGameBtn);

        hintBtn = new QPushButton(verticalLayoutWidget);
        hintBtn->setObjectName("hintBtn");
        hintBtn->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(hintBtn);

        rearrangeBtn = new QPushButton(verticalLayoutWidget);
        rearrangeBtn->setObjectName("rearrangeBtn");
        rearrangeBtn->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(rearrangeBtn);

        timerLabel = new QLabel(verticalLayoutWidget);
        timerLabel->setObjectName("timerLabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("Helvetica")});
        font.setPointSize(24);
        timerLabel->setFont(font);
        timerLabel->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        timerLabel->setStyleSheet(QString::fromUtf8("color: black"));
        timerLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        timerLabel->setMargin(0);

        verticalLayout->addWidget(timerLabel);

        verticalLayoutWidget_2 = new QWidget(BasicModeWindow);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(700, 520, 81, 61));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(verticalLayoutWidget_2);
        pushButton->setObjectName("pushButton");

        verticalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(verticalLayoutWidget_2);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout_2->addWidget(pushButton_2);

        gridLayoutWidget = new QWidget(BasicModeWindow);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(20, 20, 640, 400));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
#if QT_CONFIG(shortcut)
#endif // QT_CONFIG(shortcut)

        retranslateUi(BasicModeWindow);

        QMetaObject::connectSlotsByName(BasicModeWindow);
    } // setupUi

    void retranslateUi(QWidget *BasicModeWindow)
    {
        BasicModeWindow->setWindowTitle(QCoreApplication::translate("BasicModeWindow", "\346\254\242\344\271\220\350\277\236\350\277\236\347\234\213\342\200\224\342\200\224\345\237\272\346\234\254\346\250\241\345\274\217", nullptr));
        startGameBtn->setText(QCoreApplication::translate("BasicModeWindow", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        pauseGameBtn->setText(QCoreApplication::translate("BasicModeWindow", "\346\232\202\345\201\234\346\270\270\346\210\217", nullptr));
        hintBtn->setText(QCoreApplication::translate("BasicModeWindow", "\346\217\220\347\244\272", nullptr));
        rearrangeBtn->setText(QCoreApplication::translate("BasicModeWindow", "\351\207\215\346\216\222", nullptr));
        timerLabel->setText(QCoreApplication::translate("BasicModeWindow", "00:00:00", nullptr));
        pushButton->setText(QCoreApplication::translate("BasicModeWindow", "\350\256\276\347\275\256", nullptr));
        pushButton_2->setText(QCoreApplication::translate("BasicModeWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BasicModeWindow: public Ui_BasicModeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASICMODEWINDOW_H
