#include "split_and_merge.hpp"
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int chapter5::SplitAndMerge() {
    int w = 384, h = 384;
    Mat image, image_YUV, dst;
    vector<Mat> yuv_channels(3);

    image = imread("./resources/lena.jpg");
    resize(image, image, Size(w, h), IMREAD_COLOR);

    cvtColor(image, image_YUV, COLOR_BGR2YUV);

    split(image_YUV, yuv_channels);
    merge(yuv_channels, dst);

    imshow("input image", image);
    imshow("Y", yuv_channels[0]);
    imshow("U", yuv_channels[1]);
    imshow("V", yuv_channels[2]);
    imshow("YUV image", dst);

    waitKey(0);
    return 1;
}
