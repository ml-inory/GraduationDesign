/*************************************************************************
	> File Name: Cap_Controller.cpp
	> Author: inory
	> Mail: madscientist_yang@foxmail.com
	> Created Time: Sat 08 Apr 2017 10:09:26 AM PDT
 ************************************************************************/

#include "Cap_Controller.hpp"

#include <glog/logging.h>

/* OpenCV part */
ev::Cap_Controller::Cap_Controller()
{
}

ev::Cap_Controller::Cap_Controller(const string& video_path):
video_path_(video_path),
camera_id_(-1),
is_opened_camera_(false)
{
    cap_.open(video_path);
}

ev::Cap_Controller::Cap_Controller(const char* video_path):
video_path_(video_path),
camera_id_(-1),
is_opened_camera_(false)
{
    cap_.open(video_path);
}

ev::Cap_Controller::Cap_Controller(const int camera_id):
video_path_(""),
camera_id_(camera_id),
is_opened_camera_(true)
{
    cap_.open(camera_id_);
}

ev::Cap_Controller::~Cap_Controller()
{
    cap_.release();
}

bool ev::Cap_Controller::open(const string& video_path)
{
    video_path_ = video_path;
    camera_id_ = -1;
    is_opened_camera_ = false;
    bool ret = cap_.open(video_path);
    if(ret)
    {
        total_frames_ = cap_.get(cv::CAP_PROP_FRAME_COUNT);     
    }
    return ret;
}

bool ev::Cap_Controller::open(const char* video_path)
{
    video_path_ = string(video_path);
    camera_id_ = -1;
    is_opened_camera_ = false;
    bool ret = cap_.open(video_path);
    if(ret)
    {
        total_frames_ = cap_.get(cv::CAP_PROP_FRAME_COUNT);     
    }
    return ret;
}

bool ev::Cap_Controller::open(const int camera_id)
{
    video_path_ = "";
    camera_id_ = camera_id;
    is_opened_camera_ = true;
    total_frames_ = -1;
    return cap_.open(camera_id);
}

bool ev::Cap_Controller::read(cv::Mat& img, bool flip_channel)
{
    bool ret = cap_.read(origin_frame_);
    if(flip_channel)    cv::cvtColor(origin_frame_, origin_frame_, COLOR_BGR2RGB);
    pos_frame_ = cap_.get(cv::CAP_PROP_POS_FRAMES);
    //LOG(INFO) << "Read frame " << pos_frame_;
    if(!force_not_resize_ && !force_resize_)
        check_if_need_resize();
    resized_frame_ = auto_resize(origin_frame_);
    resized_frame_.copyTo(img);
    return ret;
}

bool ev::Cap_Controller::isOpened()
{
    return cap_.isOpened();
}

bool ev::Cap_Controller::set(int prop_id, double value)
{
    return cap_.set(prop_id, value);
}

double ev::Cap_Controller::get(int prop_id)
{
    return cap_.get(prop_id);
}


/* New Part */

// flags
bool ev::Cap_Controller::is_opened_camera()
{
    return is_opened_camera_;
}


// getter
std::string ev::Cap_Controller::get_video_path()
{
    return video_path_;
}

int ev::Cap_Controller::get_camera_id()
{
    return camera_id_;
}

int ev::Cap_Controller::get_frame_width()
{
    return resized_frame_.cols;
}

int ev::Cap_Controller::get_frame_height()
{
    return resized_frame_.rows;
}

int ev::Cap_Controller::get_pos_frame()
{
    if(cap_.isOpened())
    {
        cv::Mat tmp;
        if(read(tmp))
        {
            set(cv::CAP_PROP_POS_FRAMES, pos_frame_ - 1);
            return pos_frame_;
        }
        else
            return -2;
    }
    else
        return -1;
}

int ev::Cap_Controller::get_total_frames()
{
    return total_frames_;
}

// setter
void ev::Cap_Controller::set_resize_thresh(int size_thresh)
{
    size_thresh_ = cv::Size(size_thresh, size_thresh);
}

void ev::Cap_Controller::set_resize_thresh(int width_thresh, int height_thresh)
{
    size_thresh_ = cv::Size(width_thresh, height_thresh);
}

void ev::Cap_Controller::set_resize_size(int width, int height)
{
    is_resize_by_factor_ = false;
    resize_size_ = cv::Size(width, height);
    resize_factor_ = cv::Point2f(0,0);
}

void ev::Cap_Controller::set_resize_factor(double x, double y)
{
    is_resize_by_factor_ = true;
    resize_size_ = cv::Size(0,0);
    resize_factor_ = cv::Point2f(x, y);
}

void ev::Cap_Controller::set_force_not_resize(bool flag)
{
    force_not_resize_ = flag;
    force_resize_ = !flag;
}

void ev::Cap_Controller::set_force_resize(bool flag)
{
    force_not_resize_ = !flag;
    force_resize_ = flag;
}

// private
void ev::Cap_Controller::check_if_need_resize()
{
    if(origin_frame_.cols > size_thresh_.width || origin_frame_.rows > size_thresh_.height)
        need_resize_ = true;
    else
        need_resize_ = false;
}

cv::Mat ev::Cap_Controller::auto_resize(cv::Mat& img)
{
    cv::Mat ret_img;
    if(force_not_resize_)   return img;     // 强行不缩放
    
    if(force_resize_)   // 强行缩放
    {
        if(is_resize_by_factor_)    // 按比例缩放
        {
            cv::resize(img, ret_img, cv::Size(0,0), resize_factor_.x, resize_factor_.y);
        }
        else    // 按具体大小缩放
        {
            cv::resize(img, ret_img, resize_size_);
        }
        LOG_IF(ERROR, ret_img.empty()) << "resize_factor or resize_size not set";
        return ret_img;
    }

    if(need_resize_)    //按需缩放
    {
        if(is_resize_by_factor_)    // 按比例缩放
        {
            cv::resize(img, ret_img, cv::Size(0,0), resize_factor_.x, resize_factor_.y);
        }
        else    // 按具体大小缩放
        {
            cv::resize(img, ret_img, resize_size_);
        }
        return ret_img;
    }
    else
    {
        return img;
    }
}
