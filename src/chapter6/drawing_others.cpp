#include "drawing_others.hpp"

using namespace std;
using namespace cv;

// 제네릭 포인터(Generic Pointer)  void* userdata
void chapter6::onMouse(int event, int x, int y, int flags, void* userdata) {
    // 나 데이터의 실제 타입을 알지 못하므로 직접 역참조는 불가능.
    // 따라서 reinterpret_cast 또는 static_cast를 사용하여 올바른 타입으로 변환함.
    bool* isOnceClicked = reinterpret_cast<bool*>(userdata);

    // cv내부에 인풋 이벤트가 있다.
    if (event == cv::EVENT_LBUTTONDOWN) {
        cout << "Mouse clicked at (" << x << ", " << y << "). Exiting program." << endl;
        *isOnceClicked = true;
    }
}

void chapter6::WaitForMouseInput(const string& windowName) {
    bool IsOnceClicked = false;
    // 레퍼런스 전달을 해도 문제가 없다.
    setMouseCallback(windowName, onMouse, &IsOnceClicked);

    while(true){
        if(IsOnceClicked) {
            cout << "Exiting program as isOnceClicked is true." << endl;
            break;
        }
        waitKey(10);
    }
}

struct EdgeTrackBarData {
    string windowName;
    Mat* targetImage;
    Mat* maskImage;
};

void chapter6::onTrackbar(int intencity, void* userdata) {
    EdgeTrackBarData* data = reinterpret_cast<EdgeTrackBarData*>(userdata);
    Mat* targetImage = data->targetImage;
    Mat* maskImage = data->maskImage;
    imshow("targetImage", *targetImage);
    imshow("maskImage", *maskImage);
    Mat bitXorImage;
    circle(
        *maskImage,
        Point(maskImage->rows /2 , maskImage->cols /2),
        (maskImage->rows /2), Scalar(intencity, intencity, intencity), -1, LINE_AA, 0);
    bitwise_xor(*targetImage, *maskImage, bitXorImage);
    imshow(data->windowName, bitXorImage);
}

int chapter6::DrawingArrow(){
    const string WINDOW_NAME = "drawing arrowed on image";
    Mat image = Mat::zeros(400, 400, CV_8UC3);

    // 선 그리기
    Point start(100, 100);
    Point end(300,300);
    Scalar color(0, 255, 0);
    int thickness = 2;

    arrowedLine(image, start, end, color, thickness);
    imshow(WINDOW_NAME, image);
    WaitForMouseInput(WINDOW_NAME);
    return 1;
}

int chapter6::DrawingMarker(){
    const string WINDOW_NAME = "drawing marker on image";
    Mat image = Mat::zeros(400, 400, CV_8UC3);

    // 마커 그리기
    cv::Point center(250, 250);   // 중심점
    cv::Scalar color(255, 0, 0);  // 파란색
    int markerType = cv::MARKER_CROSS; // 마커 타입
    int markerSize = 50;
    int thickness = 2;

    cv::drawMarker(image, center, color, markerType, markerSize, thickness);
    imshow(WINDOW_NAME, image);

    WaitForMouseInput(WINDOW_NAME);
    return 1;
}

int chapter6::DrawingTrackbar(){
    const string WINDOW_NAME = "drawing xor mask change trackbar on image";
    int intensity = 128;
    Mat image = imread("./resources/lena.jpg");
    resize(image, image, Size(400, 400), IMREAD_COLOR);

    Mat circleMat = Mat::zeros(Size(400,400), CV_8UC3);
    circle(circleMat, Point(200, 200), 200, Scalar(255,255,255), -1, LINE_AA, 0);

    EdgeTrackBarData userData = {
        WINDOW_NAME,
        &image,
        &circleMat
    };

    namedWindow(WINDOW_NAME);

    cv::createTrackbar("xor mask", WINDOW_NAME, &intensity, 255, onTrackbar, &userData);

    while (waitKey(10) != 'q')
    {

    }

    return 1;
}
