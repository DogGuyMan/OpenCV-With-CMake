#include "color_histogram.hpp"

using namespace std;
using namespace cv;

int chapter11::HistogramEqualizeYCrCbAndHSV() {
    Mat image = imread("./resources/lena.jpg");
    Mat ycrcb_image, hsv_image;
    Mat equalized_ycrcb_image, equalized_hsv_image;
    cvtColor(image, ycrcb_image, COLOR_BGR2YCrCb);
    cvtColor(image, hsv_image, COLOR_BGR2HSV);
    vector<Mat> splited_ycrcb;
    vector<Mat> splited_hsv;

    split(ycrcb_image, splited_ycrcb);
    split(hsv_image, splited_hsv);

    equalizeHist(splited_ycrcb[0], splited_ycrcb[0]);
    equalizeHist(splited_hsv[2], splited_hsv[2]);

    merge(splited_ycrcb, equalized_ycrcb_image);
    merge(splited_hsv, equalized_hsv_image);
    cvtColor(equalized_ycrcb_image, equalized_ycrcb_image, COLOR_YCrCb2BGR);
    cvtColor(equalized_hsv_image, equalized_hsv_image, COLOR_HSV2BGR);

    imshow("origin image", image);
    imshow("equalized ycrcb image", equalized_ycrcb_image);
    imshow("equalized hsv image", equalized_hsv_image);

    waitKey(0);
    return 1;
}

int chapter11::HistogramBackProject(){
    Mat image = imread("./resources/dice.png");
    Mat ycrcb_image;
    cvtColor(image, ycrcb_image, COLOR_BGR2YCrCb);
    /* DrawRect */
    Rect rect(0,0, 200, 800);
    /* Rect로 Mask 생성 */
    Mat mask_image = Mat::zeros(image.size(), CV_8UC1);
    rectangle(mask_image, rect, Scalar(255), FILLED);

    /* 어디가 마스크인지 디버그*/
    rectangle(image, rect, Scalar(0,0,255), 4, LINE_AA);

    /* calcHist에 마스크를 넣어주자. */
    Mat hist;

    vector<int> channels = {1, 2};
    vector<int> histSize = {128, 128};
    vector<float> ranges = {0, 256, 0, 256};

    calcHist(vector<Mat>{ycrcb_image}, channels, mask_image, hist, histSize, ranges);

    /*
    vector<Mat>{ycrcb_image}는 calcHist에 적합하며,
    멀티채널 이미지를 직접 처리할 수 있어 추가적인 채널 분리가 필요 없습니다.
    */
    Mat backProj;
    calcBackProject(vector<Mat>{ycrcb_image}, channels, hist, backProj, ranges, 1);
    medianBlur(backProj, backProj, 13);

    threshold(backProj, backProj, 1, 255, THRESH_BINARY);

    imshow("original image", image);
    imshow("backProjected image", backProj);

    waitKey(0);

    return 1;
}
