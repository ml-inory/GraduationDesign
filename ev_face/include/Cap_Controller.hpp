/*************************************************************************
	> File Name: Cap_Controller.h
	> Author: inory
	> Mail: madscientist_yang@foxmail.com
	> Created Time: Fri 07 Apr 2017 10:43:26 AM PDT
 ************************************************************************/

#ifndef Cap_Controller_hpp
#define Cap_Controller_hpp

#include <string>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

namespace ev
{
	class Cap_Controller
	{
		public:
            /* OpenCV VideoCapture part */
            Cap_Controller();
			Cap_Controller(const string& video_path);
            Cap_Controller(const char* video_path);
            Cap_Controller(const int camera_id);
            ~Cap_Controller();

            bool open(const string& video_path);
            bool open(const char* video_path);
            bool open(const int camera_id);

            bool read(cv::Mat& img);
            bool isOpened();
            bool set(int prop_id, double value);
            double get(int prop_id);
            
            
            /* New part */
            
            // flags
            bool is_opened_camera();

            // getter
            string get_video_path();
            int get_camera_id();
            int get_frame_width();
            int get_frame_height();
            int get_pos_frame();

            // setter
            void set_resize_thresh(int size_thresh);    // 缩放的阈值，宽或高大于此阈值则需要resize
            void set_resize_thresh(int width_thresh, int height_thresh);    // 宽高中的其一大于各自的阈值则缩放
            void set_resize_size(int width, int height);    // 缩放到某个大小
            void set_resize_factor(double x, double y);   // 按比例缩放
            void set_force_not_resize(bool flag);    // 强行不缩放
            void set_force_resize(bool flag);


		private:
            void check_if_need_resize();
            cv::Mat auto_resize(cv::Mat& img);

            string video_path_;
            
            int camera_id_ = -1;
            int pos_frame_ = 0;
            
            bool is_opened_camera_;
            bool need_resize_ = false;
            bool force_not_resize_ = false;
            bool force_resize_ = false;
            bool is_resize_by_factor_;
            
            cv::Size size_thresh_;  // 缩放阈值
            cv::Size resize_size_;  // 缩放具体大小
            cv::Point2f resize_factor_;    // 缩放比例
            cv::Mat origin_frame_;  // 原始图像
            cv::Mat resized_frame_; // 缩放后的图像
			cv::VideoCapture cap_;
	};
}
#endif

