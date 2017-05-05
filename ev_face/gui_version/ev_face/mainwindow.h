#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QResizeEvent>
#include <QProgressDialog>
#include <QIODevice>

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

    void on_detection_browse_btn_clicked();

    void on_detection_show_checkbox_clicked(bool checked);

    void on_align_switch_checkbox_clicked(bool checked);

    void on_align_show_checkbox_clicked(bool checked);

    void on_id_switch_checkbox_clicked(bool checked);

    void on_id_browse_btn_clicked();

    void on_gen_btn_clicked();

    void on_snapshot_btn_clicked();

    void on_verify_btn_clicked(bool checked);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void init_glog();
    void init_cap();
    void init_verify_target_combo();
    bool get_frame();
    QPixmap mat_to_pixmap(cv::Mat& src_img, int dst_width = 0);
    cv::Mat image_to_mat(QImage& src_img);
    void add_array(float (&src_array)[2048], float (&dst_array)[2048]);
    void avg_array(float (&src_array)[2048], float (&dst_array)[2048], float avg_num);
    int verify(seeta::ImageData img_color_data, std::vector<seeta::FacialLandmark>& llpoints, QString& verify_target, float thresh = 0.5);
    bool read_target_features(QString& verify_target, float (&dst_array)[2048]);

    Ui::MainWindow *ui;

    ev::Cap_Controller cap_;

    std::shared_ptr<ev::Face_Detector> face_detector_;
    std::shared_ptr<ev::Face_Aligner> face_aligner_;
    std::shared_ptr<ev::Face_Identifier> face_identifier_;

    FacialLandmark pt5_[5];

    int fps_;

    float verify_thresh_;

    bool is_playing_;
    bool is_detection_model_loaded_;
    bool is_draw_detection_result_;
    bool is_aligner_model_loaded_;
    bool is_draw_align_result_;
    bool is_identifier_model_loaded_;
    bool is_verify_start_;

    QTimer timer_;

    const QString feature_root_ = "/Users/rzyang/GraduationDesign/ev_face/gui_version/build/features/";
    const QString image_root_ = "/Users/rzyang/GraduationDesign/ev_face/gui_version/build/images/";
};

#endif // MAINWINDOW_H
