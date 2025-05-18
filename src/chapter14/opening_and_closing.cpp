#include "opening_and_closing.hpp"

using namespace std;
using namespace cv;

int chapter14::OpeningAndClosing() {
    Mat image, opening, closing;
    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(16, 16));

    image = imread("./resources/coins.png", 0);
    resize(image, image, Size(0,0), 1.5, 1.5);
    threshold(image, image, 0, 255, THRESH_BINARY | THRESH_OTSU);

    morphologyEx(image, opening, MORPH_OPEN, kernel);
    morphologyEx(image, closing, MORPH_CLOSE, kernel);

    imshow("image", image);
    imshow("opening", opening);
    imshow("closing", closing);
    waitKey(0);
    return 1;
}
