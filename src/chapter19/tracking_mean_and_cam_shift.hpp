#ifndef __TRACKING_MEAN_AND_CAM_SHIFT_HPP__
#define __TRACKING_MEAN_AND_CAM_SHIFT_HPP__
#define MEAN_SHIFT_TRACKING 1
#define CAM_SHIFT_TRACKING 0

#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>

namespace chapter19 {
    // 컴파일 타임 상수
        // constexpr로 선언된 변수나 함수는 컴파일 타임에 평가될 수 있습니다.
        // 이는 런타임 대신 컴파일 시점에 값이 결정된다는 의미입니다.
        // 컴파일 시간에 평가될 수 있는 코드
        // const 변수는 런타임에 초기화될 수 있지만, constexpr 변수는 컴파일 타임에 초기화되어야 합니다
    constexpr std::string_view TRACKER_WINDOW = "Tracker Image";
    constexpr std::string_view INPUT_WINDOW = "Input Image";
    constexpr std::string_view OUTPUT_WINDOW = "Output Image";

    int Tracking();
    int MeanShift();
    int CamShift();

    struct CallbackData {
        cv::Mat frame;
        cv::Point pt[2];
        cv::Rect roi;
        bool isDragging;
        bool isUpdated;
    };
}

#endif//__TRACKING_MEAN_AND_CAM_SHIFT_HPP__
