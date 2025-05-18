#include "drawing_polygon.hpp"

using namespace std;
using namespace cv;

int chapter6::DrawingPolygon() {
    Mat image = Mat::zeros(400,400, CV_8UC3);
    int w = 400, h = 400;
    Point trapezoid[1][4] = {
        Point(w*2/6, h/4),
        Point(w*4/6, h/4),
        Point(w*5/6, h*3/4),
        Point(w/6,   h*3/4),
    };

    const Point* ppt[1] = {trapezoid[0]};
    int npt[] = {4};
    fillPoly(image, ppt, npt, 1, Scalar(255,255,255), 8);
    imshow("drawing polygon", image);
    waitKey(0);
    return 0;
}

int chapter6::DrawingMultiplePoly() {
    Mat image = Mat::zeros(400,400, CV_8UC3);
    int w = 400, h = 400;
    Point triagnle[1][3] = {Point(80, 10), Point(20, 140), Point(120, 140)};
    Point trapezium[1][4] = {Point(80, w-30), Point(200, w-10), Point(180, w-120),Point(80, w-120)};
    Point pentaogn[1][5] = {Point(300, 180), Point(350, 180), Point(380, 120),Point(325, 40), Point(270, 80)};
    const Point* ppt[3] = {triagnle[0], trapezium[0], pentaogn[0]};
    int npt[] = {3,4,5};
    fillPoly(image, ppt, npt, 3, Scalar(255,255,255), 8);
    imshow("drawing multiple poly", image);
    waitKey(0);
    return 0 ;
}

int chapter6::DrawingPolyLine() {
    Mat imageClosed = Mat::zeros(400,400, CV_8UC3);
    Mat imageOpened = Mat::zeros(400,400, CV_8UC3);
    int w = 400, h = 400;
    Point trapezoid[1][4] = {
        Point(w*2/6, h/4),
        Point(w*4/6, h/4),
        Point(w*5/6, h*3/4),
        Point(w/6,   h*3/4),
    };

    const Point* ppt[1] = {trapezoid[0]};
    int npt[] = {4};
    polylines(imageClosed, ppt, npt,1, true, Scalar(255,255,255), 4, LINE_AA);
    polylines(imageOpened, ppt, npt,1, false, Scalar(255,255,255), 4, LINE_AA);
    imshow("drawing close polyline", imageClosed);
    imshow("drawing open polyline", imageOpened);
    waitKey(0);
    return 0;
}
