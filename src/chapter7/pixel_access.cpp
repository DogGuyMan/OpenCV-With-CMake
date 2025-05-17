#
#include "pixel_access.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace cv;

// uchars
// Vec3b
// image.channels()

// Value At(50, 100) : 76 70 181
int chapter7::PixelAccessByAt() {
    Mat image, image_gray;
    int value, value_B, value_G, value_R, channels;

    image = imread("./resources/lena.jpg");
    image_gray = imread("./resources/lena.jpg", 0);

    channels = image.channels();

    switch(channels) {
        case 1 : {
            value = image.at<uchar>(50, 100);
            cout << "value : " << value;
            break;
        }
        case 3 : {
            Vec3b colorValue = image.at<Vec3b>(50, 100);
            value_B = colorValue[0];
            value_G = colorValue[1];
            value_R = colorValue[2];
            cout << "Value At(50, 100) : "  << value_B << ' '
                                            << value_G << ' '
                                            << value_R << ' ' << endl;
            break;
        }
    }
    return 1;
}

int chapter7::PixelAccessByPointer() {
    Mat image = imread("./resources/lena.jpg");
    int value, value_B, value_G, value_R, channels;
    channels = image.channels();

    uchar* p = image.ptr<uchar>(50);
    value_B = p[100 * channels + 0];
    value_G = p[100 * channels + 1];
    value_R = p[100 * channels + 2];
    cout << "Value At(50, 100) : "  << value_B << ' '
                                    << value_G << ' '
                                    << value_R << ' ' << endl;

    const int WANT_ROW = 50;
    const int WANT_COL = 100;
    uchar* data = (uchar*)image.data;
    int WANT_ROW_N_COL = ((WANT_ROW * image.cols) + WANT_COL);
    value_B = p[((WANT_ROW_N_COL) * channels) + 0];
    value_G = p[((WANT_ROW_N_COL) * channels) + 1];
    value_R = p[((WANT_ROW_N_COL) * channels) + 2];
    cout << "Value At(50, 100) : "  << value_B << ' '
                                    << value_G << ' '
                                    << value_R << ' ' << endl;

    return 1;
}

int chapter7::PixelAccessByIterator() {
    Mat image, image_gray;
    int value, value_B, value_G, value_R, channels;

    image = imread("./resources/lena.jpg");
    image_gray = imread("./resources/lena.jpg", 0);

    channels = image.channels();

    MatIterator_ <uchar> it, end;
    MatIterator_ <Vec3b> it3, end3;

    switch (channels)
    {
        case 1 : {
            for(it = image.begin<uchar>(), end = image.end<uchar>(); it != end; ++it){
                value = *it;
                cout << "value : " << value << endl;
            }
            break;
        }
        case 3 : {
            for(it3 = image.begin<Vec3b>(), end3 = image.end<Vec3b>(); it3 != end3; ++it3){
                value_B = (*it3)[0];
                value_G = (*it3)[1];
                value_R = (*it3)[2];
                cout    << "B : " << value_B
                        << "G : " << value_G
                        << "R : " << value_R << endl;
            }
            break;
        }
    }

    return 1;
}
