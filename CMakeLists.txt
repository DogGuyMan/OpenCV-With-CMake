cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME opencv-project)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)
find_package(spdlog REQUIRED)

set(DEP_LIBS ${DEP_LIBS} ${OpenCV_LIBS})
set(DEP_LIBS ${DEP_LIBS} spdlog::spdlog)

# set(DEP_SOURCE_DIR ${DEP_SOURCE_DIR} "${spdlog_SOURCE_DIR}/include") # spdlog 헤더 (필요에 따라 경로 수정)
# set(DEP_SOURCE_DIR ${DEP_SOURCE_DIR} "${OpenCV_SOURCE_DIR}/include") # opencv_world 옵션 활성화: 모든 모듈을 하나의 통합 라이브러리로 빌드

message(STATUS "CMAKE_TOOLCHAIN_FILE ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "OpenCV_LIBS ${CMAKE_TOOLCHAIN_FILE}")

# ─── 실행 파일 생성 및 설정 ──────────────────────────
# Executable에 사용하는 Source들과 Header 모음
set(PROJECT_SOURCES
    # src/buffer.cpp src/common.cpp src/context.cpp src/image.cpp src/program.cpp
    # src/shader.cpp src/vertex_layout.cpp src/texture.cpp
)

set(PROJECT_HEADERS
    # src/buffer.h src/common.h src/context.h src/image.h src/program.h
    # src/shader.h src/vertex_layout.h src/texture.h
)

add_executable(${PROJECT_NAME} app/main.cpp)

# 의존성 헤더 경로 추가
# OpenCV의 경우, 헤더 구조에 따라 opencv4 디렉토리 하위에 헤더가 존재할 수 있습니다.
# spdlog_SOURCE_DIR:STATIC=~/Develop Projects/CXXProject/OpenCV-With-CMake/build/_deps/dep_spdlog-src
target_include_directories(${PROJECT_NAME} PUBLIC
    ${DEP_SOURCE_DIR}
    ${DEP_INCLUDE_DIR}
    src
)

# 의존성 라이브러리 링크
# spdlog와 OpenCV는 각각의 CMake 타겟 이름으로 링크합니다.
target_link_libraries(${PROJECT_NAME} PUBLIC
    ${DEP_LIBS}
)

add_subdirectory(config)
