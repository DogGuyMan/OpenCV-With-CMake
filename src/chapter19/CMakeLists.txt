set(CHAPTER19_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/tracking_mean_and_cam_shift.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/optical_flow.cpp
)
set(CHAPTER19_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/chapter19_headers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/tracking_mean_and_cam_shift.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/optical_flow.hpp
)

set(PROJECT_SOURCES ${PROJECT_SOURCES} ${CHAPTER19_SOURCES} PARENT_SCOPE)
set(PROJECT_HEADERS ${PROJECT_HEADERS} ${CHAPTER19_HEADERS} PARENT_SCOPE)
set(PROJECT_CHAPTER_DEFINES ${PROJECT_CHAPTER_DEFINES} CHAPTER19 PARENT_SCOPE)
