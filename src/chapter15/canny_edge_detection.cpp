#include "canny_edge_detection.hpp"

using namespace cv;
using namespace std;

int chapter15::CannyEdgeDetection() {
    Mat image, canny;
    image = imread("./resources/lena.jpg", IMREAD_GRAYSCALE);

    Canny(image, canny, 190, 200, 3);

    imshow("image", image);
    imshow("canny", canny);
    waitKey(0);
    return 0;
}
