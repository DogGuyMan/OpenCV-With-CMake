#include "drawing_polygon.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int chapter6::DrawingPolygon() {
    Mat image = Mat::zeros(400,400, CV_8UC3);
    int w = 400, h = 400;
    Point trapezoid[1][4] = {
        Point(w*2/6, w/4),
        Point(w*4/6, w/4),
        Point(w*5/6, w*3/4),
        Point(w/6,   w*3/4),
    };

    const Point* ppt[1] = {trapezoid[0]};
    int npt[] = {4};
    fillPoly(image, ppt, npt, 1, Scalar(255,255,255), 8);
    imshow("drawing polygon", image);
    waitKey(0);
    return 0;
}


int chapter6::DrawingPolyLine() {
    return 0;
}
