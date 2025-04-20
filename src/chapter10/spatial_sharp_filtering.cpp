#include "spatial_sharp_filtering.hpp"

int chapter10::SpatialSharpFiltering() {
    Mat image, laplacian, abs_laplacian, sharpening;
    image = imread("./data/moon.jpeg", 0);

    GaussianBlur(image, image, Size(3,3), 0, 0, BORDER_DEFAULT);


    // 2차 미분을 수행하기 위해 라플라시안 함수를 활용할 수 있다.
    // Laplacian of an image ?
    /* Laplacian(
        image : src,
        laplacian : dst,
        CV_16S desire depth of dst,
        1 : aperture size use to compute second-derivative
        1 : optional scale factor for the compute laplacian values
        0 : optional delta value tha is added to the result
    ) */
    Laplacian(image, laplacian, CV_16S, 1,1,0);

    // 8비드 영상으로 바꿔주기
    convertScaleAbs(laplacian, abs_laplacian);

    // 언샤프 한 결과와 원본 이미지를 합한다면, 언샤프닝이 된다.
    sharpening = abs_laplacian + image;

    imshow("original image", image);
    imshow("Laplacian", laplacian);
    imshow("abs_Laplacian", abs_laplacian);
    imshow("sharpening", sharpening);
    waitKey(0);
    return 1;
}

// 언샤프 마스킹을 얻어서 언샤프닝이 가능하다.
// 그렇게 하기위해서는 가우시안 블러 취하고 난 뒤에, 연샤프 마스크를 역으로 계산할 수 있다.
int chapter10::SpatialUnsharpMasking() {
    Mat input = imread("./data/lena.jpg");
    Mat gray, blur, sharp;
    cvtColor(input, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, blur, Size(5,5), 3);
    addWeighted(gray, 1.5, blur, -0.5, 0, sharp);

    imshow("gray image", gray);
    imshow("sharp image", sharp);
    waitKey(0);
    return 1;
}
