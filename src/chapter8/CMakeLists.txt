set(CHAPTER8)

set(CHAPTER8_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/negative_transformation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/log_transformation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gamma_transformation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/piecewise_transformation.cpp

)

set(CHAPTER8_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/chapter8_headers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/negative_transformation.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/log_transformation.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gamma_transformation.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/piecewise_transformation.hpp

)

set(PROJECT_SOURCES ${PROJECT_SOURCES} ${CHAPTER8_SOURCES} PARENT_SCOPE)
set(PROJECT_HEADERS ${PROJECT_HEADERS} ${CHAPTER8_SOURCES} PARENT_SCOPE)
set(PROJECT_CHAPTER_DEFINES ${PROJECT_CHAPTER_DEFINES} CHAPTER8 PARENT_SCOPE)
