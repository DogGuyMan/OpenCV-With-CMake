#include "drawing_circle.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int chapter6::DrawingCircle() {
    Mat image = imread("./resources/lena.jpg");

    Point center(100,60);
    int radius = 40;
    circle(image, center, radius, Scalar(0,255,255), 8, 4, 0);
    imshow("circle on image", image);
    waitKey(0);
    return 0;
}


int chapter6::FillCircle() {
    Mat image = imread("./resources/lena.jpg");

    Point center(image.size().width / 2, image.size().height / 2);
    int radius = 150;
    circle(image, center, radius, Scalar(0,255,255), -1, 4, 0);
    imshow("fiil circle on image", image);
    waitKey(0);
    return 0;
}
