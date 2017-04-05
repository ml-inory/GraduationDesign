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

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "face_detection.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		cout << "Usage: " << argv[0]
			 << "video_path" << endl;
	}

	const string video_path = argv[1];

	VideoCapture cap;
	if(video_path.size() == 1)
		cap.open(atoi(video_path.c_str())); // open camera
	else
		cap.open(video_path); // open video

	if(!cap.isOpened())
	{
		cerr << "Cannot open camera\n";
	}
	
	Mat img, img_gray;
	while(!cap.read(img));

	// Load model
	seeta::FaceDetection detector("../data/model/seeta_fd_frontal_v1.0.bin");
	detector.SetMinFaceSize(20);
	detector.SetScoreThresh(2.f);
	detector.SetImagePyramidScaleFactor(0.8f);
	detector.SetWindowStep(4, 4);

	seeta::ImageData img_data;
	img_data.width = img.cols;
	img_data.height = img.rows;
	img_data.num_channels = 1;

	// read frame
	namedWindow("Video");
	while(true)
	{
		if(!cap.read(img)) continue;
	    if(img.cols > 1024)
			resize(img, img, Size(0,0), 0.5, 0.5);
		if(img.channels() != 1)
			cvtColor(img, img_gray, COLOR_BGR2GRAY);
		else
			img_gray = img;

		// detect
		img_data.data = img_gray.data;
		std::vector<seeta::FaceInfo> faces = detector.Detect(img_data);

		cv::Rect face_rect;
		int32_t num_face = static_cast<int32_t>(faces.size());

		cout << "Got " << num_face << " faces";

		for (int32_t i = 0; i < num_face; i++) 
		{
			face_rect.x = faces[i].bbox.x;
			face_rect.y = faces[i].bbox.y;
			face_rect.width = faces[i].bbox.width;
			face_rect.height = faces[i].bbox.height;

			rectangle(img, face_rect, CV_RGB(0, 0, 255), 4, 8, 0);
		}
		
		imshow("Video", img);

		char key = waitKey(40);
		if(key == 'q')
			break;
	}
}
