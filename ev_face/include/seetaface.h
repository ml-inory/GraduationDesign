/*************************************************************************
	> File Name: seetaface.h
	> Author: inory
	> Mail: madscientist_yang@foxmail.com
	> Created Time: Sun 07 Apr 2017 10:48:38 PM PDT
 ************************************************************************/

#ifndef SEETAFACE_H
#define SEETAFACE_H

#include <cstdint>
#include <cstdlib>
#include <vector>
#include <memory>
#include <fstream>
#include <glog/logging.h>
#include "fust.h"
#include "detector.h"
#include "face_detection.h"

using namespace std;

namespace ev
{
    class Face_Detector
    {
        public:
            Face_Detector(const string model_path="../data/model/seeta_fd_frontal_v1.0.bin", int32_t min_face_size=20, float score_thresh=2.f, float pyramid_scale_factor=0.8f, int32_t window_step=4):
                model_path_(model_path),
                min_face_size_(min_face_size),
                score_thresh_(score_thresh),
                pyramid_scale_factor_(pyramid_scale_factor),
                window_step_(window_step),
                detector_(new seeta::FaceDetection(model_path.c_str()))
            {
                //detector_->LoadModel(model_path);
                detector_->SetMinFaceSize(min_face_size);
                //detector_->SetMaxFaceSize(max_face_size);
                detector_->SetScoreThresh(score_thresh);
                detector_->SetImagePyramidScaleFactor(pyramid_scale_factor);
                detector_->SetWindowStep(window_step, window_step);
            }

            std::vector<seeta::FaceInfo> detect(const seeta::ImageData& img_data)
            {
                return detector_->Detect(img_data);
            }

            void set_min_face_size(int32_t min_face_size)
            {
                detector_->SetMinFaceSize(min_face_size);
            }

        private:
            string model_path_;
            int32_t min_face_size_;
            int32_t max_face_size_;
            float score_thresh_;
            float pyramid_scale_factor_;
            int32_t window_step_;
            std::shared_ptr<seeta::FaceDetection> detector_;
    };
}

#endif
