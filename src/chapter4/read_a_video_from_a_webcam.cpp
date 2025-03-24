#include "read_a_video_from_a_webcam.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

namespace chapter4
{
    int ReadAVideoFromAWebcam()
    {
        VideoCapture cap(0);

        cap.set(CAP_PROP_FRAME_WIDTH, 800);
        cap.set(CAP_PROP_FRAME_HEIGHT, 600);

        if (!cap.isOpened()) {	// isOpened() : 카메라 정보가 있는지 없는지 (1: 있다, 0: 없다)
            printf("Can't open the camera");
            return -1;
        }

        Mat img;

        while (true) {
            cap >> img;

            imshow("camera img", img);

            if (waitKey(1) == 27) break;
        }

        return 0;
    }
} // namespace chapter4
