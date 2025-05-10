#include "line_detection.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

struct PolarCoord {
    float rho;
    float theta;
};

struct TrackBarData {
    Mat* image;
    Mat* edge_image;
    int* threshold_min;
    int* threshold_max;
};

void static TrackThresholdMin(int threshold, void* userdata) {
    TrackBarData* data = reinterpret_cast<TrackBarData*>(userdata);
    Mat* image = data->image;
    Mat* edge_image = data->edge_image;
    int fixed_threshold_image = *(data->threshold_max);
    int* threshold_min = data->threshold_min;
    *threshold_min = threshold;
    Canny(*image, *edge_image, *threshold_min, fixed_threshold_image, 3);
}

void static TrackThresholdMax(int threshold, void* userdata) {
    TrackBarData* data = reinterpret_cast<TrackBarData*>(userdata);
    Mat* image = data->image;
    Mat* edge_image = data->edge_image;
    int fixed_threshold_image = *(data->threshold_min);
    int* threshold_max = data->threshold_min;

    *threshold_max = threshold;
    Canny(*image, *edge_image, fixed_threshold_image, *threshold_max, 3);
}

void static DrawTrackbar(const string& window_name, Mat& image, Mat& edge_image) {
    const string WINDOW_NAME = window_name;

    int threshold_min = 0;
    int threshold_max = 255;

    TrackBarData data = {
        &image, &edge_image,
        &threshold_min, &threshold_max
    };

    createTrackbar("Threshold Min", WINDOW_NAME, &threshold_min, 255, TrackThresholdMin, &data);
    createTrackbar("Threshold Max", WINDOW_NAME, &threshold_max, 255, TrackThresholdMax, &data);

    int threshold = 128;
}

int chapter16::HoughLineDetection() {
    Mat image, edge_image, result_image;
    image = imread("./data/board5.png");
    result_image = image.clone();

    cvtColor(image, image, COLOR_BGR2GRAY);

    // 에지 이미지 생성
    Canny(image, edge_image, 50, 200, 3);

    // 허프 선 검출
    vector<Vec2f> lines;
    double rho = 1;
    double theta = CV_PI/180;
    int threshold = 150;

    /*
    InputArray image, OutputArray lines,
    double rho, double theta, int threshold,
    */
    HoughLines(edge_image, lines, rho, theta, threshold);

    // 결과 이미지에 선 그리기
    Point pt[2];
    int a, b, x0, y0;
    for(int i = 0; i < lines.size(); i++) {
        PolarCoord pos = {lines[i][0], lines[i][1]};
        a = cos(pos.theta);
        b = sin(pos.theta);
        x0 = a * pos.rho;
        y0 = b * pos.rho;
        pt[0] = Point(cvRound(x0 + 1000*(-b)), cvRound(y0 + 1000*a));
        pt[1] = Point(cvRound(x0 - 1000*(-b)), cvRound(y0 - 1000*a));
        line(result_image, pt[0], pt[1], Scalar(0, 0, 255), 3, 8);
    }

    imshow("Input image", image);
    imshow("edge", edge_image);
    imshow("Hough Transform", result_image);
    waitKey(0);
    return 1;
}

int chapter16::HoughLineSpDetection() {
    return 1;
}
