set(CHAPTER10_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/spatial_blur_filtering.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/spatial_sharp_filtering.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/spatial_median_filtering.cpp
    PARENT_SCOPE
)

set(CHAPTER10_HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/spatial_blur_filtering.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/spatial_sharp_filtering.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/spatial_median_filtering.hpp
    PARENT_SCOPE
)
