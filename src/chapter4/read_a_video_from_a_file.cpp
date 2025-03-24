#include "read_a_video_from_a_file.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

namespace chapter4 {

    int ReadAVideoFromAFile() {
        Mat frame;
        // 비디오를 읽으려먼 `VideoCapture`를 반드시 써야한다.
        VideoCapture cap("./data/move_file.avi");

        // check if file exists. if none program ends
        if(cap.isOpened() == 0) {
            cout << "no such file!" << endl;
            waitKey(0);
            return 0 ;
        }

        while(1) {
            cap >> frame;
            if(frame.empty()) {
                cout << "end of video" << endl;
                break;
            }
            imshow("video", frame);

            // `waitKey(33) //ms` 이 함수가 없다면
            // 우리가 눈치채기도 전에 쭉~ 아주 빠르게 프레임을 재생하고 꺼질 것 이다.
            // 그래서 33ms를 기다리도록 할 수 있다.
            waitKey(33);
        }
        return 0;
    }

}
