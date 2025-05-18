#include "log_transformation.hpp"

using namespace std;
using namespace cv;

const double C = 1.5f;

int chapter8::LogTransformation() {
    Mat image = imread("./resources/lena.jpg", 0);
    Mat float_image, log_image;
    // 로그 변환에서 사용할 수 있으려면, Float형의 데이터 타입을 써야 하므로 그렇다.
    image.convertTo(float_image, CV_32F);
    float_image = abs(float_image) + 1;
    // 0~ 255같은 정수 범위가 아니라, 실수 변환이 되므로 그렇다.
    log(float_image, float_image);
    // 실수 로그 변환 된것을 다시 0~255사이로 존재하도록 정구화 시켜준다.
    normalize(float_image, float_image, 0, 255, NORM_MINMAX);
    convertScaleAbs(float_image, log_image, C);

    imshow("original image", image);
    imshow("log image", log_image);

    waitKey(0);
    return 1;
}
