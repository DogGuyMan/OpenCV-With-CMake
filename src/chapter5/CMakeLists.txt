set(CHAPTER5)

set(CHAPTER5_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/color_space_conversion_cvt.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/split_and_merge.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/roi_image_mask.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/addition_and_subtraction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/threshold_operations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/extra_matrix_operation.cpp

)

set(CHAPTER5_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/chapter5_headers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/color_space_conversion_cvt.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/split_and_merge.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/roi_image_mask.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/addition_and_subtraction.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/threshold_operations.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/extra_matrix_operation.hpp

)

set(PROJECT_SOURCES ${PROJECT_SOURCES} ${CHAPTER5_SOURCES} PARENT_SCOPE)
set(PROJECT_HEADERS ${PROJECT_HEADERS} ${CHAPTER5_SOURCES} PARENT_SCOPE)
set(PROJECT_CHAPTER_DEFINES ${PROJECT_CHAPTER_DEFINES} CHAPTER5 PARENT_SCOPE)
