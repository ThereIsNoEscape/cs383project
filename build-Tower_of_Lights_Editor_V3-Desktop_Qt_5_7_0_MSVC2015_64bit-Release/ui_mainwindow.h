/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QFrame *frame;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QPushButton *cell001;
    QPushButton *cell002;
    QPushButton *cell004;
    QPushButton *cell005;
    QPushButton *cell006;
    QPushButton *cell007;
    QPushButton *cell003;
    QPushButton *cell009;
    QPushButton *cell000;
    QPushButton *cell008;
    QPushButton *cell010;
    QPushButton *cell011;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(892, 510);
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 861, 451));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setMinimumSize(QSize(72, 18));
        pushButton->setMaximumSize(QSize(128, 24));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1, Qt::AlignTop);

        frame = new QFrame(gridLayoutWidget);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy2);
        frame->setMinimumSize(QSize(168, 280));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(3);
        gridLayoutWidget_2 = new QWidget(frame);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(9, 9, 761, 431));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        cell001 = new QPushButton(gridLayoutWidget_2);
        cell001->setObjectName(QStringLiteral("cell001"));
        sizePolicy2.setHeightForWidth(cell001->sizePolicy().hasHeightForWidth());
        cell001->setSizePolicy(sizePolicy2);
        cell001->setMinimumSize(QSize(10, 10));
        cell001->setProperty("coord", QVariant(0u));

        gridLayout_2->addWidget(cell001, 0, 1, 1, 1);

        cell002 = new QPushButton(gridLayoutWidget_2);
        cell002->setObjectName(QStringLiteral("cell002"));
        sizePolicy2.setHeightForWidth(cell002->sizePolicy().hasHeightForWidth());
        cell002->setSizePolicy(sizePolicy2);
        cell002->setMinimumSize(QSize(10, 10));
        cell002->setProperty("coord", QVariant(0u));

        gridLayout_2->addWidget(cell002, 0, 2, 1, 1);

        cell004 = new QPushButton(gridLayoutWidget_2);
        cell004->setObjectName(QStringLiteral("cell004"));
        sizePolicy2.setHeightForWidth(cell004->sizePolicy().hasHeightForWidth());
        cell004->setSizePolicy(sizePolicy2);
        cell004->setMinimumSize(QSize(10, 10));
        cell004->setProperty("coord", QVariant(0u));

        gridLayout_2->addWidget(cell004, 0, 4, 1, 1);

        cell005 = new QPushButton(gridLayoutWidget_2);
        cell005->setObjectName(QStringLiteral("cell005"));
        sizePolicy2.setHeightForWidth(cell005->sizePolicy().hasHeightForWidth());
        cell005->setSizePolicy(sizePolicy2);
        cell005->setMinimumSize(QSize(10, 10));
        cell005->setProperty("coord", QVariant(0u));

        gridLayout_2->addWidget(cell005, 0, 5, 1, 1);

        cell006 = new QPushButton(gridLayoutWidget_2);
        cell006->setObjectName(QStringLiteral("cell006"));
        sizePolicy2.setHeightForWidth(cell006->sizePolicy().hasHeightForWidth());
        cell006->setSizePolicy(sizePolicy2);
        cell006->setMinimumSize(QSize(10, 10));
        cell006->setProperty("coord", QVariant(0u));

        gridLayout_2->addWidget(cell006, 0, 6, 1, 1);

        cell007 = new QPushButton(gridLayoutWidget_2);
        cell007->setObjectName(QStringLiteral("cell007"));
        sizePolicy2.setHeightForWidth(cell007->sizePolicy().hasHeightForWidth());
        cell007->setSizePolicy(sizePolicy2);
        cell007->setMinimumSize(QSize(10, 10));
        cell007->setProperty("coord", QVariant(0u));

        gridLayout_2->addWidget(cell007, 0, 7, 1, 1);

        cell003 = new QPushButton(gridLayoutWidget_2);
        cell003->setObjectName(QStringLiteral("cell003"));
        sizePolicy2.setHeightForWidth(cell003->sizePolicy().hasHeightForWidth());
        cell003->setSizePolicy(sizePolicy2);
        cell003->setMinimumSize(QSize(10, 10));
        cell003->setProperty("coord", QVariant(0u));

        gridLayout_2->addWidget(cell003, 0, 3, 1, 1);

        cell009 = new QPushButton(gridLayoutWidget_2);
        cell009->setObjectName(QStringLiteral("cell009"));
        sizePolicy2.setHeightForWidth(cell009->sizePolicy().hasHeightForWidth());
        cell009->setSizePolicy(sizePolicy2);
        cell009->setMinimumSize(QSize(10, 10));
        cell009->setProperty("coord", QVariant(0u));

        gridLayout_2->addWidget(cell009, 0, 9, 1, 1);

        cell000 = new QPushButton(gridLayoutWidget_2);
        cell000->setObjectName(QStringLiteral("cell000"));
        sizePolicy2.setHeightForWidth(cell000->sizePolicy().hasHeightForWidth());
        cell000->setSizePolicy(sizePolicy2);
        cell000->setMinimumSize(QSize(10, 10));
        cell000->setProperty("coord", QVariant(0u));

        gridLayout_2->addWidget(cell000, 0, 0, 1, 1);

        cell008 = new QPushButton(gridLayoutWidget_2);
        cell008->setObjectName(QStringLiteral("cell008"));
        sizePolicy2.setHeightForWidth(cell008->sizePolicy().hasHeightForWidth());
        cell008->setSizePolicy(sizePolicy2);
        cell008->setMinimumSize(QSize(10, 10));
        cell008->setProperty("coord", QVariant(0u));

        gridLayout_2->addWidget(cell008, 0, 8, 1, 1);

        cell010 = new QPushButton(gridLayoutWidget_2);
        cell010->setObjectName(QStringLiteral("cell010"));
        sizePolicy2.setHeightForWidth(cell010->sizePolicy().hasHeightForWidth());
        cell010->setSizePolicy(sizePolicy2);
        cell010->setMinimumSize(QSize(10, 10));
        cell010->setProperty("coord", QVariant(0u));

        gridLayout_2->addWidget(cell010, 0, 10, 1, 1);

        cell011 = new QPushButton(gridLayoutWidget_2);
        cell011->setObjectName(QStringLiteral("cell011"));
        sizePolicy2.setHeightForWidth(cell011->sizePolicy().hasHeightForWidth());
        cell011->setSizePolicy(sizePolicy2);
        cell011->setMinimumSize(QSize(10, 10));
        cell011->setProperty("coord", QVariant(0u));

        gridLayout_2->addWidget(cell011, 0, 11, 1, 1);


        gridLayout->addWidget(frame, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 892, 17));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Tower of Lights v3.0", 0));
        pushButton->setText(QApplication::translate("MainWindow", "open", 0));
        cell001->setText(QApplication::translate("MainWindow", "1", 0));
        cell001->setProperty("activated", QVariant(QApplication::translate("MainWindow", "false", 0)));
        cell002->setText(QApplication::translate("MainWindow", "2", 0));
        cell002->setProperty("activated", QVariant(QApplication::translate("MainWindow", "false", 0)));
        cell004->setText(QApplication::translate("MainWindow", "4", 0));
        cell004->setProperty("activated", QVariant(QApplication::translate("MainWindow", "false", 0)));
        cell005->setText(QApplication::translate("MainWindow", "5", 0));
        cell005->setProperty("activated", QVariant(QApplication::translate("MainWindow", "false", 0)));
        cell006->setText(QApplication::translate("MainWindow", "6", 0));
        cell006->setProperty("activated", QVariant(QApplication::translate("MainWindow", "false", 0)));
        cell007->setText(QApplication::translate("MainWindow", "7", 0));
        cell007->setProperty("activated", QVariant(QApplication::translate("MainWindow", "false", 0)));
        cell003->setText(QApplication::translate("MainWindow", "3", 0));
        cell003->setProperty("activated", QVariant(QApplication::translate("MainWindow", "false", 0)));
        cell009->setText(QApplication::translate("MainWindow", "9", 0));
        cell009->setProperty("activated", QVariant(QApplication::translate("MainWindow", "false", 0)));
        cell000->setText(QApplication::translate("MainWindow", "0", 0));
        cell000->setProperty("activated", QVariant(QApplication::translate("MainWindow", "false", 0)));
        cell008->setText(QApplication::translate("MainWindow", "8", 0));
        cell008->setProperty("activated", QVariant(QApplication::translate("MainWindow", "false", 0)));
        cell010->setText(QApplication::translate("MainWindow", "10", 0));
        cell010->setProperty("activated", QVariant(QApplication::translate("MainWindow", "false", 0)));
        cell011->setText(QApplication::translate("MainWindow", "11", 0));
        cell011->setProperty("activated", QVariant(QApplication::translate("MainWindow", "false", 0)));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
