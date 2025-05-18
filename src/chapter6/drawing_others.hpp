#ifndef __DRAWING_OTHERS__
#define __DRAWING_OTHERS__

#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

namespace chapter6 {
    void onMouse(int event, int x, int y, int flags, void* userdata);
    void WaitForMouseInput(const string& windowName);
    void onTrackbar(int intencity, void* userdata);

    int DrawingArrow();
    int DrawingMarker();
    int DrawingTrackbar();
}

#endif//__DRAWING_OTHERS__
