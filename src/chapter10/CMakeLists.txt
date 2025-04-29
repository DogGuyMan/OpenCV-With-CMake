set(CHAPTER10_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/spatial_blur_filtering.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/spatial_sharp_filtering.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/spatial_median_filtering.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/spatial_emboss_filtering.cpp

)

set(CHAPTER10_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/chapter10_headers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/spatial_blur_filtering.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/spatial_sharp_filtering.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/spatial_median_filtering.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/spatial_emboss_filtering.hpp

)

set(PROJECT_SOURCES ${PROJECT_SOURCES} ${CHAPTER10_SOURCES} PARENT_SCOPE)
set(PROJECT_HEADERS ${PROJECT_HEADERS} ${CHAPTER10_SOURCES} PARENT_SCOPE)
set(PROJECT_CHAPTER_DEFINES ${PROJECT_CHAPTER_DEFINES} CHAPTER10 PARENT_SCOPE)
