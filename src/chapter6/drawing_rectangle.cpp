#include "drawing_rectangle.hpp"

using namespace cv;
using namespace std;

int chapter6::DrawingRectangleWithRect() {
    Mat image = imread("./resources/lena.jpg");
    Rect rect1 = Rect(10, 10, 100, 100);
    Rect rect2 = Rect(200, 10, 100, 100);
    Rect rect3 = Rect(10, 200, 100, 100);
    rectangle(image, rect1, Scalar(255,0,0), 4, LINE_4, 0);
    rectangle(image, rect2, Scalar(0,255,0), 4, LINE_8, 0);
    rectangle(image, rect3, Scalar(0,0,255), 4, LINE_AA, 0);
    imshow("DrawingRectangleWithRect", image);
    waitKey(0);
    return 1;
}

int chapter6::DrawingRectangleWithPoints() {
    Mat image = imread("./resources/lena.jpg");
    Point points1[1][2] = {Point(10, 10), Point(100, 100)};
    Point points2[1][2] = {Point(200, 10), Point(100, 100)};
    Point points3[1][2] = {Point(10, 200), Point(100, 100)};
    rectangle(image, points1[0][0], points1[0][1], Scalar(255,0,0), 4, LINE_4, 0);
    rectangle(image, points2[0][0], points2[0][1], Scalar(0,255,0), 4, LINE_8, 0);
    rectangle(image, points3[0][0], points3[0][1], Scalar(0,0,255), 4, LINE_AA, 0);
    imshow("DrawingRectangleWithPoints", image);
    waitKey(0);
    return 1;
}

int chapter6::FillRectangleWithRect() {
    Mat image = imread("./resources/lena.jpg");
    Point points1[1][2] = {Point(10, 10), Point(100, 100)};
    Point points2[1][2] = {Point(200, 10), Point(100, 100)};
    Point points3[1][2] = {Point(10, 200), Point(100, 100)};
    rectangle(image, points1[0][0], points1[0][1], Scalar(255,0,0), -1, LINE_4);
    rectangle(image, points2[0][0], points2[0][1], Scalar(0,255,0), -1, LINE_8);
    rectangle(image, points3[0][0], points3[0][1], Scalar(0,0,255), -1, LINE_AA);
    imshow("FillRectangleWithPoints", image);
    waitKey(0);
    return 1;
}
