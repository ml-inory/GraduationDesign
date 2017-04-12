#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

// external
#include <glog/logging.h>
#include "Cap_Controller.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_exit_triggered();

    void on_action_open_camera_triggered();

    void on_action_open_video_triggered();

    void on_video_backward_clicked();

    void on_video_forward_clicked();

    void on_video_slider_valueChanged(int position);

    void play_video();

    void on_video_play_pause_clicked();

private:
    void init_glog();
    void init_cap();
    bool get_frame();

    Ui::MainWindow *ui;
    ev::Cap_Controller cap_;

    int fps_;

    bool is_playing_ = false;

    QTimer timer_;
};

#endif // MAINWINDOW_H
