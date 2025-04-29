#ifdef CHAPTER11

#include "chapter11/usage_of_hsl.hpp"
#include "chapter11/pseudo_coloring.hpp"
#include "chapter11/color_balancing.hpp"
#include "chapter11/color_histogram.hpp"

int Chapter11() {
    chapter11::UsageOfHSL();
    chapter11::PseudoColoring();
    chapter11::ColorBalancing();
    chapter11::HistogramEqualizeYCrCbAndHSV();
    chapter11::HistogramBackProject();
    return 1;
}

#endif
