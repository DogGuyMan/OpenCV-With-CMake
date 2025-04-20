#include "spatial_emboss_filtering.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int chapter10::SpatialEmbossFiltering() {
    Mat image = imread("./data/lena.jpg", 0);
    Mat embossKernal = (Mat_<int>(3, 3) <<  -2 ,-1 ,0,
                                            -1 ,1 ,1,
                                             0 ,1 ,2);
    Mat embossed_float_image, embossed_delta_image;

    // filter2D 함수의 delta 파라미터에 128을 추가하는 것은,
    // 필터 연산 후 손실을 방지하는 다른 방법으로,
    // 필터링 결과에서 발생할 수 있는 음수 값을 중간 값(예: 128)을 기준으로 이동시켜,
    filter2D(image, embossed_delta_image, -1, embossKernal, Point(1, 1), 128);

    // 또한 CV_32F로 결과를 저장하여 필터 연산 후 손실을 방지하는 다른 방법으로 쓸 수 있다.
    filter2D(image, embossed_float_image, CV_32F , embossKernal);
    embossed_float_image.convertTo(embossed_float_image, CV_8U);

    imshow("origial image", image);
    imshow("emboss delat image", embossed_delta_image);
    imshow("emboss float image", embossed_float_image);
    waitKey(0);
    return 1;
}
