#ifndef __COLOR_BALANCING__
#define __COLOR_BALANCING__

#pragma once

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

namespace chapter11 {
    int CalculateChannelAverage(std::vector<Mat> &, cv::Vec3i &);
    int GrayWorldAssumsptionBalancing(vector<Mat> &,  const::Vec3i &);
    int ColorBalancing();
}

#endif//__COLOR_BALANCING__
