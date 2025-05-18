#ifndef __USAGE_OF_HSL__
#define __USAGE_OF_HSL__
#pragma once
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <algorithm>

namespace chapter11 {
    int UsageOfHSL();
    void onMouse(int event, int x, int y, int flags, void* userData);
    void WaitForMouseInput(const string& windowName, void* isOnceClickedFlags);
}

#endif//__USAGE_OF_HSL__
