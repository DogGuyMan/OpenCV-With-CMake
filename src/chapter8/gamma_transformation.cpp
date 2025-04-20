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
    uchar pix[256]; // 일명 룩업 테이블 픽셀 Intencity에 대응되는 값을 매핑해 주는 함수를 제작하는것이다.
    for(int i = 0; i < 256; i++) {
        // i는 0~255사이의 범위를 가진다.
        // 그리고 이걸 0~1사이의 값을 가지도록 하고 감마 제곱을 시킨다.
            // 만약 이걸 0~1사이 값을 안하게 되면, 존~~~ 매우 큰 값을 가지게 되므로 그렇다.
            // 그렇게 되면 그냥 하얀 이미지만 나올 것이 분명하다.
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
