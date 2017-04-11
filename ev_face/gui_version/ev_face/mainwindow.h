#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

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

    void on_action_open_video_triggered();

    void on_action_open_camera_triggered();

private:
    void init_glog();
    void init_cap();

    Ui::MainWindow *ui;
    ev::Cap_Controller cap_;
};

#endif // MAINWINDOW_H
