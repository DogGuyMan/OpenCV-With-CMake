#include "usage_of_hsl.hpp"
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int chapter11::UsageOfHSL() {
    Mat image = imread("./data/colorful.jpeg");
    Mat HSV, intensity_change, mask_out, change_color;
    vector<Mat> splited_intensity_change(3);
    vector<Mat> splited_mask_out(3);
    vector<Mat> splited_change_color(3);

    int rows = image.rows;
    int cols = image.cols;

    uchar* hue;
    uchar* saturate;
    uchar* intensity_value;

    cvtColor(image, HSV, COLOR_BGR2HSV);
    split(HSV, splited_intensity_change);
    split(HSV, splited_mask_out);
    split(HSV, splited_change_color);

    // 1
    equalizeHist(splited_intensity_change[2], splited_intensity_change[2]);

    // 2

    // 3


    return 1;
}
