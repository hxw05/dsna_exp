/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *other_options;
    QPushButton *basicModeBtn;
    QPushButton *chillModeBtn;
    QPushButton *levelModeBtn;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *game_options;
    QPushButton *boardBtn;
    QPushButton *settingsBtn;
    QPushButton *helpBtn;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"}"));
        verticalLayoutWidget = new QWidget(MainWindow);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 190, 111, 331));
        other_options = new QVBoxLayout(verticalLayoutWidget);
        other_options->setObjectName("other_options");
        other_options->setContentsMargins(0, 0, 0, 0);
        basicModeBtn = new QPushButton(verticalLayoutWidget);
        basicModeBtn->setObjectName("basicModeBtn");
        basicModeBtn->setMinimumSize(QSize(0, 50));
        basicModeBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        basicModeBtn->setStyleSheet(QString::fromUtf8(""));
        basicModeBtn->setFlat(false);

        other_options->addWidget(basicModeBtn);

        chillModeBtn = new QPushButton(verticalLayoutWidget);
        chillModeBtn->setObjectName("chillModeBtn");
        chillModeBtn->setMinimumSize(QSize(0, 50));
        chillModeBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        chillModeBtn->setStyleSheet(QString::fromUtf8(""));

        other_options->addWidget(chillModeBtn);

        levelModeBtn = new QPushButton(verticalLayoutWidget);
        levelModeBtn->setObjectName("levelModeBtn");
        levelModeBtn->setMinimumSize(QSize(0, 50));
        levelModeBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        levelModeBtn->setStyleSheet(QString::fromUtf8(""));

        other_options->addWidget(levelModeBtn);

        horizontalLayoutWidget = new QWidget(MainWindow);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(580, 560, 211, 21));
        game_options = new QHBoxLayout(horizontalLayoutWidget);
        game_options->setObjectName("game_options");
        game_options->setContentsMargins(0, 0, 0, 0);
        boardBtn = new QPushButton(horizontalLayoutWidget);
        boardBtn->setObjectName("boardBtn");
        boardBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        boardBtn->setAutoFillBackground(false);
        boardBtn->setAutoDefault(false);
        boardBtn->setFlat(false);

        game_options->addWidget(boardBtn);

        settingsBtn = new QPushButton(horizontalLayoutWidget);
        settingsBtn->setObjectName("settingsBtn");
        settingsBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        settingsBtn->setAutoFillBackground(false);

        game_options->addWidget(settingsBtn);

        helpBtn = new QPushButton(horizontalLayoutWidget);
        helpBtn->setObjectName("helpBtn");
        helpBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        helpBtn->setAutoFillBackground(false);

        game_options->addWidget(helpBtn);


        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\254\242\344\271\220\350\277\236\350\277\236\347\234\213", nullptr));
        basicModeBtn->setText(QCoreApplication::translate("MainWindow", "\345\237\272\346\234\254\346\250\241\345\274\217", nullptr));
        chillModeBtn->setText(QCoreApplication::translate("MainWindow", "\344\274\221\351\227\262\346\250\241\345\274\217", nullptr));
        levelModeBtn->setText(QCoreApplication::translate("MainWindow", "\345\205\263\345\215\241\346\250\241\345\274\217", nullptr));
        boardBtn->setText(QCoreApplication::translate("MainWindow", "\346\216\222\350\241\214\346\246\234", nullptr));
        settingsBtn->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        helpBtn->setText(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
