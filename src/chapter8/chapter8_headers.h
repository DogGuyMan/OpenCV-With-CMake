#ifdef CHAPTER8
#include "chapter8/gamma_transformation.hpp"
#include "chapter8/log_transformation.hpp"
#include "chapter8/negative_transformation.hpp"
#include "chapter8/piecewise_transformation.hpp"

int Chapter8() {
    chapter8::NegativeTransformation();
    chapter8::LogTransformation();
    chapter8::GammaTransformation();
    chapter8::PiecewiseTransformation();
    return 1;
}

#endif
