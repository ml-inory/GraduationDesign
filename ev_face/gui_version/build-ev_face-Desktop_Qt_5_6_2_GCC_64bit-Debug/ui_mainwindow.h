/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_open_video;
    QAction *action_open_camera;
    QAction *action_exit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *video_label;
    QSlider *video_slider;
    QHBoxLayout *horizontalLayout;
    QPushButton *video_backward;
    QPushButton *video_play_pause;
    QPushButton *video_forward;
    QTabWidget *tabWidget;
    QWidget *Detection;
    QWidget *Align;
    QWidget *Identify;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(823, 534);
        action_open_video = new QAction(MainWindow);
        action_open_video->setObjectName(QStringLiteral("action_open_video"));
        action_open_camera = new QAction(MainWindow);
        action_open_camera->setObjectName(QStringLiteral("action_open_camera"));
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName(QStringLiteral("action_exit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        video_label = new QLabel(centralWidget);
        video_label->setObjectName(QStringLiteral("video_label"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(video_label->sizePolicy().hasHeightForWidth());
        video_label->setSizePolicy(sizePolicy);
        video_label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(video_label);

        video_slider = new QSlider(centralWidget);
        video_slider->setObjectName(QStringLiteral("video_slider"));
        video_slider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(video_slider);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        video_backward = new QPushButton(centralWidget);
        video_backward->setObjectName(QStringLiteral("video_backward"));

        horizontalLayout->addWidget(video_backward);

        video_play_pause = new QPushButton(centralWidget);
        video_play_pause->setObjectName(QStringLiteral("video_play_pause"));

        horizontalLayout->addWidget(video_play_pause);

        video_forward = new QPushButton(centralWidget);
        video_forward->setObjectName(QStringLiteral("video_forward"));

        horizontalLayout->addWidget(video_forward);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        Detection = new QWidget();
        Detection->setObjectName(QStringLiteral("Detection"));
        tabWidget->addTab(Detection, QString());
        Align = new QWidget();
        Align->setObjectName(QStringLiteral("Align"));
        tabWidget->addTab(Align, QString());
        Identify = new QWidget();
        Identify->setObjectName(QStringLiteral("Identify"));
        tabWidget->addTab(Identify, QString());

        horizontalLayout_2->addWidget(tabWidget);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 823, 20));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(action_open_video);
        menuFile->addAction(action_open_camera);
        menuFile->addAction(action_exit);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action_open_video->setText(QApplication::translate("MainWindow", "Open Video", 0));
        action_open_camera->setText(QApplication::translate("MainWindow", "Open Camera", 0));
        action_exit->setText(QApplication::translate("MainWindow", "Close", 0));
        video_label->setText(QString());
        video_backward->setText(QApplication::translate("MainWindow", "<<", 0));
        video_backward->setShortcut(QApplication::translate("MainWindow", "Left", 0));
        video_play_pause->setText(QApplication::translate("MainWindow", "Play", 0));
        video_play_pause->setShortcut(QApplication::translate("MainWindow", "Space", 0));
        video_forward->setText(QApplication::translate("MainWindow", ">>", 0));
        video_forward->setShortcut(QApplication::translate("MainWindow", "Right", 0));
        tabWidget->setTabText(tabWidget->indexOf(Detection), QApplication::translate("MainWindow", "Detection", 0));
        tabWidget->setTabText(tabWidget->indexOf(Align), QApplication::translate("MainWindow", "Align", 0));
        tabWidget->setTabText(tabWidget->indexOf(Identify), QApplication::translate("MainWindow", "Identify", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
