#include "log_transformation.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <limits.h>
#include <cmath>

using namespace std;
using namespace cv;

const double C = 1.5f;

int chapter8::LogTransformation() {
    Mat image = imread("./data/lena.jpg", 0);
    Mat float_image, log_image;
    image.convertTo(float_image, CV_32F);
    float_image = abs(float_image) + 1;
    log(float_image, float_image);
    normalize(float_image, float_image, 0, 255, NORM_MINMAX);
    convertScaleAbs(float_image, log_image, C);

    imshow("original image", image);
    imshow("log image", log_image);

    waitKey(0);
}
