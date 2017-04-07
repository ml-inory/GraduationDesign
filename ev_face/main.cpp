/*************************************************************************
	> File Name: main.cpp
	> Author: inory
	> Mail: madscientist_yang@foxmail.com
	> Created Time: Sun 02 Apr 2017 10:48:38 PM PDT
 ************************************************************************/

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <glog/logging.h>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "seetaface.h"

using namespace std;
using namespace cv;

bool init_glog()
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

int main(int argc, char** argv)
{
    init_glog();

	if(argc < 2)
	{
		cout << "Usage: " << argv[0]
			 << "video_path" << endl;
	}

    const string prefix = "../data/video/";
	const string video_path = prefix + argv[1];

    cv::VideoCapture cap;
    int camera_id = -1;
    string str_video_src;
	if(video_path.size() == 1)
    {
        camera_id = atoi(video_path.c_str());
		cap.open(camera_id); // open camera
        char str_camera_id[1];
        sprintf(str_camera_id, "%d", camera_id);
        str_video_src = string("camera_id: ") + str_camera_id;
        LOG_IF(INFO, cap.isOpened()) << "Open camera. camera_id = " << camera_id;
    }
	else
    {
		cap.open(video_path); // open video
        str_video_src = string("video_path: ") + video_path;
        LOG_IF(INFO, cap.isOpened()) << "Open video. video_path = " << video_path;
    }

	if(!cap.isOpened())
	{
		LOG(ERROR) << "Cannot open " << str_video_src;
        return -1;
	}
	
	Mat img, img_gray;
    int try_times = 5;
    int error_count = 0;
	while(!cap.read(img))
    {
        error_count ++;
        LOG(WARNING) << "read frame failed, retry " << error_count << "/" << try_times;
        LOG_IF(ERROR, error_count >= try_times) << "Cannot read any frame from" << str_video_src;
        return -1;
    }

	// Load model
    ev::Face_Detector detector("../data/model/seeta_fd_frontal_v1.0/bin");

    bool need_resize = (img.cols > 1024) || (img.rows > 1024);
    if(need_resize)
    {
        LOG(INFO) << "image too big, need resize";
        cv::resize(img, img, cv::Size(0,0), 0.5, 0.5);
    }
    LOG(INFO) << "image size: width = " << img.cols << " height = " << img.rows;
	seeta::ImageData img_data;
	img_data.width = img.cols;
	img_data.height = img.rows;
	img_data.num_channels = 1;

	// read frame
    cv::namedWindow("Video");
	while(true)
	{
		if(!cap.read(img)) continue;
	    if(need_resize)     cv::resize(img, img, cv::Size(0,0), 0.5, 0.5);
		if(img.channels() != 1)
			cvtColor(img, img_gray, COLOR_BGR2GRAY);
		else
			img_gray = img;

		// detect
		img_data.data = img_gray.data;
        
		std::vector<seeta::FaceInfo> faces = detector.detect(img_data);

		cv::Rect face_rect;
		int32_t num_face = static_cast<int32_t>(faces.size());

		for (int32_t i = 0; i < num_face; i++) 
		{
			face_rect.x = faces[i].bbox.x;
			face_rect.y = faces[i].bbox.y;
			face_rect.width = faces[i].bbox.width;
			face_rect.height = faces[i].bbox.height;

            cv::rectangle(img, face_rect, CV_RGB(0, 0, 255), 4, 8, 0);
		}
        
        cv::imshow("Video", img);

		char key = cv::waitKey(40);
		if(key == 'q')
			break;
	}
}
