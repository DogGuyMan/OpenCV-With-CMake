#include "color_balancing.hpp"

enum RGBKey {
    R = 2, G = 1, B = 0
};

int chapter11::CalculateChannelAverage(std::vector<Mat> &ch, cv::Vec3i &bgrAverage) {
    uchar *channelPtr[3];
    int rows = ch[0].rows;
    int cols = ch[0].cols;
    int total = ch[0].total();
    int sum[3] = {0,0,0};

    for(int i = 0; i < rows; ++i) {
        channelPtr[RGBKey::B] = ch[RGBKey::B].ptr<uchar>(i);
        channelPtr[RGBKey::G] = ch[RGBKey::G].ptr<uchar>(i);
        channelPtr[RGBKey::R] = ch[RGBKey::R].ptr<uchar>(i);
        for(int j = 0; j < cols; j++) {
            sum[RGBKey::B] += channelPtr[RGBKey::B][j];
            sum[RGBKey::G] += channelPtr[RGBKey::G][j];
            sum[RGBKey::R] += channelPtr[RGBKey::R][j];
        }
    }
    bgrAverage[RGBKey::B] = sum[RGBKey::B] / total;
    bgrAverage[RGBKey::G] = sum[RGBKey::G] / total;
    bgrAverage[RGBKey::R] = sum[RGBKey::R] / total;
    return 1;
}

int chapter11::GrayWorldAssumsptionBalancing(vector<Mat> &ch, const::Vec3i &bgrAverage) {
    uchar *channelPtr[3];
    int rows = ch[0].rows;
    int cols = ch[0].cols;
    int total = ch[0].total();
    int temp[3] = {0,0,0};
    for(int i = 0; i < rows; ++i) {
        channelPtr[RGBKey::B] = ch[RGBKey::B].ptr<uchar>(i);
        channelPtr[RGBKey::G] = ch[RGBKey::G].ptr<uchar>(i);
        channelPtr[RGBKey::R] = ch[RGBKey::R].ptr<uchar>(i);
        for(int j = 0; j < cols; j++) {
            temp[RGBKey::B] = (128 * channelPtr[RGBKey::B][j]) / bgrAverage[RGBKey::B];
            channelPtr[RGBKey::B][j] = (temp[RGBKey::B] > UCHAR_MAX) ? UCHAR_MAX : temp[RGBKey::B];

            temp[RGBKey::G] = (128 * channelPtr[RGBKey::G][j]) / bgrAverage[RGBKey::G];
            channelPtr[RGBKey::G][j] = (temp[RGBKey::G] > UCHAR_MAX) ? UCHAR_MAX : temp[RGBKey::G];

            temp[RGBKey::R] = (128 * channelPtr[RGBKey::R][j]) / bgrAverage[RGBKey::R];
            channelPtr[RGBKey::R][j] = (temp[RGBKey::R] > UCHAR_MAX) ? UCHAR_MAX : temp[RGBKey::R];
        }
    }
    return 1;
}

int chapter11::ColorBalancing() {
    Mat image = imread("./data/lena.jpg");
    Mat balanced_image;

    vector<Mat> ch(3);
    split(image, ch);
    Vec3i bgrAverage = {0,0,0};

    if(!CalculateChannelAverage(ch, bgrAverage)) {
    }

    if(!GrayWorldAssumsptionBalancing(ch, bgrAverage)) {
    }

    merge(ch, balanced_image);

    imshow("Original Image", image);
    imshow("Balanced Image", balanced_image);
    waitKey(0);
    return 1;
}
