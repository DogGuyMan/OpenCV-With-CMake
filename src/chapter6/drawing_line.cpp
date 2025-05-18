#include "drawing_line.hpp"

using namespace std;
using namespace cv;

int chapter6::DrawingLine() {
    Mat image = imread("./resources/lena.jpg");

    Point p1(25,25), p2(100, 50);
    line(image, p1, p2, Scalar(0,255,255), 8, 4, 0);
    imshow("line on image", image);
    waitKey(0);
    return 0;
}
