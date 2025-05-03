#include "background_subtraction.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int chapter13::MeanFilterSubtraction() {
    Mat frame;
    VideoCapture capture;
    if(capture.open("./data/vtest.avi") == false) return -1;
    double fps = capture.get(CAP_PROP_FPS);
    double time_in_msec = 0;
    int curr_frame = 0;
    int total_frames = capture.get(CAP_PROP_FRAME_COUNT);


    while(true) {
        capture >> frame;
        if(frame.empty()) break;

        time_in_msec = capture.get(CAP_PROP_POS_MSEC);
        curr_frame = capture.get(CAP_PROP_POS_FRAMES);
        // 현재 프레임을 하나하나 씩 출력하며 전체 프레임 을 리턴한다

        imshow("video", frame);

        waitKey(1000 / fps);
    }
    return 1;
}
