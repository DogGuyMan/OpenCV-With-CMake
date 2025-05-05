#include "contour_counting.hpp"
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


Mat static DrawHistogram(Mat &srcImage) {
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

Mat static PerformClustering(Mat &srcImage) {
    Mat samples = srcImage.reshape(1, srcImage.total());
    samples.convertTo(samples, CV_32F);
    Mat labels, centers;
    kmeans(samples, 2, labels, TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0), 3, KMEANS_PP_CENTERS, centers);
    Mat clusterd(srcImage.size(), CV_8UC1);
    for (int i = 0; i < labels.rows; i++) {
        int cluster_idx = labels.at<int>(i);
        clusterd.at<uchar>(i / srcImage.cols, i % srcImage.cols) = (uchar)centers.at<float>(cluster_idx, 0);
    }
    return clusterd;
}

int chapter13::ContourCounting() {
    Mat coins_img = imread("./data/coins.png", 0);
    Mat clusterd = PerformClustering(coins_img);
    Mat result;

    Mat original_hist = DrawHistogram(coins_img);
    Mat clusterd_hist = DrawHistogram(clusterd);

    threshold(clusterd, clusterd, 100, 255, THRESH_BINARY);
    threshold(coins_img, result, 100, 255, THRESH_BINARY);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    resize(coins_img, coins_img, Size(0,0), 2, 2);
    resize(clusterd, clusterd, Size(0,0), 2, 2);

    findContours(result, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    cvtColor(result, result, COLOR_GRAY2BGR);
    resize(result, result, Size(0,0), 2, 2);
    putText(result, format("contour count: %d", contours.size()), Point(50,80),
        FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 4);

    imshow("coins image", coins_img);
    imshow("clusterd image", clusterd);
    imshow("result", result);
    imshow("coin hist", original_hist);
    imshow("clusterd hist", clusterd_hist);
    waitKey(0);
    return 1;
}
