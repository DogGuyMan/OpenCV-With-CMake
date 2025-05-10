#include "line_detection.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

struct PolarCoord {
    float rho;
    float theta;
};

// TrackBarCallback이 너무 응집력 없이 분산되어 있는 점을 착안해 TrackBar를 그리는 것을 클래스 캡슐화하는 방식을 사용했지만
// 하지만, OpenCV의 트랙바 자체가 임시적이고 단순한 디버깅/튜닝 용도에 가깝기 때문에, 너무 복잡하게 구조화하는 것은 오히려 과도할 수 있다.
// 실무에서는 트랙바를 캡슐화하되, 필요 이상으로 추상화하지 않는 것이 현실적이다.
class EdgeTrackBar {

public :
   EdgeTrackBar(const string& window_name, const Mat& image, const Mat& edge_image)
       : WINDOW_NAME(window_name),
         mImagePtr(makePtr<Mat>(image)),
         mEdgeImagePtr(makePtr<Mat>(edge_image)),
         mThresholdMin(0),
         mThresholdMax(0)
   {}

    void ImageShowWithTrackbar() {
        createTrackbar("Threshold Min", WINDOW_NAME, &mThresholdMin, 255, ControlCannyMinThreshold, this);
        createTrackbar("Threshold Max", WINDOW_NAME, &mThresholdMax, 255, ControlCannyMaxThreshold, this);
    }

private :
    const string    WINDOW_NAME;
    Ptr<Mat>        mImagePtr;
    Ptr<Mat>        mEdgeImagePtr;
    int             mThresholdMin;
    int             mThresholdMax;

    static void ControlCannyMinThreshold(int threshold, void* userData) {
        auto* self = reinterpret_cast<EdgeTrackBar*>(userData);
        self->mThresholdMin = threshold;
        Canny(*self->mImagePtr, *self->mEdgeImagePtr, self->mThresholdMin, self->mThresholdMax, 3);
        imshow(self->WINDOW_NAME, *self->mEdgeImagePtr);
        cout    << "ThresholdMin: " << self->mThresholdMin << ", ThresholdMax: " << self->mThresholdMax << endl;
    }

    static void ControlCannyMaxThreshold(int threshold, void* userData) {
        auto* self = reinterpret_cast<EdgeTrackBar*>(userData);
        self->mThresholdMax = threshold;
        Canny(*self->mImagePtr, *self->mEdgeImagePtr, self->mThresholdMin, self->mThresholdMax, 3);
        imshow(self->WINDOW_NAME, *self->mEdgeImagePtr);
        cout    << "ThresholdMin: " << self->mThresholdMin << ", ThresholdMax: " << self->mThresholdMax << endl;
    }
};

void static DrawEdgeModulateTrackbar(const string& window_name, Mat& image, Mat& edge_image) {
    const string WINDOW_NAME = window_name;

    int threshold_min = 0;
    int threshold_max = 0;

    EdgeTrackBar edge_track_bar = EdgeTrackBar(WINDOW_NAME, image, edge_image);
    edge_track_bar.ImageShowWithTrackbar();

    waitKey(0);
}

struct LineTrackBarData {
    double* rho;
    double* theta;
    int* threshold;
    Mat* edge_image;
    Mat* result_image;
    int* min_line_length;
    int* max_line_gap;
};

void static ContolMinLineLength(int, void* userdata) {
    LineTrackBarData* data = reinterpret_cast<LineTrackBarData*>(userdata);
    double& rho = *data->rho;
    double& theta = *data->theta;
    int& threshold = *data->threshold;
    Mat& edge_image = *data->edge_image;
    Mat& result_image = *data->result_image;
    int minLineLength = getTrackbarPos("Min Line Length", "Hough Line P Detection result");
    int maxLineGap = getTrackbarPos("Max Line Gap", "Hough Line P Detection result");
    vector<Vec4i> lines;
    HoughLinesP(edge_image, lines, rho, theta, threshold, minLineLength, maxLineGap);

    result_image = Mat::zeros(result_image.size(), result_image.type()); // 결과 이미지 초기화
    for(int i = 0; i < lines.size(); i++) {
        Point pt1(lines[i][0], lines[i][1]);
        Point pt2(lines[i][2], lines[i][3]);
        line(result_image, pt1, pt2, Scalar(0, 0, 255), 3, 8);
    }
    imshow("Hough Line P Detection result", result_image);
}

void static ContolMaxLineGap(int, void* userdata) {
    LineTrackBarData* data = reinterpret_cast<LineTrackBarData*>(userdata);
    double& rho = *data->rho;
    double& theta = *data->theta;
    int& threshold = *data->threshold;
    Mat& edge_image = *data->edge_image;
    Mat& result_image = *data->result_image;
    int minLineLength = getTrackbarPos("Min Line Length", "Hough Line P Detection result");
    int maxLineGap = getTrackbarPos("Max Line Gap", "Hough Line P Detection result");
    vector<Vec4i> lines;
    HoughLinesP(edge_image, lines, rho, theta, threshold, minLineLength, maxLineGap);

    result_image = Mat::zeros(result_image.size(), result_image.type()); // 결과 이미지 초기화
    for(int i = 0; i < lines.size(); i++) {
        Point pt1(lines[i][0], lines[i][1]);
        Point pt2(lines[i][2], lines[i][3]);
        line(result_image, pt1, pt2, Scalar(0, 0, 255), 3, 8);
    }
    imshow("Hough Line P Detection result", result_image);
}

void static DrawLineModulateTrackbar(const string& window_name, Mat& edge_image, Mat& result_image) {
    double rho = 1;
    double theta = CV_PI/180;
    int threshold = 150;

    // HoughLinesP 에 추가로 사용될 변수
    int minLineLength = 0;
    int maxLineGap = 0;

    LineTrackBarData data = {
        &rho,
        &theta,
        &threshold,
        &edge_image,
        &result_image,
        &minLineLength,
        &maxLineGap
    };

    createTrackbar("Min Line Length", window_name, nullptr, 1000, ContolMinLineLength, &data);
    createTrackbar("Max Line Gap", window_name, nullptr, 1000, ContolMaxLineGap, &data);

    waitKey(0);
}

int chapter16::HoughLineDetection() {
    Mat image, edge_image, result_image;
    image = imread("./data/board5.png");
    result_image = image.clone();
    Canny(image, edge_image, 0, 255, 3);

    cvtColor(image, image, COLOR_BGR2GRAY);

    imshow("Hough Line Detection Input image", image);
    imshow("Hough Line Detection edge", edge_image);

    // 에지 이미지 생성
    DrawEdgeModulateTrackbar("Hough Line Detection edge", image, edge_image);

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

    imshow("Hough Line Detection Input image", image);
    imshow("Hough Line Detection edge", edge_image);
    imshow("Hough Transform", result_image);
    waitKey(0);
    return 1;
}

int chapter16::HoughLinesPDetection() {
        Mat image, edge_image, result_image;
    image = imread("./data/board5.png");
    result_image = image.clone();
    Canny(image, edge_image, 0, 255, 3);

    cvtColor(image, image, COLOR_BGR2GRAY);

    imshow("Hough Line P Detection Input image", image);
    imshow("Hough Line P Detection edge", edge_image);

    // 에지 이미지 생성
    DrawEdgeModulateTrackbar("Hough Line P Detection edge", image, edge_image);
    DrawLineModulateTrackbar("Hough Line P Detection result", edge_image, result_image);

    imshow("Hough Line P Detection Input image", image);
    imshow("Hough Line P Detection edge", edge_image);
    imshow("Hough Line P Detection result", result_image);
    waitKey(0);

    return 1;
}
