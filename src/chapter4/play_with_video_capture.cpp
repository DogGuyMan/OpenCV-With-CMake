#include "play_with_video_capture.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

namespace chapter4 {

    int PlayWithVideoCapture() {
        Mat frame;
        VideoCapture cap;

        if(cap.open("./date/Megamind.avi") == false) return -1;
        double fps = cap.get(CAP_PROP_FPS);
        double time_in_msec = 0;
        int curr_frame = 0;
        int total_frames = cap.get(CAP_PROP_FRAME_COUNT);

        while(time_in_msec < 3000) {
            cap >> frame;
            if(frame.empty()) break;
            time_in_msec = cap.get(CAP_PROP_POS_MSEC);
            curr_frame = cap.get(CAP_PROP_POS_FRAMES);
            // 현재 프레임을 하나하나 씩 출력하며 전체 프레임 을 리턴한다
            cout << "frames: " << curr_frame << "/" << total_frames << endl;
            imshow("video", frame);

            // 현재 fps를 통해 딜레이를 계산하고, WaitKey()에 fps에 해당하는 대기 시간을 넣어 준다.
            waitKey(1000 / fps);
        }

        waitKey(0);
        return 0;
    }

}
