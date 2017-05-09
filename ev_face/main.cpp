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

#include "Cap_Controller.hpp"
#include "Seetaface.hpp"

using namespace std;
using namespace cv;

enum class Message
{
    OK = 0,
    ERROR_CAP_OPEN = 1
};

void init_glog()
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
			 << "video_path/camera_id" << endl;
        return -1;
	}

    ev::Cap_Controller cap;
    cap.set_force_resize(true);
    cap.set_resize_thresh(1024);
    cap.set_resize_factor(0.5, 0.5);
    // Open video
    if(strlen(argv[1]) == 1)
        cap.open(atoi(argv[1]));
    else
        cap.open(argv[1]);

    if(!cap.isOpened())
    {
        LOG_IF(ERROR, cap.is_opened_camera()) << "Cannot open camera, camera_id = " << cap.get_camera_id();
        LOG_IF(ERROR, !cap.is_opened_camera()) << "Cannot open video, video_path = " << cap.get_video_path();
        return (int)Message::ERROR_CAP_OPEN;
    }

    LOG_IF(INFO, cap.is_opened_camera()) << "Opened camera. camera_id = " << cap.get_camera_id();
    LOG_IF(INFO, !cap.is_opened_camera()) << "Opened video. video_path = " << cap.get_video_path(); 
	
	// Load model
    const string detection_model_path = "../data/model/seeta_fd_frontal_v1.0.bin";
    const string alignment_model_path = "../data/model/seeta_fa_v1.1.bin";
    ev::Face_Detector detector(detection_model_path);
    ev::Face_Aligner aligner(alignment_model_path);

    cv::Mat tmp;
    while(!cap.read(tmp));
    seeta::ImageData img_data;
    img_data.width = tmp.cols;
    img_data.height = tmp.rows;
    img_data.num_channels = 1;

    // read frame
    cv::Mat img, img_gray;
    cv::namedWindow("Video");
	while(true)
	{
		if(!cap.read(img))
        {
            LOG(WARNING) << "Got no image";
            continue;
        }
        //LOG(INFO) << "Read " << cap.get_pos_frame() << " frame";
	    //if(need_resize)     cv::resize(img, img, cv::Size(0,0), 0.5, 0.5);
		if(img.channels() != 1)
			cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
		else
			img_gray = img;

		// detect
		img_data.data = img_gray.data;

		std::vector<seeta::FaceInfo> faces = detector.detect(img_data);
		int32_t num_face = static_cast<int32_t>(faces.size());

		cv::Rect face_rect;

		for (int i = 0; i < num_face; i++) 
		{
			face_rect.x = faces[i].bbox.x;
			face_rect.y = faces[i].bbox.y;
			face_rect.width = faces[i].bbox.width;
			face_rect.height = faces[i].bbox.height;
            LOG(INFO) << "score: " << faces[i].score;
            cv::rectangle(img, face_rect, CV_RGB(0, 0, 255), 2, 1, 0);
		}
        
        // align
        if(num_face > 0)
        {
            std::vector<seeta::FacialLandmark> points;
            bool align_ret = aligner.detect_multi_landmarks(img_data, faces, points);
        
            if(align_ret)
            {
                for(int i = 0; i < 5*num_face; i++)
                {
                    cv::circle(img, cv::Point(points[i].x, points[i].y), 2, CV_RGB(0,255,0), CV_FILLED);
                }
            }
        }
        
        cv::imshow("Video", img);

		char key = cv::waitKey(1);
		if(key == 'q')
			break;
	}
    return (int)Message::OK;
}
