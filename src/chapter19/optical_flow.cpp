#include "optical_flow.hpp"

using namespace std;
using namespace cv;

static bool isInitialized = false;

int chapter19::OpticalFlow() {
    VideoCapture cap(0);
    if(!cap.isOpened()) {
        cerr << "Error: Could not open video capture." << endl;
        return -1;
    }
    double fps = cap.get(CAP_PROP_FPS);
    Mat cur_image, prev_image;
    Mat frame, dst_image;

    double quality_level = 0.01;
    double min_distance = 10;
    int block_size = 3;
    bool use_harris_detector = false;
    double k = 0.04;
    int max_corners = 500;

    TermCriteria criteria = TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 0.01);
    Size win_size(15, 15);

    vector<Point2f> prev_points;
    vector<Point2f> cur_points;
    vector<Point2f> bound_points;

    int delay = 1000 / fps;
    int nframe = 0;

    while(true) {
        cap >> frame;
        if(frame.empty()) break;

        frame.copyTo(dst_image);
        cvtColor(dst_image, cur_image, COLOR_BGR2GRAY);

        GaussianBlur(cur_image, cur_image, Size(5,5), 0.5);
        if(!isInitialized) {
            goodFeaturesToTrack(prev_image, prev_points, max_corners,
                                quality_level, min_distance, Mat(), block_size,
                                use_harris_detector, k);
            cornerSubPix(prev_image, prev_points, win_size, Size(-1,-1), criteria);
            DrawTrackingPoints(prev_points, dst_image);
            isInitialized = true;
        }

        if(prev_points.size() > 0) {
            vector<Mat> prevPyr, currPyr;
            Mat status, err;
            buildOpticalFlowPyramid(prev_image, prevPyr, win_size, 3, true);
            buildOpticalFlowPyramid(cur_image, currPyr, win_size, 3, true);
            calcOpticalFlowPyrLK(prevPyr, currPyr, prev_points, cur_points, status, err, win_size);

            for(int i = 0; i < prev_points.size(); i++) {
                if(!status.at<uchar>(i)) {
                    prev_points.erase(prev_points.begin() + i);
                    cur_points.erase(cur_points.begin() + i);
                }
            }
            DrawTrackingPoints(cur_points, dst_image);
            prev_points = cur_points;
        }

        imshow("dst image", dst_image);
        cur_image.copyTo(prev_image);

        int ch = waitKey(33);
        if (ch == 27) break; // 27 == ESC key
        if (ch == 32) isInitialized = false;
    }

    return 1;
}

void chapter19::DrawTrackingPoints(vector<Point2f> &points, Mat &img) {
    for(int i = 0; i < points.size(); i++) {
        int x = cvRound(points[i].x);
        int y = cvRound(points[i].y);
        circle(img, Point(x, y), 3, Scalar(255, 0,0), 2 );
    }
}
