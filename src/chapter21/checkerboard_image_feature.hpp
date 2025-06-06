#ifndef __CHECKERBOARD_IMAGE_FEAUTURE__
#define __CHECKERBOARD_IMAGE_FEAUTURE__

#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

namespace chapter21 {
    int CheckerBoardImageFeature();
    struct MouseParams {
        std::string windowName;
        cv::Size size;
        std::vector<cv::Point> input;
        cv::Mat mask;
        bool isMask = false; // 마스크가 설정되었는지 여부
    };
}

#endif//__CHECKERBOARD_IMAGE_FEAUTURE__
