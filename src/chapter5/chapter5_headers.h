#ifdef CHAPTER5
#include "chapter5/color_space_conversion_cvt.hpp"
#include "chapter5/split_and_merge.hpp"
#include "chapter5/roi_image_mask.hpp"
#include "chapter5/addition_and_subtraction.hpp"
#include "chapter5/threshold_operations.hpp"
#include "chapter5/extra_matrix_operation.hpp"

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
    chapter5::MatrixConsturct();
    chapter5::MatrixBitwise();
    chapter5::MatrixInverted();
    return 1;
}

#endif
