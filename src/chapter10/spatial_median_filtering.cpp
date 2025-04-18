#include "spatial_median_filtering.hpp"

int chapter10::SpatialMedianFiltering() {
    Mat image = imread("./data/Noise_salt_and_pepper.png");
    imshow("Salt And Pepper", image);
    Mat mf1, mf2;

    medianBlur(image, mf1, 3);
    imshow("MedianFiltered1", mf1);

    medianBlur(image, mf2, 9);
    imshow("MedianFiltered2", mf2);

    waitKey(0);
    return 1;
}
