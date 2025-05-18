#include "negative_transformation.hpp"

using namespace std;
using namespace cv;

const int INTENSITY_MAX = UCHAR_MAX;
void PixelToNeg(uchar& r) { r = INTENSITY_MAX - r; }
int chapter8::NegativeTransformation() {
    Mat image = imread("./resources/lena.jpg", 0);
    Mat neg_image = image.clone();
    for(MatIterator_<uchar> it = neg_image.begin<uchar>(); it != neg_image.end<uchar>(); ++it) {
        PixelToNeg((*it));
    }

    imshow("original image", image);
    imshow("negative image", neg_image);

    waitKey(0);

    return 1;
}
