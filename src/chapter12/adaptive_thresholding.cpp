#include "adaptive_thresholding.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int chapter12::AdaptiveThresholding() {
    Mat image = imread("./data/sudoku.png", IMREAD_GRAYSCALE);
    Mat global_thresholded_image;
    Mat adaptive_thresholded_image;

    threshold(image, global_thresholded_image, 0, 255, THRESH_BINARY | THRESH_OTSU);
    adaptiveThreshold(image, adaptive_thresholded_image, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 85, 15);

    imshow("original image", image);
    imshow("global thresholded image", global_thresholded_image);
    imshow("adaptive thresholded image", adaptive_thresholded_image);

    waitKey(0);
    return 1;
}
