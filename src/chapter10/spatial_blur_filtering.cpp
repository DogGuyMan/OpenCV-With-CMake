#include "spatial_blur_filtering.hpp"

// BORDER_DEFAULT
// Laplacian : 라플라시안
int chapter10::SpatialBlurFiltering() {
    Mat image, laplacian, abs_laplacian, sharpening;
    image = imread("./data/moon.jpeg", 0);

    GaussianBlur(image, image, Size(3,3), 0, 0, BORDER_DEFAULT);
    // Laplacian of an image ?
    // image : src,
    // laplacian : dst,
    // CV_16S desire depth of dst,
    // 1 : aperture size use to compute second-derivative
    // 1 : optional scale factor for the compute laplacian values
    // 0 : optional delta value tha is added to the result

    Laplacian(image, laplacian, CV_16S, 1,1,0);
    convertScaleAbs(laplacian, abs_laplacian);
    sharpening = abs_laplacian + image;

    imshow("original image", image);
    imshow("Laplacian", laplacian);
    imshow("abs_Laplacian", abs_laplacian);
    imshow("sharpening", sharpening);
    waitKey(0);
    return 1;
}

// addWeighted?
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

int chapter10::SpatialAverageFiltering() {
    Mat image, average_image, gaussian_image;
    image = imread("./data/lena.jpg");

    blur(image, average_image, Size(5,5));
    GaussianBlur(image, gaussian_image, Size(5,5), 1.5);

    imshow("original image", image);
    imshow("average image", average_image);
    imshow("gaussian image", gaussian_image);
    waitKey(0);
    return 1;

}
