#include "tracking_mean_and_cam_shift.hpp"

using namespace std;
using namespace cv;


static void onMouse(int event, int x, int y, int flags, void* userData) {
    chapter19::CallbackData* data = reinterpret_cast<chapter19::CallbackData*>(userData);
    if(event == EVENT_LBUTTONDOWN) {
        data->pt[0].x = x;
        data->pt[0].y = y;
        data->pt[1] = data->pt[0];
        data->isDragging = true;
    }
    if(event == EVENT_LBUTTONUP) {
        int width = abs(x - data->pt[0].x);
        int height = abs(y - data->pt[0].y);
        data->roi.x = data->pt[0].x;
        data->roi.y = data->pt[0].y;
        data->roi.width = width;
        data->roi.height = height;
        data->isDragging = false;

        if(width >= 10 && height >= 10) {
            data->isUpdated = true;
        } else {
            data->isUpdated = false;
        }
    }
    if(data->isDragging && event == EVENT_MOUSEMOVE) {
        if(data->pt[1].x != x && data->pt[1].y != y) {
            Mat img = data->frame.clone();
            data->pt[1].x = x;
            data->pt[1].y = y;
            rectangle(img, data->pt[0], data->pt[1], Scalar(0, 255, 0), 1);
            // 참조하고 있는 문자열의 시작 포인터 (const chat*)을 반환하므로, 여러번 호출하더라도 복사가 되지 않는다.
            imshow(chapter19::TRACKER_WINDOW.data(), img);
        }
    }
}

int chapter19::MeanShift() {
    VideoCapture cap(0);
    chapter19::CallbackData data;
    Mat frame, m_backProj, hsv;
    Mat m_model3d;
    Rect m_rc;

    float hrange[] = {0, 180};
    float vrange[] = {0, 256};
    const float* ranges[] = {hrange, vrange, vrange}; // hue, saturation, bightness
    int channels[] = {0, 1, 2}; // hue, saturation, brightness
    int hist_size[] = {16, 16, 16};

    if(!cap.isOpened()) {
        cerr << "Error: Could not open video capture." << endl;
        return -1;
    }

    cap >> frame;
    imshow(chapter19::TRACKER_WINDOW.data(), frame);

    data.frame = frame; // shellow copy
    data.isDragging = false;
    data.isUpdated = false;
    setMouseCallback(chapter19::TRACKER_WINDOW.data(), onMouse, &data);

    bool tracking = false;

    while(true) {
        if(data.isDragging) {
            if(waitKey(33) == 27) break; // ESC key to exit
            continue;
        }
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        if(data.isUpdated) {
            // HandleRectDirtied
            Rect rc = data.roi;
            Mat mask = Mat::zeros(rc.height, rc.width, CV_8U);
            ellipse(mask, Point(rc.width/2, rc.height/2), Size(rc.width/2, rc.height/2), 0, 0, 360, 255);
            Mat roi(hsv, rc);
            calcHist(&roi, 1, channels, mask, m_model3d, 3, hist_size, ranges);
            m_rc = rc;
            data.isUpdated = false;
            tracking = true;
        }
        cap >> frame;
        if(frame.empty()) break;
        if(tracking) {
            calcBackProject(&hsv, 1, channels, m_model3d, m_backProj, ranges);;
#if     (MEAN_SHIFT_TRACKING == 1)
            meanShift(
                m_backProj,
                m_rc,
                TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1) // The type of termination criteria
            );
#elif   (CAM_SHIFT_TRACKING == 1)
            CamShift(
                m_backProj,
                m_rc,
                cvTermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 20, 1);
            );
#else
            cout << "Please define either MEAN_SHIFT_TRACKING or CAM_SHIFT_TRACKING." << endl;
#endif

            rectangle(frame, m_rc, Scalar(0,0, 255), 3);
        }

        imshow(chapter19::TRACKER_WINDOW.data(), frame);

        char ch = waitKey(33);
        if(ch == 27) break;     // ESC key to exit
        else if(ch == 32)       // Space Key Pause
        {
            while((ch == waitKey(33)) != 32 && ch != 27);
            if(ch == 27) break;
        }
    }
}
