#include "my_demo_opencv.hpp"
#include "chapter4/baisic_data_structure_in_openCV.hpp"
#include "chapter4/read_an_image_in_openCV.hpp"
#include "chapter4/play_with_video_capture.hpp"
#include "chapter4/read_a_video_from_a_file.hpp"
#include "chapter4/read_a_video_from_a_webcam.hpp"
#include "chapter5/color_space_conversion_cvt.hpp"
#include "chapter5/split_and_merge.hpp"
#include "chapter5/roi_image_mask.hpp"
#include "chapter5/addition_and_subtraction.hpp"
#include "chapter5/threshold_operations.hpp"
#include "chapter6/drawing_rectangle.hpp"
#include "chapter6/drawing_line.hpp"
#include "chapter6/drawing_circle.hpp"
#include "chapter6/drawing_polygon.hpp"
#include "chapter6/drawing_text.hpp"
#include "chapter7/deepcopy_vs_shallowcopy.hpp"
#include "chapter7/pixel_access.hpp"
#include "chapter8/gamma_transformation.hpp"
#include "chapter8/log_transformation.hpp"
#include "chapter8/negative_transformation.hpp"
#include "chapter8/piecewise_transformation.hpp"
#include "chapter9/histogram_equalization.hpp"
#include "chapter10/spatial_blur_filtering.hpp"
#include "chapter10/spatial_median_filtering.hpp"

int Chapter4() {
    chapter4::ReadAnImageInOpenCV();
    chapter4::PlayWithVideoCapture();
    chapter4::ReadAVideoFromAFile();
    chapter4::ReadAVideoFromAWebcam();
    return 1;
}

int Chapter5() {
    chapter5::ColorSpaceConversionCvt();
    chapter5::SplitAndMerge();
    chapter5::RectROIImageMask(); chapter5::PolygonROIImageMask();
    chapter5::MatOriginal();
    chapter5::MatAdd();
    chapter5::MatScaleadd();
    chapter5::MatAbsdiff();
    chapter5::MatSubtract();
    chapter5::Threshold();
    chapter5::AdaptiveThreshold();
    chapter5::InRange();
    return 1;
}

int Chapter6() {
    chapter6::DrawingRectangleWithPoints();
    chapter6::DrawingRectangleWithRect();
    chapter6::FillRectangleWithRect();
    chapter6::DrawingLine();
    chapter6::DrawingCircle();
    chapter6::FillCircle();
    chapter6::DrawingPolygon();
    chapter6::DrawingMultiplePoly();
    chapter6::DrawingPolyLine();
    chapter6::DrawingText();
    chapter6::DrawingDateTime();
    return 1;
}

int Chapter7() {
    chapter7::DeepCopyVsShallowCopy();
    chapter7::PixelAccessByAt();
    chapter7::PixelAccessByPointer();
    chapter7::PixelAccessByIterator();
    return 1;
}

int Chapter8() {
    chapter8::NegativeTransformation();
    chapter8::LogTransformation();
    chapter8::GammaTransformation();
    chapter8::PiecewiseTransformation();
    return 1;
}

int Chapter9() {
    chapter9::HistogramEqualization();
    return 1;
}

int Chapter10() {
    // chapter10::SpatialAverageFiltering();
    // chapter10::SpatialBlurFiltering();
    chapter10::SpatialMedianFiltering();
    // chapter10::SpatialUnsharpMasking();
    return 1;
}

int main()
{
    // Chapter4();
    // Chapter5();
    // Chapter6();
    // Chapter7();
    // Chapter8();
    // Chapter9();
    Chapter10();
    return 1;
}
