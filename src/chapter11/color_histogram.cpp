#include "color_histogram.hpp"
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int chapter11::HistogramEqualizeYCrCbAndHSV() {
    Mat image = imread("./data/lena.jpg");
    Mat ycrcb_image, hsv_image;
    Mat equalized_ycrcb_image, equalized_hsv_image;
    cvtColor(image, ycrcb_image, COLOR_BGR2YCrCb);
    cvtColor(image, hsv_image, COLOR_BGR2HSV);
    vector<Mat> splited_ycrcb;
    vector<Mat> splited_hsv;

    split(ycrcb_image, splited_ycrcb);
    split(hsv_image, splited_hsv);

    equalizeHist(splited_ycrcb[0], splited_ycrcb[0]);
    equalizeHist(splited_hsv[2], splited_hsv[2]);

    merge(splited_ycrcb, equalized_ycrcb_image);
    merge(splited_hsv, equalized_hsv_image);
    cvtColor(equalized_ycrcb_image, equalized_ycrcb_image, COLOR_YCrCb2BGR);
    cvtColor(equalized_hsv_image, equalized_hsv_image, COLOR_HSV2BGR);

    imshow("origin image", image);
    imshow("equalized ycrcb image", equalized_ycrcb_image);
    imshow("equalized hsv image", equalized_hsv_image);

    waitKey(0);
    return 1;
}

int chapter11::HistogramBackProject(){return 1;}
