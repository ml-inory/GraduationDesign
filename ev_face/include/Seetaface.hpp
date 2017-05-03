/*************************************************************************
	> File Name: seetaface.h
	> Author: inory
	> Mail: madscientist_yang@foxmail.com
	> Created Time: Sun 07 Apr 2017 10:48:38 PM PDT
 ************************************************************************/

#ifndef Seetaface_hpp
#define Seetaface_hpp

#include <cstdint>
#include <cstdlib>
#include <vector>
#include <memory>
#include <fstream>
#include <glog/logging.h>

#include "common.h"
#include "face_detection.h"
#include "face_alignment.h"
#include "face_identification.h"

using namespace std;
using namespace seeta;

namespace ev
{
    class Face_Detector
    {
        public:
            Face_Detector(const string model_path="", int32_t min_face_size=20/*at least 20*/, int32_t max_face_size=-1/*compute by pyramid_scale_factor*/, float score_thresh=2.f, float pyramid_scale_factor=0.8f, int32_t window_step=4):
                model_path_(model_path),
                min_face_size_(min_face_size),
                score_thresh_(score_thresh),
                pyramid_scale_factor_(pyramid_scale_factor),
                window_step_(window_step),
                detector_(std::make_shared<seeta::FaceDetection>(model_path.c_str()))
            {
                detector_->SetMinFaceSize(min_face_size);
                detector_->SetMaxFaceSize(max_face_size);
                detector_->SetScoreThresh(score_thresh);
                detector_->SetImagePyramidScaleFactor(pyramid_scale_factor);
                detector_->SetWindowStep(window_step, window_step);
            }

            bool load_model(const string& model_path)
            {
                return detector_->LoadModel(model_path.c_str());
            }

            std::vector<seeta::FaceInfo> detect(const seeta::ImageData& img_data)
            {
                return detector_->Detect(img_data);
            }

            void set_min_face_size(int32_t min_face_size)
            {
                detector_->SetMinFaceSize(min_face_size);
            }

            void set_max_face_size(int32_t max_face_size)
            {
                detector_->SetMaxFaceSize(max_face_size);
            }

            void set_score_thresh(float score_thresh)
            {
                detector_->SetScoreThresh(score_thresh);
            }

            void set_image_pyramid_scale_factor(float pyramid_scale_factor)
            {
                detector_->SetImagePyramidScaleFactor(pyramid_scale_factor);
            }

            void set_window_step(int32_t x, int32_t y)
            {
                detector_->SetWindowStep(x, y);
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


    class Face_Aligner
    {
        public:
            Face_Aligner(const string model_path=""):
                model_path_(model_path),
                aligner_(std::make_shared<seeta::FaceAlignment>(model_path.c_str()))
            {
            }

            bool detect_landmarks(ImageData& gray_im, FaceInfo& face_info, FacialLandmark* points)
            {
                return aligner_->PointDetectLandmarks(gray_im, face_info, points);
            }

            bool detect_multi_landmarks(ImageData& gray_im, std::vector<FaceInfo>& face_infos, std::vector<FacialLandmark>& points)
            {
                if(gray_im.num_channels != 1)
                {
                    LOG(ERROR) << "Input image must be grayscale";
                    return false;
                }
                int face_num = face_infos.size();
                const int pts_num = 5;

                FacialLandmark* pt5 = new FacialLandmark[pts_num];
                for(int i = 0; i < face_num; i++)
                {
                    detect_landmarks(gray_im, face_infos[i], pt5);

                    for(int j = 0; j < pts_num; j++)
                    {
                        //points[i * pts_num + j].x = pt5[j].x;
                        //points[i * pts_num + j].y = pt5[j].y;
                        points.push_back(pt5[j]);
                    }


                }
                delete pt5;

                return true;
            }

        private:
            string model_path_;
            std::shared_ptr<seeta::FaceAlignment> aligner_;
    };

    typedef float* FaceFeatures;

    class Face_Identifier
    {
        public:
            Face_Identifier(const string model_path=""):
                model_path_(model_path),
                identifier_(std::make_shared<seeta::FaceIdentification>(model_path.c_str()))
            {
            }

            uint8_t crop_face(const ImageData& src_img, const FacialLandmark* llpoint, const ImageData& dst_img)
            {
                return identifier_->CropFace(src_img, llpoint, dst_img);
            }

            uint8_t extract_features(const ImageData& crop_img, FaceFeatures const feats)
            {
                return identifier_->ExtractFeature(crop_img, feats);
            }

            uint32_t crop_width()   { return identifier_->crop_width(); }
            uint32_t crop_height()  { return identifier_->crop_height(); }
            uint32_t crop_channels(){ return identifier_->crop_channels(); }
            uint32_t feature_size() { return identifier_->feature_size(); }

        private:
            string model_path_;
            std::shared_ptr<seeta::FaceIdentification> identifier_;
    };
}

#endif
