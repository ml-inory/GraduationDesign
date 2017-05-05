#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    is_playing_(false),
    is_detection_model_loaded_(false),
    is_draw_detection_result_(true),
    is_aligner_model_loaded_(false),
    is_draw_align_result_(true),
    is_identifier_model_loaded_(false),
    is_verify_start_(false),
    verify_thresh_(0.5)
{
    ui->setupUi(this);

    init_glog();
    init_cap();
    init_verify_target_combo();

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

void MainWindow::init_verify_target_combo()
{
    // 遍历features目录
    QDir features_dir(QString("/Users/rzyang/GraduationDesign/ev_face/gui_version/build/features/"));
    features_dir.setFilter(QDir::Files | QDir::NoSymLinks);
    const QFileInfoList file_list = features_dir.entryInfoList();
    QFileInfoList::const_iterator iterator = file_list.begin();
    while(iterator != file_list.end())
    {
        QString file_name = (*iterator).fileName();
        file_name.remove(".features");
        //qDebug() << file_name;
        ui->verify_target_combo->addItem(file_name);
        ++iterator;
    }
}

bool MainWindow::get_frame()    // 读取一帧并显示
{
    if(cap_.isOpened())
    {
        // read frame
        cv::Mat tmp;
        cv::Mat origin_frame;
        cv::Mat gray_frame;
        bool ret = cap_.read(tmp, true);      // true means BGR2RGB
        if(ret) origin_frame = cap_.origin_frame_.clone();
        else    return false;

        // construct image data
        seeta::ImageData img_data(origin_frame.cols, origin_frame.rows, 1);
        seeta::ImageData img_color_data(origin_frame.cols, origin_frame.rows, 3);
        img_color_data.data = origin_frame.data;
        cv::cvtColor(origin_frame, gray_frame, cv::COLOR_RGB2GRAY);
        img_data.data = gray_frame.data;

        // detection
        if(is_detection_model_loaded_)
        {
           std::vector<seeta::FaceInfo> faces = face_detector_->detect(img_data);
           int face_num = static_cast<int>(faces.size());
           // draw
           cv::Rect face_rect;
           for(int i = 0; i < face_num; ++i)
           {
               face_rect.x = faces[i].bbox.x;
               face_rect.y = faces[i].bbox.y;
               face_rect.width = faces[i].bbox.width;
               face_rect.height = faces[i].bbox.height;
               //LOG(INFO) << "score: " << faces[i].score;
               if(is_draw_detection_result_)
                   cv::rectangle(origin_frame, face_rect, cv::Scalar(255,0,0), 2, 1, 0);
           }

           // alignment
           if(is_aligner_model_loaded_ && face_num > 0)
           {
               std::vector<FacialLandmark> face_feature_points;
               face_aligner_->detect_multi_landmarks(img_data, faces, face_feature_points);
               //LOG(INFO) << "Detected " << face_feature_points.size() << " points";

               for(int i = 0; i < face_feature_points.size(); ++i)
               {
                   // assign to pt5_
                   if(i < 5)    { pt5_[i].x = face_feature_points[i].x; pt5_[i].y = face_feature_points[i].y; }
                   // draw
                   if(is_draw_align_result_)
                   {
                       cv::Point center;
                       center.x = face_feature_points[i].x;
                       center.y = face_feature_points[i].y;
                       cv::circle(origin_frame, center, 3, cv::Scalar(0,0,255), -1);
                   }
               }

               // identification
               if(is_identifier_model_loaded_)
               {
                   ui->snapshot_btn->setEnabled(true);
               }

               // vertification
               if(is_verify_start_)
               {
                   QString verify_target = ui->verify_target_combo->currentText();
                   if(verify_target != QString(""))
                   {
                       int max_idx = verify(img_color_data, face_feature_points, verify_target, verify_thresh_);
                       // qDebug() << "max_idx: " << max_idx;
                       // Found match
                       if(max_idx != -1)
                       {
                           face_rect.x = faces[max_idx].bbox.x;
                           face_rect.y = faces[max_idx].bbox.y;
                           face_rect.width = faces[max_idx].bbox.width;
                           face_rect.height = faces[max_idx].bbox.height;
                           cv::rectangle(origin_frame, face_rect, cv::Scalar(0,255,0), 2, 1, 0);
                       }
                   }
               }

           }
           else
           {
               ui->snapshot_btn->setEnabled(false);
           }
        }

        QImage image = QImage((const unsigned char*)origin_frame.data, origin_frame.cols, origin_frame.rows, QImage::Format_RGB888).scaledToWidth(ui->video_label->width());
        ui->video_label->setPixmap(QPixmap::fromImage(image));

        return true;
    }
    else
        return false;
}

QPixmap MainWindow::mat_to_pixmap(Mat &src_img, int dst_width)
{
    QImage image = QImage((const unsigned char*)src_img.data, src_img.cols, src_img.rows, QImage::Format_RGB888);
    if(dst_width > 0)
        image = image.scaledToWidth(dst_width);
    return QPixmap::fromImage(image);
}

cv::Mat MainWindow::image_to_mat(QImage &src_img)
{
    src_img = src_img.convertToFormat(QImage::Format_RGB888);
    // src_img = src_img.rgbSwapped();
    return cv::Mat(src_img.height(), src_img.width(),
                   CV_8UC3,
                   const_cast<uchar*>(src_img.bits()),
                   static_cast<size_t>(src_img.bytesPerLine())
                   ).clone();
}

void MainWindow::add_array(float (&src_array)[2048], float (&dst_array)[2048])
{
    for(int i = 0; i < face_identifier_->feature_size(); ++i)
    {
        dst_array[i] += src_array[i];
    }
}

void MainWindow::avg_array(float (&src_array)[2048], float (&dst_array)[2048], float avg_num)
{
    for(int i = 0; i < face_identifier_->feature_size(); ++i)
    {
        dst_array[i] = src_array[i] / avg_num;
    }
}

int MainWindow::verify(seeta::ImageData img_color_data, std::vector<seeta::FacialLandmark>& llpoints, QString &verify_target, float thresh)
{
    float dst_features[2048] = {0.0};
    // 从文件读feature
    if(!read_target_features(verify_target, dst_features))  return -1;
    // 遍历faces，找到置信度超过阈值的脸，返回脸的index
    const int point_num = llpoints.size();
    seeta::FacialLandmark pt5[5];
    float src_features[2048] = {0.0};
    float max_sim = 0.0;
    int max_idx = -1;
    for(int i = 0; i <= point_num; ++i)
    {
        // assign point to pt5
        if((i % 5 != 0 || i == 0) && i != point_num)
        {
            pt5[i % 5] = llpoints[i];
        }
        // when pt5 is full, extract features
        else
        {
            face_identifier_->extract_features_with_crop(img_color_data, pt5, src_features);
            float sim = face_identifier_->calc_sim(src_features, dst_features);
            qDebug() << "sim: " << sim;
            if(max_sim < sim && sim >= thresh)   {   max_sim = sim; max_idx = i / 5 - 1;   }
        }
    }
    return max_idx;
}

bool MainWindow::read_target_features(QString& verify_target, float (&dst_array)[2048])
{
    QFile verify_target_file(feature_root_ + verify_target + QString(".features"));
    // check if exist
    if(!verify_target_file.exists())    return false;
    // read file
    if(!verify_target_file.open(QFile::ReadOnly))   return false;
    QTextStream in(&verify_target_file);
    QString line = in.readLine();
    QStringList str_list = line.split(' ', QString::SkipEmptyParts);
    // assign value to dst_array
    for(int i = 0; i < str_list.size(); ++i)
    {
        QString str = str_list.at(i);
        dst_array[i] = str.toFloat();
    }
    return true;
}

/* Slots */
void MainWindow::on_action_open_video_triggered()   // 打开视频
{
    // pause
    if(is_playing_)
        on_video_play_pause_clicked();
    // pop up dialog
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
            ui->video_slider->setEnabled(true);
            ui->video_slider->setMaximum(std::pow(10, k-1));
            if(!is_playing_)
                on_video_play_pause_clicked();
        }
        else
        {
            QMessageBox::warning(this, "Error", QString("Cannot open ") + file_path, QMessageBox::Yes);
        }
    }
}

void MainWindow::on_action_open_camera_triggered()  // 打开摄像头
{
    // pause
    if(is_playing_)
        on_video_play_pause_clicked();

    cap_.open(0);
    if(cap_.isOpened())
    {
        // init video_label
        get_frame();
        fps_ = 1000;
    }
    ui->video_slider->setEnabled(false);
    ui->video_backward->setEnabled(false);
    ui->video_forward->setEnabled(false);

    if(!is_playing_)
        on_video_play_pause_clicked();
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
    if(!cap_.is_opened_camera())
    {
        ui->video_backward->setEnabled(!is_playing_);
        ui->video_forward->setEnabled(!is_playing_);
    }
    //ui->video_slider->setEnabled(!is_playing_);

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

void MainWindow::on_detection_switch_checkbox_clicked(bool checked)     // 检测开启
{
    ui->detection_show_checkbox->setEnabled(checked);
    ui->Align->setEnabled(checked);
    ui->align_switch_checkbox->setEnabled(checked);
    ui->align_browse_btn->setEnabled(checked);

    if(checked)     // start to detect
    {
        // register Face_Detector
        QString model_path = ui->detection_model_lineedit->text();
        if(!QFile::exists(model_path))
        {
            QMessageBox::warning(this, "Error", QString("Detection model file ") + model_path + QString(" not exist!"), QMessageBox::Yes);
            ui->detection_switch_checkbox->setChecked(false);
            on_detection_switch_checkbox_clicked(false);
            return;
        }
        if(!model_path.endsWith(".bin"))
        {
            QMessageBox::warning(this, "Error", QString("Model path NOT right!"), QMessageBox::Yes);
            ui->detection_switch_checkbox->setChecked(false);
            on_detection_switch_checkbox_clicked(false);
            return;
        }

        LOG(INFO) << "Load detection model from " << model_path.toStdString();
        face_detector_ = std::make_shared<ev::Face_Detector>(model_path.toStdString());
        // some settings
        face_detector_->set_score_thresh(10.0f);
        face_detector_->set_min_face_size(100);
        // set flag
        is_detection_model_loaded_ = true;
    }
    else
    {
        is_detection_model_loaded_ = false;
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QSize new_size = event->size();

}

void MainWindow::on_detection_browse_btn_clicked()
{
    // pop up dialog
    QFileDialog* file_dialog = new QFileDialog(this);
    file_dialog->setWindowTitle(tr("Browse detection model"));
    file_dialog->setDirectory(".");
    if(file_dialog->exec() == QDialog::Accepted)
    {
        QString file_path = file_dialog->selectedFiles()[0];
        ui->detection_model_lineedit->setText(file_path);
    }
}

void MainWindow::on_detection_show_checkbox_clicked(bool checked)
{
    is_draw_detection_result_ = checked;
}

void MainWindow::on_align_switch_checkbox_clicked(bool checked)     // 对齐开始
{
    ui->align_show_checkbox->setEnabled(checked);
    ui->Identify->setEnabled(checked);

    if(checked)
    {
        // register Face_Aligner
        QString model_path = ui->align_model_lineedit->text();
        if(!QFile::exists(model_path))
        {
            QMessageBox::warning(this, "Error", QString("Alignment model file ") + model_path + QString(" not exist!"), QMessageBox::Yes);
            ui->align_switch_checkbox->setChecked(false);
            on_align_switch_checkbox_clicked(false);
            return;
        }
        if(!model_path.endsWith(".bin"))
        {
            QMessageBox::warning(this, "Error", QString("Model path NOT right!"), QMessageBox::Yes);
            ui->align_switch_checkbox->setChecked(false);
            on_align_switch_checkbox_clicked(false);
            return;
        }

        LOG(INFO) << "Load alignment model from " << model_path.toStdString();
        face_aligner_ = std::make_shared<ev::Face_Aligner>(model_path.toStdString());

        // set flag
        is_aligner_model_loaded_ = true;

        // disable toolkit_tabwidget
        if(!is_identifier_model_loaded_)
            ui->toolkit_tagwidget->setEnabled(false);
    }
    else
    {
        is_aligner_model_loaded_ = false;
    }
}

void MainWindow::on_align_show_checkbox_clicked(bool checked)
{
    is_draw_align_result_ = checked;
}

void MainWindow::on_id_switch_checkbox_clicked(bool checked)    // 识别模块工作
{
    if(checked)
    {
        // register Face_Identifier
        QString model_path = ui->id_model_lineedit->text();
        if(!QFile::exists(model_path))
        {
            QMessageBox::warning(this, "Error", QString("Identification model file ") + model_path + QString(" not exist!"), QMessageBox::Yes);
            ui->id_switch_checkbox->setChecked(false);
            on_id_switch_checkbox_clicked(false);
            return;
        }
        if(!model_path.endsWith(".bin"))
        {
            QMessageBox::warning(this, "Error", QString("Model path NOT right!"), QMessageBox::Yes);
            ui->id_switch_checkbox->setChecked(false);
            on_id_switch_checkbox_clicked(false);
            return;
        }

        LOG(INFO) << "Load identification model from " << model_path.toStdString();
        face_identifier_ = std::make_shared<ev::Face_Identifier>(model_path.toStdString());

        // set flag
        is_identifier_model_loaded_ = true;
    }
    else
    {
        is_identifier_model_loaded_ = false;
    }

    ui->toolkit_tagwidget->setEnabled(is_identifier_model_loaded_);
}

void MainWindow::on_id_browse_btn_clicked()
{
    // pop up dialog
    QFileDialog* file_dialog = new QFileDialog(this);
    file_dialog->setWindowTitle(tr("Browse detection model"));
    file_dialog->setDirectory(".");
    if(file_dialog->exec() == QDialog::Accepted)
    {
        QString file_path = file_dialog->selectedFiles()[0];
        ui->id_model_lineedit->setText(file_path);
    }
}

void MainWindow::on_gen_btn_clicked()
{
    // check if dir features/ exist, if not create it.
    QDir target_root_dir(feature_root_);
    if(!target_root_dir.exists())    target_root_dir.mkdir(target_root_dir.absolutePath());
    if(ui->target_name_lineedit->text() != QString(""))
    {
        // TODO
        QFile target_feature(target_root_dir.absolutePath() + QString("/") + ui->target_name_lineedit->text() + QString(".features"));
        if(target_feature.exists())     target_feature.remove();

        // 遍历images目录
        QDir image_dir(QString(image_root_) + ui->target_name_lineedit->text());
        image_dir.setFilter(QDir::Files | QDir::NoSymLinks);
        const QFileInfoList list = image_dir.entryInfoList();
        // QFileInfoList::const_iterator iterator = list.begin();
        const int feature_size = face_identifier_->feature_size();
        float features[2048] = {0.0};
        float sum_features[2048] = {0.0};
        float avg_features[2048] = {0.0};
        qDebug() << "Feature size: " << feature_size;
        int num_files = list.size();
        if(num_files <= 0)
        {
            QMessageBox::critical(this, "Error", "Got no images under " + image_dir.absolutePath());
        }
        QProgressDialog progress(QString("Extracting features from %1...").arg(target_root_dir.absolutePath()), "Abort Extract", 0, num_files, this);
        // setting
        progress.setWindowModality(Qt::WindowModal);
        progress.setMinimumDuration(0);
        progress.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        progress.setWindowTitle("Extract features");
        for(int i = 0; i < num_files; ++i)
        {
            //qDebug() << (*iterator).fileName();
            // TODO: extract features of every image and average them

            // set progress bar
            progress.setValue(i);
            // exit if canceled
            if(progress.wasCanceled())      break;

            QString img_path = image_dir.absolutePath() + QString("/") + list[i].fileName();
            qDebug() << "Extract features from " << img_path;
            QImage src_img(img_path);
            cv::Mat src_mat = image_to_mat(src_img);
            ImageData src_img_data(src_img.width(), src_img.height(), 3);
            src_img_data.data = src_mat.data;

            face_identifier_->extract_features(src_img_data, features);

            add_array(features, sum_features);
        }
        progress.setValue(num_files);
        avg_array(sum_features, avg_features, (float)num_files);
        // 写feature到文件
        if (!target_feature.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::critical(this, "提示", "无法创建文件");
            return;
        }
        QTextStream out(&target_feature);
        for(int i = 0; i < face_identifier_->feature_size(); ++i)
        {
            out << avg_features[i] << " ";
        }
        target_feature.close();
        // 添加目标到verify
        if(ui->verify_target_combo->findText(ui->target_name_lineedit->text()) == -1)   // 没找着
        {
            ui->verify_target_combo->addItem(ui->target_name_lineedit->text());
        }
    }
}

void MainWindow::on_snapshot_btn_clicked()      // 截图
{
    // check if dir images/ exist, if not create it.
    QDir target_root_dir(image_root_);
    if(!target_root_dir.exists())      target_root_dir.mkdir(target_root_dir.absolutePath());

    // crop face
    cv::Mat dst_img(face_identifier_->crop_height(), face_identifier_->crop_width(), CV_8UC(face_identifier_->crop_channels()));

    ImageData dst_img_data(dst_img.cols, dst_img.rows, dst_img.channels());
    dst_img_data.data = dst_img.data;

    cv::Mat src_img = cap_.origin_frame_;
    ImageData src_img_data(src_img.cols, src_img.rows, src_img.channels());
    src_img_data.data = src_img.data;

    face_identifier_->crop_face(src_img_data, pt5_, dst_img_data);
    QPixmap dst_pixmap = mat_to_pixmap(dst_img);

    // show snapshot
    ui->snapshot_label->setPixmap(dst_pixmap);

    // save
    if(ui->target_name_lineedit->text() != QString(""))
    {
        // TODO
        QDir target_dir(target_root_dir.absolutePath() + QString("/") + ui->target_name_lineedit->text());
        if(!target_dir.exists())      target_dir.mkdir(target_dir.absolutePath());
        int file_num = target_dir.count() - 2;
        QString img_name = QString("%1.jpg").arg(file_num + 1);
        QString img_path = target_dir.absolutePath() + QString("/") + img_name;
        dst_pixmap.save(img_path);
    }
}

void MainWindow::on_verify_btn_clicked(bool checked)
{
    is_verify_start_ = checked;
}
