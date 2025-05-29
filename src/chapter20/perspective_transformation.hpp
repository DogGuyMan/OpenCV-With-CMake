#ifndef _PERSPECTIVE_TRANSFORMATION_
#define _PERSPECTIVE_TRANSFORMATION_

#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

namespace chapter20 {
    int PerspectiveTransformation();
    struct MouseParams {
        Mat img;
        vector<Point2f> input, output;
    };
}

#endif//_PERSPECTIVE_TRANSFORMATION_
