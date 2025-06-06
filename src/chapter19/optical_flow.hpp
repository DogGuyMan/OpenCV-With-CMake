#ifndef __OPTICAL_FLOW__
#define __OPTICAL_FLOW__

#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

namespace chapter19 {
    struct feature {
        cv::Point2f pt;
        int val;
    };

    void DrawTrackingPoints(std::vector<cv::Point2f> &points, cv::Mat &img);
    int OpticalFlow();
}

#endif//__OPTICAL_FLOW__
