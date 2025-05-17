#include "spatial_blur_filtering.hpp"

// addWeighted?


int chapter10::SpatialAverageFiltering() {
    Mat image, average_image, gaussian_image;
    image = imread("./resources/lena.jpg");

    blur(image, average_image, Size(5,5));

    imshow("original image", image);
    imshow("average image", average_image);
    waitKey(0);
    return 1;
}

int chapter10::SpatialGaussianFiltering() {
    Mat image, average_image, gaussian_image;
    image = imread("./resources/lena.jpg");

    //1.5각각은 x, y의 표준 편차를 말한다.
    GaussianBlur(image, gaussian_image, Size(5,5), 1.5, 1.5);

    imshow("original image", image);
    imshow("gaussian image", gaussian_image);
    waitKey(0);
    return 1;
}
