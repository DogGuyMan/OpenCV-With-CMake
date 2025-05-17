#include "pseudo_coloring.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int chapter11::PseudoColoring() {
    Mat sad_dog_image = imread("./resources/sad_dog.jpg");
    Mat xray_image = imread("./resources/x_ray.png");
    Mat colored_sad_dog_image, colored_xray_image;
    Mat invert_colored_sad_dog_image, invert_colored_xray_image;
    int target_height = 400;

    double dog_aspect_ratio = (double)sad_dog_image.cols/ sad_dog_image.rows;
    int target_dog_width = (int)(dog_aspect_ratio * target_height);

    double xray_aspect_ratio = (double)xray_image.cols/ xray_image.rows;
    int target_xray_width = (int)(xray_aspect_ratio * target_height);

    resize(sad_dog_image, sad_dog_image, Size(target_dog_width, target_height));
    resize(xray_image, xray_image, Size(target_xray_width, target_height));

    applyColorMap(sad_dog_image, colored_sad_dog_image, COLORMAP_JET);
    applyColorMap(xray_image, colored_xray_image, COLORMAP_JET);

    // Look Up Table 반전
    Mat color_map((UCHAR_MAX+1), 1, CV_8UC3);
    for(int i = 0; i <= UCHAR_MAX; ++i) {
        color_map.row(i).setTo(i);
    }
    applyColorMap(color_map, color_map, COLORMAP_JET);

    Mat inverted_colormap((UCHAR_MAX+1), 1, CV_8UC3);

    for(int i = 0; i <= UCHAR_MAX; ++i) {
        Vec3b origin_color = color_map.at<Vec3b>(0, i);
        inverted_colormap.at<Vec3b>(UCHAR_MAX-i) = origin_color;
    }

    LUT(sad_dog_image, inverted_colormap, invert_colored_sad_dog_image);
    LUT(xray_image, inverted_colormap, invert_colored_xray_image);

    imshow("Original Dog Image", sad_dog_image);
    imshow("Colored Dog Image", colored_sad_dog_image);
    imshow("Invert Colored Dog Image", invert_colored_sad_dog_image);
    imshow("Original Xray Image", xray_image);
    imshow("Colored Xray Image", colored_xray_image);
    imshow("Invert Colored Xray Image", invert_colored_xray_image);

    waitKey(0);
    return 1;
}
