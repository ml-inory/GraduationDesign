#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QResizeEvent>

// external
#include <glog/logging.h>
#include "Cap_Controller.hpp"
#include "Seetaface.hpp"

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

    void on_detection_switch_checkbox_clicked(bool checked);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void init_glog();
    void init_cap();
    bool get_frame();

    Ui::MainWindow *ui;

    ev::Cap_Controller cap_;
    std::shared_ptr<ev::Face_Detector> face_detector_;

    int fps_;

    bool is_playing_ = false;
    bool is_detection_model_loaded_ = false;

    const std::string detection_model_path_ = "../../data/model/seeta_fd_frontal_v1.0.bin";

    QTimer timer_;
};

#endif // MAINWINDOW_H
