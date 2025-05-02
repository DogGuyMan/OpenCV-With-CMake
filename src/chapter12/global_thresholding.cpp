#include "global_thresholding.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

#define DEBUG 1

using namespace std;
using namespace cv;

pair<int,int> static CalcSegmentsMean(const Mat& image, const int tVal, const int gapVal) {
    auto start = image.begin<uchar>();
    auto end = image.end<uchar>();
    int black_cnt = 0, black_sum = 0;
    int white_cnt = 0, white_sum = 0;
    for(auto it = start; it != end; ++it) {
        uchar pixel = (*it);
        if(pixel >= tVal)   {white_cnt++; white_sum += pixel;}
        else                {black_cnt++; black_sum += pixel;}
    }
    return {(black_sum / black_cnt), (white_sum / white_cnt)};
}

int static GetGlobalThreshold(const Mat& image, const int init_thresh, const int gapVal) {
    int black_cnt = 0, black_sum = 0;
    int white_cnt = 0, white_sum = 0;
    int global_thresh = init_thresh;
    pair<int, int> means = {-1, -1};
    while(1) {
        means = CalcSegmentsMean(image, global_thresh, gapVal);
        int white_mean = means.second;
        int black_mean = means.first;
        int nxt_tVal = (white_mean + black_mean) / 2.0f;

#if DEBUG
        cout    << "white_mean" << white_mean << '\n'
                << "black_mean" << black_mean << '\n'
                << "nxt_tVal" << nxt_tVal << endl;
#endif
        if(abs(global_thresh - nxt_tVal) < gapVal) {
#if DEBUG
            cout << "calc finished" << endl;
#endif
            break;
        }
        else {
            global_thresh = nxt_tVal;
            black_cnt = 0, black_sum = 0;
            white_cnt = 0, white_sum = 0;
#if DEBUG
            cout << "perform again..." << endl;
#endif
        }
    }

    return global_thresh;
}

int chapter12::BasicMethod() {
    Mat image = imread("./data/lena.jpg", IMREAD_GRAYSCALE);
    Mat threshed_image;
    int thresh_T = 200;
    int mean_gap = 10;

    int global_thresh = GetGlobalThreshold(image,thresh_T,mean_gap);
    threshold(image, threshed_image, global_thresh, 255, THRESH_BINARY);

    imshow("original image", image);
    imshow("threshed image", threshed_image);

    waitKey(0);
    return 1;
}

int chapter12::OtusMethod() {
    Mat image = imread("./data/lena.jpg", IMREAD_GRAYSCALE);
    Mat threshed_image;

    // 오.. 비트셋으로 스레숄드 옵션을 정하는구나.
    threshold(image, threshed_image, 0, 255, THRESH_BINARY | THRESH_OTSU);

    imshow("original image", image);
    imshow("threshed image", threshed_image);

    waitKey(0);
    return 1;
}
