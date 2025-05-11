#include "line_detection.hpp"

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
    int threshold = 150;        // 150번 활용 되었을떄, 선이라고 한다.

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
        x0 = a * pos.rho; // 점
        y0 = b * pos.rho; // 점
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

struct LineTrackBarData {
    Mat* image;
    Mat* edge_image;
    Mat* result_image;
};

void static DrawLine(Mat& image, Mat& result_image, const vector<Vec4i>& lines) {
    Point pt[2] = { {0,0}, {0,0} };
    result_image = image.clone();
    for(int i = 0; i < lines.size(); i++) {
        pt[0].x = lines[i][0]; pt[0].y = lines[i][1];
        pt[1].x = lines[i][2]; pt[1].y = lines[i][3];
        line(result_image, pt[0], pt[0], Scalar(0, 0, 255), 3, 8);
    }
}

void static ContolTrackBar(int, void* userdata) {
    LineTrackBarData* data = reinterpret_cast<LineTrackBarData*>(userdata);

    Mat& image          = *(data->image);
    Mat& edge_image     = *(data->edge_image);
    Mat& result_image   = *(data->result_image);
    int threshold       = getTrackbarPos("Line Threshold",  chapter16::HOUGH_LINE_P_RESULT);
    int minLineLength   = getTrackbarPos("Min Line Length", chapter16::HOUGH_LINE_P_RESULT);
    int maxLineGap      = getTrackbarPos("Max Line Gap",    chapter16::HOUGH_LINE_P_RESULT);

    vector<Vec4i> lines;
    HoughLinesP(edge_image, lines, 1, CV_PI/180, threshold, minLineLength, maxLineGap);
    DrawLine(image, result_image, lines);
    imshow(chapter16::HOUGH_LINE_P_RESULT, result_image);
    cout << "threshold : " << threshold << " ";
    cout << "minLineLength : " << minLineLength << " ";
    cout << "maxLineGap : " << maxLineGap << endl;
}

void static DrawLineModulateTrackbar(const string& window_name, Mat& image, Mat& edge_image, Mat& result_image) {
    int threshold = 150;

    LineTrackBarData data = { &image, &edge_image, &result_image };

    createTrackbar(chapter16::HOUGH_LINE_P_MIN_LINE_LENGTH,    window_name, nullptr, 1000, ContolTrackBar, &data);
    createTrackbar(chapter16::HOUGH_LINE_P_MAX_LINE_GAP,       window_name, nullptr, 1000, ContolTrackBar, &data);
    createTrackbar(chapter16::HOUGH_LINE_P_LINE_THRESHOLD,     window_name, nullptr, 255, ContolTrackBar, &data);

    waitKey(0);
}

int chapter16::HoughLinesPDetection() {
    Mat image, blurred_image, gray_image, edge_image, result_image;
    image = imread("./data/board5.png");

    bilateralFilter(    image,      // src: 입력 이미지 (Mat)
                        blurred_image,      // dst: 결과 이미지 (Mat)
                        5,          // d: 필터링에 사용할 이웃 픽셀의 지름(보통 5~15 정도 사용)
                        50,         // sigmaColor: 색상 차이에 대한 표준편차(값이 클수록 색상 차이가 커도 영향을 받음)
                        50          // sigmaSpace: 공간적 거리(좌표) 표준편차(값이 클수록 멀리 있는 픽셀도 영향을 줌)
                    );
    image = blurred_image.clone();
    result_image = image.clone();

    cvtColor(image, gray_image, COLOR_BGR2GRAY);
    Canny(gray_image, edge_image, 0, 255, 3);
    vector<Vec4i> lines;
    HoughLinesP(edge_image, lines, 1, CV_PI/180, 50, 10, 300); //길이가 10 이상이 아니면 버리기, 간격이 300 이상이면 버리기
    DrawLine(image, result_image, lines);

    imshow(chapter16::HOUGH_LINE_P_IMAGE,  gray_image);
    imshow(chapter16::HOUGH_LINE_P_EDGE,   edge_image);
    imshow(chapter16::HOUGH_LINE_P_RESULT, result_image);

    // 에지 이미지 생성
    DrawEdgeModulateTrackbar(chapter16::HOUGH_LINE_P_EDGE,     gray_image, edge_image);
    DrawLineModulateTrackbar(chapter16::HOUGH_LINE_P_RESULT,   image, edge_image, result_image);

    imshow(chapter16::HOUGH_LINE_P_IMAGE,  gray_image);
    imshow(chapter16::HOUGH_LINE_P_EDGE,   edge_image);
    imshow(chapter16::HOUGH_LINE_P_RESULT, result_image);
    waitKey(0);

    return 1;
}
