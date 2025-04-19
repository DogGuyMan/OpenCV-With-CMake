#include "extra_matrix_operation.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int chapter5::MatrixConsturct() {
    Mat zeroMat = Mat::zeros(8, 8, CV_8U);
    Mat oneMat = Mat::ones(8, 8, CV_8U);
    Mat eyeMat = Mat::eye(8, 8, CV_8U);

    // imshow("zeroMat", zeroMat);
    // imshow("oneMat", oneMat);
    // imshow("eysMat", eyeMat);

    for(Mat_<uchar>::iterator it = zeroMat.begin<uchar>(); it != zeroMat.end<uchar>(); ++it) {
        cout << (*it) << ' ';
    }
    for(Mat_<uchar>::iterator it = oneMat.begin<uchar>(); it != oneMat.end<uchar>(); ++it) {
        cout << (*it) << ' ';
    }
    for(Mat_<uchar>::iterator it = eyeMat.begin<uchar>(); it != eyeMat.end<uchar>(); ++it) {
        cout << (*it) << ' ';
    }
    return 1;
}
int chapter5::AlgebricMatrixOperation() {

    return 1;
}
int chapter5::MatrixConcatination() {

    return 1;
}
int chapter5::MatrixBitwise() {
    Mat image = imread("./data/lena.jpg");
    resize(image, image, Size(200, 200), IMREAD_COLOR);
    Mat circleMat = Mat::zeros(Size(200,200), CV_8UC3);
    circle(circleMat, Point(100, 100), 100, Scalar(255,255,255), -1, LINE_AA, 0);

    Mat bitAddImage, bitOrImage, bitXorImage, bitNotImage;

    bitwise_and(image, circleMat, bitAddImage);
    bitwise_or(image, circleMat, bitOrImage);
    bitwise_xor(image, circleMat, bitXorImage);
    bitwise_not(image, bitNotImage);


    imshow("Bit ADD  Image", bitAddImage);
    imshow("Bit OR  Image", bitOrImage);
    imshow("Bit XOR  Image", bitXorImage);
    imshow("Bit NOT  Image", bitNotImage);

    waitKey(0);
    return 1;
}

int chapter5::MatrixInverted() {
    Mat image = imread("./data/lena.jpg");
    MatExpr imageInverted = ~(image.clone());

    imshow("Original Image", image);
    imshow("Inverted Image", imageInverted);

    while(true) {
        int key = cv::waitKey();
        if(key == 'q')
            break;
    }
}
