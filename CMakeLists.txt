cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME OpenCVProject)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# FetchContent 모듈 포함
include(FetchContent)

set(DEP_INSTALL_DIR ${CMAKE_BINARY_DIR}/install)    # build/install
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)     # build/install/include
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)             # build/install/lib
set(CMAKE_INSTALL_PREFIX ${DEP_INSTALL_DIR})

# ─── spdlog 의존성 구성 ─────────────────────────────
# (spdlog 저장소 URL 및 태그는 필요에 맞게 수정)
FetchContent_Declare(dep_spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG "v1.x"
    GIT_SHALLOW 1 # 1==true 로 하면 깃 변경 내역 최신것만 받아온다는 의미.
)

set(DEP_LIST ${DEP_LIST} dep_spdlog)
set(DEP_LIBS ${DEP_LIBS} spdlog::spdlog) # spdlog 라이브러리 (타겟 이름은 해당 프로젝트의 CMake 설정에 따라 다를 수 있음)
set(DEP_SOURCE_DIR ${DEP_SOURCE_DIR} ${spdlog_SOURCE_DIR}/include) # spdlog 헤더 (필요에 따라 경로 수정)

# ─── OpenCV 의존성 구성 ─────────────────────────────
FetchContent_Declare( dep_opencv
  GIT_REPOSITORY https://github.com/opencv/opencv.git
  GIT_TAG        4.x
  GIT_SHALLOW TRUE
)

set(BUILD_opencv_world ON CACHE BOOL "" FORCE)
set(BUILD_opencv_contrib_world OFF CACHE BOOL "" FORCE)
set(OPENCV_ENABLE_NONFREE ON CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(BUILD_WITH_STATIC_CRT OFF CACHE BOOL "" FORCE)

set(BUILD_EXAMPLES ON CACHE BOOL "" FORCE)
set(BUILD_PERF_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_PACKAGE OFF CACHE BOOL "" FORCE)
set(BUILD_opencv_apps OFF CACHE BOOL "" FORCE)

set(DEP_LIST ${DEP_LIST} dep_opencv)
set(DEP_SOURCE_DIR ${DEP_SOURCE_DIR} ${OpenCV_SOURCE_DIR}/include) # opencv_world 옵션 활성화: 모든 모듈을 하나의 통합 라이브러리로 빌드
set(OPENCV_EXTRA_MODULES_PATH ../opencv_contrib/modules CACHE PATH "" FORCE)

FetchContent_MakeAvailable(${DEP_LIST})

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

target_compile_definitions(${PROJECT_NAME}
PUBLIC
    WINDOW_NAME="${WINDOW_NAME}"
)
