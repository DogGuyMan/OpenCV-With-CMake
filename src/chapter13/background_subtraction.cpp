#include "background_subtraction.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace cv;

int chapter13::MeanFilterSubtraction() {
    Mat frame, sum, avg;
    VideoCapture capture;
    if(capture.open("./data/vtest.avi") == false) return -1;
    double fps = capture.get(CAP_PROP_FPS);
    int total_frames = capture.get(CAP_PROP_FRAME_COUNT);
    int cnt = 2;
    capture >> avg;

    for(int i = 0; i < 100; i++) {
        if (!capture.read(frame) || frame.empty()) break;
        add((frame / cnt), (avg * (cnt-1)) / cnt, avg);
        cnt++;
        cout << i << "/100" << '\n';
    }
    imshow("avg background", avg);
    waitKey(0);
    return 1;
}

uchar static GetMedianWithVector(vector<uchar>& v) {
    nth_element(v.begin(), v.begin() + (v.size() / 2), v.end());
    return v[v.size() / 2];
}

int chapter13::MedianFilterSubtraction() {
    /* Video Capture 열기 */
    VideoCapture cap("./data/vtest.avi");

    Mat frame;
    vector<Mat> frames;


    for(int i = 0; i < 100; ++i) {
        cap >> frame;
        frames.push_back(frame.clone());
        cout << i << "/100" << '\n';
    }

    Size img_size = frames[0].size();
    cap.release();
    Mat background(img_size, frame.type());

    vector<uchar> pixels_by_times[3];
    pixels_by_times[0].reserve(100);
    pixels_by_times[1].reserve(100);
    pixels_by_times[2].reserve(100);

    for(int y = 0; y < img_size.height; ++y) {
        for(int x = 0; x < img_size.width; ++x) {
            Vec3b medianPixel;
            pixels_by_times[0].clear();
            pixels_by_times[1].clear();
            pixels_by_times[2].clear();

            for(auto& f : frames) {
                Vec3b pixel = f.at<Vec3b>(y, x);
                pixels_by_times[0].push_back(pixel[0]);
                pixels_by_times[1].push_back(pixel[1]);
                pixels_by_times[2].push_back(pixel[2]);
            }

            medianPixel = {
                GetMedianWithVector(pixels_by_times[0]),
                GetMedianWithVector(pixels_by_times[1]),
                GetMedianWithVector(pixels_by_times[2])
            };

            background.at<Vec3b>(y, x) = medianPixel;
        }
    }

    imshow("median Background", background);
    waitKey(0);
    return 1;
}
