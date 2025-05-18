#include "roi_image_mask.hpp"

using namespace cv;
using namespace std;

int chapter5::RectROIImageMask() {
    Mat image, rect_roi;
    Rect rect(100, 30, 250, 300);

    image = imread("./resources/lena.jpg");
    rect_roi = image(rect);

    imshow("rect ROI image", rect_roi);
    waitKey(0);
    return 1;
}

int chapter5::PolygonROIImageMask() {
    Mat image, poly_roi, poly_mask;
    image = imread("./resources/lena.jpg");
    Point polys[1][4] = {
        Point(255, 100), Point(286, 100), Point(316, 300), Point(196, 300)
    };

    const Point* ppt[1] = {polys[0]}; // InputArrayOfArray
    int npt[] = {4}; // npts
    poly_mask = Mat::zeros(image.size(), image.type());

    // CV_EXPORTS void fillPoly(InputOutputArray img, const Point** pts,
    //                          const int* npts, int ncontours,
    //                          const Scalar& color, int lineType = LINE_8, int shift = 0,
    //                          Point offset = Point() );
    fillPoly(poly_mask, ppt, npt, 1, Scalar(255,255,255), 8);

    // inline void GpuMat::copyTo(OutputArray dst, InputArray mask) const
    // {
    //     copyTo(dst, mask, Stream::Null());
    // }
    image.copyTo(poly_roi, poly_mask);
    imshow("poly ROI image", poly_roi);

    waitKey(0);
    return 1;
}
