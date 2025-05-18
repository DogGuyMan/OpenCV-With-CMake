#include "addition_and_subtraction.hpp"

using namespace cv;
using namespace std;

int chapter5::MatOriginal() {
    Mat image1 = imread("./resources/lena.jpg");
    resize(image1, image1, Size(300, 300), IMREAD_COLOR);
    Mat image2 = imread("./resources/gradient.png");
    imshow("Mat Original", image1);
    imshow("Mat Gradient", image2);
    waitKey(0);
    return 1;
}

int chapter5::MatAdd() {
    Mat image1 = imread("./resources/lena.jpg");
    resize(image1, image1, Size(300, 300), IMREAD_COLOR);
    Mat image2 = imread("./resources/gradient.png");
    Mat dst;

    add(image1, image2, dst);
    imshow("Mat Add", dst);
    waitKey(0);
    return 1;
}

int chapter5::MatScaleadd() {
    Mat image1 = imread("./resources/lena.jpg");
    resize(image1, image1, Size(300, 300), IMREAD_COLOR);
    Mat image2 = imread("./resources/gradient.png");
    Mat dst;

    scaleAdd(image1, 0.25, image2, dst);
    imshow("Mat Scale Add", dst);
    waitKey(0);
    return 1;
}

int chapter5::MatAbsdiff() {
    Mat image1 = imread("./resources/lena.jpg");
    resize(image1, image1, Size(300, 300), IMREAD_COLOR);
    Mat image2 = imread("./resources/gradient.png");
    Mat dst;
    absdiff(image1, image2, dst);
    imshow("Mat Abs Diff", dst);
    waitKey(0);
    return 1;
}

int chapter5::MatSubtract() {
    Mat image1 = imread("./resources/lena.jpg");
    resize(image1, image1, Size(300, 300), IMREAD_COLOR);
    Mat image2 = imread("./resources/gradient.png");
    Mat dst;
    subtract(image1, image2, dst);
    imshow("Mat Subtract", dst);
    waitKey(0);
    return 1;
}
