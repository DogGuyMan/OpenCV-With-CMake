#ifndef __BACKGROUND_SUBTRACTION__
#define __BACKGROUND_SUBTRACTION__

#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

namespace chapter13 {
    int MeanFilterSubtraction();
    int MedianFilterSubtraction();
    int AbsDiffSubtraction();
    int MoG2ModelSubtraction();
}

#endif//__BACKGROUND_SUBTRACTION__
