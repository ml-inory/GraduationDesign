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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
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
    QGridLayout *gridLayout_2;
    QLineEdit *detection_model_lineedit;
    QPushButton *detection_browse_btn;
    QCheckBox *detection_switch_checkbox;
    QLabel *label;
    QCheckBox *detection_show_checkbox;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *Align;
    QGridLayout *gridLayout_4;
    QPushButton *align_browse_btn;
    QLabel *label_2;
    QLineEdit *align_model_lineedit;
    QCheckBox *align_switch_checkbox;
    QCheckBox *align_show_checkbox;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QWidget *Identify;
    QGridLayout *gridLayout_6;
    QLineEdit *id_model_lineedit;
    QLabel *label_3;
    QCheckBox *id_switch_checkbox;
    QPushButton *id_browse_btn;
    QTabWidget *toolkit_tagwidget;
    QWidget *Crop;
    QGridLayout *gridLayout;
    QLineEdit *target_name_lineedit;
    QPushButton *snapshot_btn;
    QPushButton *gen_btn;
    QLabel *label_4;
    QLabel *snapshot_label;
    QWidget *Verify;
    QGridLayout *gridLayout_3;
    QComboBox *verify_target_combo;
    QPushButton *verify_btn;
    QLabel *label_5;
    QLabel *label_6;
    QSpacerItem *verticalSpacer;
    QDoubleSpinBox *verify_thresh_text;
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
        video_label->setScaledContents(true);
        video_label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(video_label);

        video_slider = new QSlider(centralWidget);
        video_slider->setObjectName(QStringLiteral("video_slider"));
        video_slider->setMaximum(99);
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
        tabWidget->setEnabled(true);
        Detection = new QWidget();
        Detection->setObjectName(QStringLiteral("Detection"));
        gridLayout_2 = new QGridLayout(Detection);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        detection_model_lineedit = new QLineEdit(Detection);
        detection_model_lineedit->setObjectName(QStringLiteral("detection_model_lineedit"));
        detection_model_lineedit->setReadOnly(false);

        gridLayout_2->addWidget(detection_model_lineedit, 3, 0, 1, 1);

        detection_browse_btn = new QPushButton(Detection);
        detection_browse_btn->setObjectName(QStringLiteral("detection_browse_btn"));
        detection_browse_btn->setEnabled(true);

        gridLayout_2->addWidget(detection_browse_btn, 4, 0, 1, 1);

        detection_switch_checkbox = new QCheckBox(Detection);
        detection_switch_checkbox->setObjectName(QStringLiteral("detection_switch_checkbox"));

        gridLayout_2->addWidget(detection_switch_checkbox, 0, 0, 1, 1);

        label = new QLabel(Detection);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 2, 0, 1, 1);

        detection_show_checkbox = new QCheckBox(Detection);
        detection_show_checkbox->setObjectName(QStringLiteral("detection_show_checkbox"));
        detection_show_checkbox->setEnabled(false);
        detection_show_checkbox->setChecked(true);

        gridLayout_2->addWidget(detection_show_checkbox, 1, 0, 1, 1);

        scrollArea = new QScrollArea(Detection);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 217, 270));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollArea, 5, 0, 1, 1);

        tabWidget->addTab(Detection, QString());
        Align = new QWidget();
        Align->setObjectName(QStringLiteral("Align"));
        Align->setEnabled(false);
        gridLayout_4 = new QGridLayout(Align);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        align_browse_btn = new QPushButton(Align);
        align_browse_btn->setObjectName(QStringLiteral("align_browse_btn"));
        align_browse_btn->setEnabled(false);

        gridLayout_4->addWidget(align_browse_btn, 4, 1, 1, 1);

        label_2 = new QLabel(Align);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_4->addWidget(label_2, 2, 1, 1, 1);

        align_model_lineedit = new QLineEdit(Align);
        align_model_lineedit->setObjectName(QStringLiteral("align_model_lineedit"));
        align_model_lineedit->setReadOnly(false);

        gridLayout_4->addWidget(align_model_lineedit, 3, 1, 1, 1);

        align_switch_checkbox = new QCheckBox(Align);
        align_switch_checkbox->setObjectName(QStringLiteral("align_switch_checkbox"));
        align_switch_checkbox->setEnabled(false);

        gridLayout_4->addWidget(align_switch_checkbox, 0, 1, 1, 1);

        align_show_checkbox = new QCheckBox(Align);
        align_show_checkbox->setObjectName(QStringLiteral("align_show_checkbox"));
        align_show_checkbox->setEnabled(false);
        align_show_checkbox->setChecked(true);

        gridLayout_4->addWidget(align_show_checkbox, 1, 1, 1, 1);

        scrollArea_2 = new QScrollArea(Align);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 217, 264));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        gridLayout_4->addWidget(scrollArea_2, 5, 1, 1, 1);

        tabWidget->addTab(Align, QString());
        Identify = new QWidget();
        Identify->setObjectName(QStringLiteral("Identify"));
        Identify->setEnabled(false);
        gridLayout_6 = new QGridLayout(Identify);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        id_model_lineedit = new QLineEdit(Identify);
        id_model_lineedit->setObjectName(QStringLiteral("id_model_lineedit"));

        gridLayout_6->addWidget(id_model_lineedit, 2, 0, 1, 1);

        label_3 = new QLabel(Identify);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setTextFormat(Qt::AutoText);

        gridLayout_6->addWidget(label_3, 1, 0, 1, 1);

        id_switch_checkbox = new QCheckBox(Identify);
        id_switch_checkbox->setObjectName(QStringLiteral("id_switch_checkbox"));

        gridLayout_6->addWidget(id_switch_checkbox, 0, 0, 1, 1);

        id_browse_btn = new QPushButton(Identify);
        id_browse_btn->setObjectName(QStringLiteral("id_browse_btn"));

        gridLayout_6->addWidget(id_browse_btn, 3, 0, 1, 1);

        toolkit_tagwidget = new QTabWidget(Identify);
        toolkit_tagwidget->setObjectName(QStringLiteral("toolkit_tagwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toolkit_tagwidget->sizePolicy().hasHeightForWidth());
        toolkit_tagwidget->setSizePolicy(sizePolicy1);
        Crop = new QWidget();
        Crop->setObjectName(QStringLiteral("Crop"));
        gridLayout = new QGridLayout(Crop);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        target_name_lineedit = new QLineEdit(Crop);
        target_name_lineedit->setObjectName(QStringLiteral("target_name_lineedit"));

        gridLayout->addWidget(target_name_lineedit, 0, 1, 1, 1);

        snapshot_btn = new QPushButton(Crop);
        snapshot_btn->setObjectName(QStringLiteral("snapshot_btn"));

        gridLayout->addWidget(snapshot_btn, 1, 0, 1, 2);

        gen_btn = new QPushButton(Crop);
        gen_btn->setObjectName(QStringLiteral("gen_btn"));

        gridLayout->addWidget(gen_btn, 3, 0, 1, 2);

        label_4 = new QLabel(Crop);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        snapshot_label = new QLabel(Crop);
        snapshot_label->setObjectName(QStringLiteral("snapshot_label"));
        snapshot_label->setScaledContents(true);

        gridLayout->addWidget(snapshot_label, 2, 0, 1, 2);

        toolkit_tagwidget->addTab(Crop, QString());
        Verify = new QWidget();
        Verify->setObjectName(QStringLiteral("Verify"));
        gridLayout_3 = new QGridLayout(Verify);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verify_target_combo = new QComboBox(Verify);
        verify_target_combo->setObjectName(QStringLiteral("verify_target_combo"));

        gridLayout_3->addWidget(verify_target_combo, 1, 1, 1, 1);

        verify_btn = new QPushButton(Verify);
        verify_btn->setObjectName(QStringLiteral("verify_btn"));
        verify_btn->setCheckable(true);

        gridLayout_3->addWidget(verify_btn, 3, 0, 1, 2);

        label_5 = new QLabel(Verify);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 1, 0, 1, 1);

        label_6 = new QLabel(Verify);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_3->addWidget(label_6, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(14, 36, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 4, 0, 1, 1);

        verify_thresh_text = new QDoubleSpinBox(Verify);
        verify_thresh_text->setObjectName(QStringLiteral("verify_thresh_text"));
        verify_thresh_text->setMaximum(1);
        verify_thresh_text->setSingleStep(0.1);
        verify_thresh_text->setValue(0.7);

        gridLayout_3->addWidget(verify_thresh_text, 2, 1, 1, 1);

        toolkit_tagwidget->addTab(Verify, QString());

        gridLayout_6->addWidget(toolkit_tagwidget, 4, 0, 1, 1);

        tabWidget->addTab(Identify, QString());

        horizontalLayout_2->addWidget(tabWidget);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 823, 22));
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

        tabWidget->setCurrentIndex(2);
        toolkit_tagwidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "EVFace v1.0", 0));
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
        detection_model_lineedit->setText(QApplication::translate("MainWindow", "/Users/rzyang/SeetaFaceEngine/FaceDetection/model/seeta_fd_frontal_v1.0.bin", 0));
        detection_browse_btn->setText(QApplication::translate("MainWindow", "\346\265\217\350\247\210", 0));
        detection_switch_checkbox->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257", 0));
        label->setText(QApplication::translate("MainWindow", "\346\250\241\345\236\213\350\267\257\345\276\204", 0));
        detection_show_checkbox->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\347\202\271\347\272\277\346\241\206", 0));
        tabWidget->setTabText(tabWidget->indexOf(Detection), QApplication::translate("MainWindow", "Detection", 0));
        align_browse_btn->setText(QApplication::translate("MainWindow", "\346\265\217\350\247\210", 0));
        label_2->setText(QApplication::translate("MainWindow", "\346\250\241\345\236\213\350\267\257\345\276\204", 0));
        align_model_lineedit->setText(QApplication::translate("MainWindow", "/Users/rzyang/SeetaFaceEngine/FaceAlignment/model/seeta_fa_v1.1.bin", 0));
        align_switch_checkbox->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257", 0));
        align_show_checkbox->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\347\202\271\347\272\277\346\241\206", 0));
        tabWidget->setTabText(tabWidget->indexOf(Align), QApplication::translate("MainWindow", "Align", 0));
        id_model_lineedit->setText(QApplication::translate("MainWindow", "/Users/rzyang/GraduationDesign/ev_face/for_caffe/EVFaceNet.bin", 0));
        label_3->setText(QApplication::translate("MainWindow", "\346\250\241\345\236\213\350\267\257\345\276\204:", 0));
        id_switch_checkbox->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257", 0));
        id_browse_btn->setText(QApplication::translate("MainWindow", "\346\265\217\350\247\210", 0));
        target_name_lineedit->setText(QApplication::translate("MainWindow", "rzyang", 0));
        snapshot_btn->setText(QApplication::translate("MainWindow", "\346\210\252\345\217\226", 0));
        gen_btn->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220", 0));
        label_4->setText(QApplication::translate("MainWindow", "\347\233\256\346\240\207\345\220\215\347\247\260\357\274\232", 0));
        snapshot_label->setText(QString());
        toolkit_tagwidget->setTabText(toolkit_tagwidget->indexOf(Crop), QApplication::translate("MainWindow", "Crop", 0));
        verify_btn->setText(QApplication::translate("MainWindow", "\345\257\271\346\257\224", 0));
        label_5->setText(QApplication::translate("MainWindow", "\347\233\256\346\240\207\345\220\215\347\247\260\357\274\232", 0));
        label_6->setText(QApplication::translate("MainWindow", "\345\210\244\345\210\253\351\230\210\345\200\274\357\274\232", 0));
        toolkit_tagwidget->setTabText(toolkit_tagwidget->indexOf(Verify), QApplication::translate("MainWindow", "Verify", 0));
        tabWidget->setTabText(tabWidget->indexOf(Identify), QApplication::translate("MainWindow", "Identify", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
