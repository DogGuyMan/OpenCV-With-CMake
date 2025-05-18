#include "sobel_edge_detection.hpp"

using namespace cv;
using namespace std;

int chapter15::SobelEdgeDetection() {
    Mat image, g_blurred, b_blurred;
    Mat g_grad_x, g_grad_y, b_grad_x, b_grad_y;
    Mat abs_g_grad_x, abs_g_grad_y, abs_b_grad_x, abs_b_grad_y;

    Mat g_edge_image, b_edge_image;

    image = imread("./resources/lena.jpg", IMREAD_GRAYSCALE);
    resize(image, image, Size(0, 0), 0.75, 0.75);

    // 노이즈 제거.
    // 커널 크기와 표준편차가 클수록 이미지가 더 많이 흐려집니다.
    GaussianBlur(   image,          // src: 입력 이미지(Mat 타입). 여기서는 image.
                    g_blurred,      // dst: 결과가 저장될 출력 이미지(Mat 타입). 여기서는 blurred.
                    Size(5, 5),     // ksize: 가우시안 커널의 크기. (가로, 세로)로 지정. 여기서는 Size(5, 5)로 5x5 커널 사용.
                    5,              // sigmaX: X축(가로) 방향의 가우시안 커널 표준편차. 여기서는 5.
                    5,              // sigmaY: Y축(세로) 방향의 가우시안 커널 표준편차. 여기서는 5. (0이면 sigmaX와 동일하게 적용)
                    BORDER_DEFAULT  // borderType: 경계 픽셀 처리 방식. 기본값은 BORDER_DEFAULT.
                );

    // 노이즈 제거.
    // Bilateral Filter는 이미지의 노이즈를 제거 하면서도, 에지(경계선)는 잘 보존하는 고급 필터입니다.
    // 셀의 공간적 거리와 색상 차이(명암 차이) 모두를 고려하여 필터링을 수행합니다.
    bilateralFilter(    image,      // src: 입력 이미지 (Mat)
                        b_blurred,  // dst: 결과 이미지 (Mat)
                        5,          // d: 필터링에 사용할 이웃 픽셀의 지름(보통 5~15 정도 사용)
                        50,         // sigmaColor: 색상 차이에 대한 표준편차(값이 클수록 색상 차이가 커도 영향을 받음)
                        50          // sigmaSpace: 공간적 거리(좌표) 표준편차(값이 클수록 멀리 있는 픽셀도 영향을 줌)
                    );
    /*
    dx : 1 dy : 0
    -1 0 1
    -2 0 2
    -1 0 1
    */
    Sobel(g_blurred, g_grad_x, CV_16S, 1, 0 ,3);
    Sobel(b_blurred, b_grad_x, CV_16S, 1, 0 ,3);
    /*
    dx : 0 dy : 1
    -1  -2  -1
    0   0   0
    1   2   1
    */
    Sobel(g_blurred, g_grad_y, CV_16S, 0, 1 ,3);
    Sobel(b_blurred, b_grad_y, CV_16S, 0, 1 ,3);

    // convertScaleAbs는 sacle 곱셈후 절대값 취하고 saturate진행으로 0~255 범위로 변환.
    // 이 효과는 Contrast 높이기 효과가 있음.
    convertScaleAbs(g_grad_x, abs_g_grad_x); convertScaleAbs(g_grad_y, abs_g_grad_y);
    convertScaleAbs(b_grad_x, abs_b_grad_x); convertScaleAbs(b_grad_y, abs_b_grad_y);

    addWeighted(abs_g_grad_x, 0.5, abs_g_grad_y, 0.5, 0, g_edge_image);
    addWeighted(abs_b_grad_x, 0.5, abs_b_grad_y, 0.5, 0, b_edge_image);

    imshow("g_grad_x image", abs_g_grad_x); imshow("g_grad_y image", abs_g_grad_y);
    imshow("b_grad_x image", abs_b_grad_x); imshow("b_grad_y image", abs_b_grad_y);
    imshow("g_edge_image", g_edge_image);
    imshow("b_edge_image", b_edge_image);

    waitKey(0);
    return 0;
}
