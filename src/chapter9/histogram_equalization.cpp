#include "histogram_equalization.hpp"
#include <opencv2/core.hpp>

// cvRound? 반올림의 뜻인듯.
Mat chapter9::DrawHistogram(Mat srcImage) {
    Mat hist, histImage;
    int hist_w = 512, hist_h = 400, histSize = 256;
    int bin_w = cvRound((double)hist_w / histSize);
    float range[] = { 0, 256 };
    const float* histRange = { range };

    calcHist(&srcImage, 1, 0, Mat(), hist, 1, &histSize, &histRange);

    histImage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255,255,255));

    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for(int i = 0; i < histSize; i++) {
        rectangle(histImage,
            Point(bin_w*i, hist_h), Point(bin_w*i, hist_h - cvRound(hist.at<float>(i))),
            Scalar(0,0,0), 2, 8, 0);
    }
    return histImage;
}

int chapter9::HistogramEqualization() {
    Mat image, hist_equalized_image;
    Mat hist_graph, hist_equalized_graph;

    image = imread("./data/lena.jpg", 0);

    equalizeHist(image, hist_equalized_image);

    hist_graph = DrawHistogram(image);
    hist_equalized_graph = DrawHistogram(hist_equalized_image);

    imshow("original image", image);
    imshow("histogram Equalized image", hist_equalized_image);
    imshow("original graph", hist_graph);
    imshow("histogram Equalized graph", hist_equalized_graph);
    waitKey(0);
    return 0;
}
