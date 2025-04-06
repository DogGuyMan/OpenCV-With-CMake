#include "threshold_operations.hpp"
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void ThresholdWithBinaryType(Mat);
void ThresholdWithTruncType(Mat);

int chapter5::Threshold() {
    Mat image, dst;
    image = imread("./data/lena.jpg");
    resize(image, image, Size(300, 300), IMREAD_COLOR);
    cvtColor(image, image, COLOR_BGR2GRAY);
    // ThresholdWithBinaryType(image);
    ThresholdWithTruncType(image);

    waitKey(0);
    return 1;
}

void ThresholdWithBinaryType(Mat image) {
    Mat thresh[5];

    threshold(image, thresh[0], 255, 255, THRESH_BINARY);
    threshold(image, thresh[1], 127, 255, THRESH_BINARY);
    threshold(image, thresh[2], 189, 255, THRESH_BINARY);
    threshold(image, thresh[3], 63, 255, THRESH_BINARY);
    threshold(image, thresh[4], 0, 255, THRESH_BINARY);

    imshow("threshold Binary threshFullDst",   thresh[0]);
    imshow("threshold Binary threshHalfDst",   thresh[1]);
    imshow("threshold Binary thresh75Dst",     thresh[2]);
    imshow("threshold Binary thresh25Dst",     thresh[3]);
    imshow("threshold Binary threshZeroDst",   thresh[4]);
}

void ThresholdWithTruncType(Mat image) {
    Mat thresh[5];

    threshold(image, thresh[0], 255, 255, THRESH_TRUNC);
    threshold(image, thresh[1], 127, 255, THRESH_TRUNC);
    threshold(image, thresh[2], 189, 255, THRESH_TRUNC);
    threshold(image, thresh[3], 63, 255, THRESH_TRUNC);
    threshold(image, thresh[4], 0, 255, THRESH_TRUNC);

    imshow("threshold Trunc threshFullDst",   thresh[0]);
    imshow("threshold Trunc threshHalfDst",   thresh[1]);
    imshow("threshold Trunc thresh75Dst",     thresh[2]);
    imshow("threshold Trunc thresh25Dst",     thresh[3]);
    imshow("threshold Trunc threshZeroDst",   thresh[4]);
}


int chapter5::AdaptiveThreshold() {
    Mat image, dst;
    image = imread("./data/lena.jpg");
    resize(image, image, Size(300, 300), IMREAD_COLOR);
    cvtColor(image, image, COLOR_BGR2GRAY);

    Mat adaptive3, adaptive5, adaptive23;
    Mat gaussian3, gaussian5, gaussian23;

    adaptiveThreshold(image, adaptive3, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 0);
    adaptiveThreshold(image, adaptive5, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 0);
    adaptiveThreshold(image, adaptive23, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 23, 0);
    adaptiveThreshold(image, gaussian3, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, 0);
    adaptiveThreshold(image, gaussian5, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 0);
    adaptiveThreshold(image, gaussian23, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 23, 0);

    imshow("threshold MEAN 3", adaptive3);
    imshow("threshold MEAN 5", adaptive5);
    imshow("threshold MEAN 23", adaptive23);
    imshow("threshold GAUSSIAN 3", gaussian3);
    imshow("threshold GAUSSIAN 5", gaussian5);
    imshow("threshold GAUSSIAN 23", gaussian23);

    waitKey(0);
    return 1;
}

int chapter5::InRange() {
    Mat image = imread("./data/home.jpg");
    cvtColor(image, image, COLOR_BGR2YCrCb);

    imshow("image YCrCb", image);
    inRange(image, Scalar(0, 64, 64), Scalar(255, 128, 128), image);
    imshow("inRange", image);


    waitKey(0);
    return 1;
}
