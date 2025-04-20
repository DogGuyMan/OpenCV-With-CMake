#include "read_an_image_in_openCV.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

namespace chapter4 {
    int ReadAnImageInOpenCV() {
        Mat gray_image, color_image;

        // 두번째 파라미터의 0이 들어가 있다.
        // 이것이 뜻하는 바는 이미지를 GrayScale 로 읽겠다는 것 이다.
        gray_image = imread("./data/lena.jpg", 0);

        // 두번째 파라미터에 1이 들어가 있거나
        // 아무 값도 작성하지 않는 다면 Color로 읽겠다는 것 이다.
        color_image = imread("./data/lena.jpg");

        imshow("gray image", gray_image);
        imshow("color image", color_image);

        waitKey(0);
        return 0;
    }
}
