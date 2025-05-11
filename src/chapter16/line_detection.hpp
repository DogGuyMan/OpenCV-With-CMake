#ifndef __LINE_DETECTION__
#define __LINE_DETECTION__

#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

namespace chapter16 {
    int HoughLineDetection();
}

namespace chapter16 {
    const std::string HOUGH_LINE_P_IMAGE = "Hough Line P Detection Input Image";
    const std::string HOUGH_LINE_P_EDGE = "Hough Line P Detection edge";
    const std::string HOUGH_LINE_P_RESULT = "Hough Line P Detection result";
    const std::string HOUGH_LINE_P_MIN_LINE_LENGTH = "Min Line Length";
    const std::string HOUGH_LINE_P_MAX_LINE_GAP = "Max Line Gap";
    const std::string HOUGH_LINE_P_LINE_THRESHOLD = "Line Threshold";

    int HoughLinesPDetection();
}

#endif//__LINE_DETECTION__
