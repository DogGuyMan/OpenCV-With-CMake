#ifndef _PERSPECTIVE_TRANSFORMATION_
#define _PERSPECTIVE_TRANSFORMATION_

#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>

namespace chapter20 {
    static const std::string INPUT_WINDOW = "input";
    static const std::string OUTPUT_WINDOW = "output";

    int PerspectiveTransformation();
    struct MouseParams {
        cv::Mat img;
        std::vector<cv::Point2f> input, output;
    };
}

#endif//_PERSPECTIVE_TRANSFORMATION_
