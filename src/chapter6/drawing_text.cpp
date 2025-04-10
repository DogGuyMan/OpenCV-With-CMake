#include "drawing_text.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int chapter6::DrawingText() {
    Mat image = Mat::zeros(400, 600, CV_8UC3);

    int w = image.cols, h = image.rows;
    putText(image, format("width : %d, height : %d", w, h), Point(50, 80),
        FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200,200), 4
    );

    imshow("text on image", image);
    waitKey(0);
    return 0;
}

int chapter6::DrawingDateTime() {
    return 0;
}
