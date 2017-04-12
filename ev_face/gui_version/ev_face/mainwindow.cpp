#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init_glog();
    init_cap();
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
            cv::Mat tmp;
            cap_.read(tmp, true);      // true means BGR2RGB
            QImage image = QImage((const unsigned char*)tmp.data, tmp.cols, tmp.rows, QImage::Format_RGB888).scaledToWidth(ui->video_label->width());
            ui->video_label->setPixmap(QPixmap::fromImage(image));

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
        if(ui->video_slider->value() >= ui->video_slider->singleStep())
        {
            new_value = ui->video_slider->value() - ui->video_slider->singleStep();
        }
        else
        {
            new_value = 0;
        }
        ui->video_slider->setValue(new_value);
        LOG(INFO) << "Reading frame " << new_value;
    }
}
