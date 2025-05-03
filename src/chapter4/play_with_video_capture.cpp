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

            cout << "frames: " << curr_frame << "/" << total_frames << endl;
            imshow("video", frame);

            waitKey(1000 / fps);
        }

        waitKey(0);
        return 0;
    }

}
