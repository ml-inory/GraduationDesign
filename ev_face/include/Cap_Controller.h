/*************************************************************************
	> File Name: ../include/Cap_Controller.h
	> Author: inory
	> Mail: madscientist_yang@foxmail.com
	> Created Time: Fri 07 Apr 2017 10:43:26 AM PDT
 ************************************************************************/

#ifndef CAP_CONTROLLER_H
#define CAP_CONTROLLER_H

#include <glog/logging.h>

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
			Cap_Controller();

		private:
			cv::VideoCapture cap_;
	}
}
#endif

