#ifdef CHAPTER7
#include "chapter7/deepcopy_vs_shallowcopy.hpp"
#include "chapter7/pixel_access.hpp"

int Chapter7() {
    chapter7::DeepCopyVsShallowCopy();
    chapter7::PixelAccessByAt();
    chapter7::PixelAccessByPointer();
    chapter7::PixelAccessByIterator();
    return 1;
}

#endif
