#include "erosion_and_dilation.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int chapter14::ErosionAndDilation() {
    Mat image, erosion, dilation;
    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(16, 16));
    image = imread("./resources/coins.png", 0);
    resize(image, image, Size(0,0), 1.5, 1.5);
    threshold(image, image, 0, 255, THRESH_BINARY | THRESH_OTSU);

    erode(image, erosion, kernel);
    dilate(image, dilation, kernel);

    imshow("image", image);
    imshow("erosion", erosion);
    imshow("dilation", dilation);
    waitKey(0);
    return 1;
}
