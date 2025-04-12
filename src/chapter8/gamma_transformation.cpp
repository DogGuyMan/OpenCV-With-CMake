#include "gamma_transformation.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace cv;

int chapter8::GammaTransformation() {
    Mat image = imread("./data/lena.jpg", 0);
    Mat gamma_image;
    MatIterator_<uchar> it, end;
    const float gamma = 0.5;
    uchar pix[256];
    for(int i = 0; i < 256; i++) {
        pix[i] = saturate_cast<uchar>(
            pow((float)(i/255.0), gamma) * 255.0f
        );
    }
    gamma_image = image.clone();

    for(it = gamma_image.begin<uchar>(); it != gamma_image.end<uchar>(); ++it) {
        *it = pix[*it];
    }

    imshow("original image", image);
    imshow("gamma image", gamma_image);
    waitKey(0);
    return 1;
}
