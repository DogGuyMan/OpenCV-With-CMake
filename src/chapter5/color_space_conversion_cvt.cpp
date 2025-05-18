#include "color_space_conversion_cvt.hpp"

using namespace cv;
using namespace std;

int chapter5::ColorSpaceConversionCvt() {
    int w = 512, h = 512;
    Mat imageOrigin = imread("./resources/lena.jpg", IMREAD_COLOR);
    resize(imageOrigin, imageOrigin, Size(w, h), INTER_LINEAR);
    Mat GaryImage, HSVImage, YCrCvImage, LabIamge, YUVImage;
    cvtColor(imageOrigin, GaryImage, COLOR_BGR2GRAY);
    cvtColor(imageOrigin, HSVImage, COLOR_BGR2HSV);
    cvtColor(imageOrigin, YCrCvImage, COLOR_BGR2YCrCb);
    cvtColor(imageOrigin, LabIamge, COLOR_BGR2Lab);
    cvtColor(imageOrigin, YUVImage, COLOR_BGR2YUV);

    imshow("RGB image", imageOrigin);
    imshow("Gary Image", GaryImage);
    imshow("HSV Image", HSVImage);
    imshow("YCrCv Image", YCrCvImage);
    imshow("Lab Image", LabIamge);
    imshow("YUV Image", YUVImage);

    waitKey(0);
    return 0;
}
