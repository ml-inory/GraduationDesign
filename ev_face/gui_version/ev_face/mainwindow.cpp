#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init_glog();
    init_cap();

    connect(&timer_, SIGNAL(timeout()), this, SLOT(play_video()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Private */
void MainWindow::init_glog()    // 初始化glog
{
    google::InitGoogleLogging("");
    google::SetStderrLogging(google::GLOG_INFO);
    FLAGS_colorlogtostderr = true; // show logging color
    google::SetLogDestination(google::GLOG_FATAL, "../log/log_fatal_"); // log prefix
    google::SetLogDestination(google::GLOG_WARNING, "../log/log_warning_");
    google::SetLogDestination(google::GLOG_ERROR, "../log/log_error_");
    google::SetLogDestination(google::GLOG_INFO, "../log/log_info_");
    FLAGS_logbufsecs = 0; // output immediately
    FLAGS_max_log_size = 100; // 100M log size
    FLAGS_stop_logging_if_full_disk = true; // do not write log if disk full
}

void MainWindow::init_cap()     // 初始化Cap_Controller
{
    cap_.set_resize_thresh(1024);
    cap_.set_resize_factor(0.5, 0.5);
}

bool MainWindow::get_frame()    // 读取一帧并显示
{
    if(cap_.isOpened())
    {
        cv::Mat tmp;
        bool ret = cap_.read(tmp, true);      // true means BGR2RGB
        QImage image = QImage((const unsigned char*)tmp.data, tmp.cols, tmp.rows, QImage::Format_RGB888).scaledToWidth(ui->video_label->width());
        ui->video_label->setPixmap(QPixmap::fromImage(image));
        return ret;
    }
    else
        return false;
}



/* Slots */
void MainWindow::on_action_open_video_triggered()   // 打开视频
{
    QFileDialog* file_dialog = new QFileDialog(this);
    file_dialog->setWindowTitle(tr("Open Video"));
    file_dialog->setDirectory(".");
    if(file_dialog->exec() == QDialog::Accepted)
    {
        QString file_path = file_dialog->selectedFiles()[0];
        LOG(INFO) << "Video path: " << file_path.toStdString();
        cap_.open(file_path.toStdString());
        if(cap_.isOpened())
        {
            // init video_label
            get_frame();
            fps_ = (int)cap_.get(cv::CAP_PROP_FPS);
            if(fps_ <= 0) fps_ = 25;
            LOG(INFO) << "fps: " << fps_;

            // init video_slider
            int k = 0, total_frames = cap_.get_total_frames();
            while(total_frames)
            {
                total_frames = total_frames / 10;
                k++;
            }
            ui->video_slider->setMaximum(std::pow(10, k-1));
        }
        else
        {
            QMessageBox::warning(this, "Error", QString("Cannot open ") + file_path, QMessageBox::Yes);
        }
    }
}

void MainWindow::on_action_open_camera_triggered()  // 打开摄像头
{

}

void MainWindow::on_action_exit_triggered() // 关闭窗口
{
    this->close();
}

void MainWindow::on_video_backward_clicked()    // 左移进度条
{
    if(cap_.isOpened() && !cap_.is_opened_camera())
    {
        // Move slider
        int new_value;
        if(ui->video_slider->value() - ui->video_slider->minimum() >= ui->video_slider->singleStep())
        {
            new_value = ui->video_slider->value() - ui->video_slider->singleStep();
        }
        else
        {
            new_value = 0;
        }
        ui->video_slider->setValue(new_value);
    }
}

void MainWindow::on_video_forward_clicked()     // 右移进度条
{
    if(cap_.isOpened() && !cap_.is_opened_camera())
    {
        // Move slider
        int new_value;
        if(ui->video_slider->maximum() - ui->video_slider->value() - 1 >= ui->video_slider->singleStep())
        {
            new_value = ui->video_slider->value() + ui->video_slider->singleStep();
        }
        else
        {
            new_value = ui->video_slider->maximum() - 1;
        }
        ui->video_slider->setValue(new_value);
    }
}

void MainWindow::on_video_slider_valueChanged(int position)     // 移动或拖动进度条
{
    if(cap_.isOpened())
    {
        double new_pos_frame = 0;
        if(!cap_.is_opened_camera())
        {
            double max_value = (double)ui->video_slider->maximum() + 1;
            double pos_frame_ratio = double(position) / max_value;
            new_pos_frame = pos_frame_ratio * cap_.get_total_frames();
            cap_.set(cv::CAP_PROP_POS_FRAMES, new_pos_frame);
        }
        if(get_frame())     LOG_IF(INFO, !cap_.is_opened_camera()) << "Reading frame " << (int)new_pos_frame;
        else    LOG_IF(ERROR, !cap_.is_opened_camera()) << "Read frame " << (int)new_pos_frame << "ERROR";
    }
}

void MainWindow::play_video()       // 播放
{
    if(cap_.isOpened())
    {
        if(!cap_.is_opened_camera())
        {
            if(cap_.get_pos_frame() < cap_.get_total_frames() - 1)  // Not to the end
            {
                // Move slider
                int value = ui->video_slider->value();
                int step = ui->video_slider->singleStep();
                int max_value = ui->video_slider->maximum();
                if(max_value - value >= step)
                    ui->video_slider->setValue(value + step);
                else
                    ui->video_slider->setValue(max_value - 1);
            }
        }
        else
            on_video_slider_valueChanged(-1);
    }
}

void MainWindow::on_video_play_pause_clicked()      // 点播放键
{
    is_playing_ = !is_playing_;

    // set text
    QString btnText = is_playing_ ? QString("Pause") : QString("Play");
    ui->video_play_pause->setText(btnText);

    // disable or enable others
    ui->video_backward->setEnabled(!is_playing_);
    ui->video_forward->setEnabled(!is_playing_);
    ui->video_slider->setEnabled(!is_playing_);

    if(cap_.isOpened() && is_playing_)
    {
        // start timer
        int interval = (int)(1000.0 / fps_);
        timer_.start(interval);
    }
    else
    {
        timer_.stop();
    }
}

void MainWindow::on_detection_switch_checkbox_clicked(bool checked)
{
    ui->detection_show_checkbox->setEnabled(checked);

    if(checked)     // start to detect
    {
        // register Face_Detector
        QString model_path = ui->detection_model_lineedit->text();
        if(!model_path.endsWith(".bin"))
        {
            QMessageBox::warning(this, "Error", QString("Model path NOT right!"), QMessageBox::Yes);
            ui->detection_switch_checkbox->setChecked(false);
            on_detection_switch_checkbox_clicked(false);
        }
        ev::Face_Detector face_detector(model_path.toStdString());

    }
}
