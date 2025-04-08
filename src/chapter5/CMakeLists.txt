set(CHAPTER5_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/color_space_conversion_cvt.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/split_and_merge.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/roi_image_mask.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/addition_and_subtraction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/threshold_operations.cpp
    PARENT_SCOPE
)

set(CHAPTER5_HEADERS
    ${PROJECT_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/color_space_conversion_cvt.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/split_and_merge.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/roi_image_mask.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/addition_and_subtraction.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/threshold_operations.hpp
    PARENT_SCOPE
)
