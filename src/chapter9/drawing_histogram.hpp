#ifndef __HISTOGRAM_EQUALIZATION__
#define __HISTOGRAM_EQUALIZATION__
#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
using namespace cv;

namespace chapter9 {
    Mat DrawHistogram(Mat image);
    int HistogramEqualization();
    int HistogramNormalization();
}

#endif//__HISTOGRAM_EQUALIZATION__
