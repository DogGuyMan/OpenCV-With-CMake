#include "drawing_histogram.hpp"
#include <opencv2/core.hpp>


Mat chapter9::DrawHistogram(Mat srcImage) {
    Mat hist, histImage;

    // 히스토그램을 그리기 위한 캔버스 제작하기
    int hist_w = 512, hist_h = 400;

    // histSize는 bin의 사이즈, Bin의 개수 정해주고,
    // Bin의 막대 그래프의 굵기를 캔버스 가로 크기 대비하여 정해준다.
    // cvRound? 반올림의 뜻인듯.
    int histSize = 256, bin_w = cvRound((double)hist_w / histSize);

    // 이미지 입력값의 범위를 정해줌
    float range[] = { 0, 256 };
    const float* histRange = { range };

    /* calcHist (
            &srcImage : 입력 이미지
            1 :  입력영상의 개수 : 여러 영상에 대해서도 그릴 수 있다.
            0 :  영상의 채널의 각 인덱스.
            Mat() : 특정한 부분에 대해 히스토그램을 분석하기 위해 마스크 설정
            hist : 히스토그램이 그려지게 될 캔버스
            1 : 히스토그램의 차원 1차원 2차원
            &histSize :  히스토그램의 크기 Bin의 사이즈
            &histRange : 히스토그램을 그리기 위해 사용될 입력값의 범위
    )*/
    calcHist(&srcImage, 1, 0, Mat(), hist, 1, &histSize, &histRange);

    histImage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255,255,255));

    // 히스토그램의 최대 높이를 활용해 Normalize하게 된다.
    // 히스토그램 막대기가 뚫고 나가지 않게끔하려고,
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
    Mat hist_graph, hist_normed_graph;

    image = imread("./data/lena.jpg", 0);

    equalizeHist(image, hist_equalized_image);

    hist_graph = DrawHistogram(image);
    hist_normed_graph = DrawHistogram(hist_equalized_image);

    imshow("original image", image);
    imshow("histogram Equalized image", hist_equalized_image);
    imshow("original graph", hist_graph);
    imshow("histogram Equalized graph", hist_normed_graph);
    waitKey(0);
    return 0;
}


int chapter9::HistogramNormalization() {
    Mat image, hist_normed_image;
    Mat hist_graph, hist_normed_graph;

    image = imread("./data/lena.jpg", 0);
    normalize(image, hist_normed_image, 0, 255, NORM_MINMAX);

    hist_graph = DrawHistogram(image);
    hist_normed_graph = DrawHistogram(hist_normed_image);

    imshow("original image", image);
    imshow("histogram Normalized image", hist_normed_image);
    imshow("original graph", hist_graph);
    imshow("histogram Normalized graph", hist_normed_graph);
    waitKey(0);
    return 0;
}
