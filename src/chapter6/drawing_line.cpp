#include "drawing_line.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int chapter6::DrawingLine() {
    Mat image = imread("./data/lena.jpg");

    Point p1(25,25), p2(100, 50);
    line(image, p1, p2, Scalar(0,255,255), 8, 4, 0);
    imshow("line on image", image);
    waitKey(0);
    return 0;
}
