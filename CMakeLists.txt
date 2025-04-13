cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME opencv-project)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
message(STATUS "CMAKE_TOOLCHAIN_FILE" ${CMAKE_TOOLCHAIN_FILE}) # 환경 변수를 가져오려면 $ENV{VAL}

# VCPKG_INSTALLED_DIR:PATH=~/Develop Projects/CXXProject/OpenCV-With-CMake/build/vcpkg_installed
set(VCPKG_INCLUDE_DIR ${VCPKG_INSTALLED_DIR}/arm64-osx/include)
set(VCPKG_LIB_DIR ${VCPKG_INSTALLED_DIR}/arm64-osx/lib)
set(CONFIG_INCLUDE_DIR ${CMAKE_BINARY_DIR}/configured_files/include)
set(CMAKE_INSTALL_PREFIX ${DEP_INSTALL_DIR})

find_package(fmt REQUIRED)
set(DEP_LIBS ${DEP_LIBS} fmt::fmt)
message(STATUS "fmt Json ${fmt_DIR}")

find_package(nlohmann_json REQUIRED)
set(DEP_LIBS ${DEP_LIBS} nlohmann_json::nlohmann_json)
message(STATUS "nlohmann json ${nlohmann_json_DIR}")

set(OPENCV_ENABLE_NONFREE ON CACHE BOOL "Enable nonfree algorithms" FORCE)
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries" FORCE)
set(BUILD_WITH_STATIC_CRT OFF CACHE BOOL "Use dynamic CRT instead of static" FORCE)
set(BUILD_PACKAGE OFF CACHE BOOL "Build package" FORCE)
set(BUILD_EXAMPLES ON CACHE BOOL "Build examples" FORCE)
set(BUILD_TBB OFF CACHE BOOL "Build TBB from 3rdparty" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "Build tests" FORCE)
set(BUILD_opencv_python3 OFF CACHE BOOL "Build OpenCV Python3 bindings" FORCE)
set(BUILD_opencv_python_bindings_generator OFF CACHE BOOL "Build Python bindings generator" FORCE)
set(BUILD_opencv_python_tests OFF CACHE BOOL "Build OpenCV Python tests" FORCE)
set(WITH_CUDA OFF CACHE BOOL "Enable CUDA support" FORCE)
set(WITH_DIRECTX OFF CACHE BOOL "Enable DirectX support" FORCE)
set(WITH_IPP ON CACHE BOOL "Enable IPP optimizations" FORCE)
set(WITH_MSMF OFF CACHE BOOL "Enable MSMF support" FORCE)
set(WITH_OPENCL ON CACHE BOOL "Enable OpenCL support" FORCE)
set(WITH_OPENCLAMDBLAS ON CACHE BOOL "Enable OpenCL AMD BLAS support" FORCE)
set(WITH_OPENCLAMDFFT ON CACHE BOOL "Enable OpenCL AMD FFT support" FORCE)
set(WITH_OPENGL OFF CACHE BOOL "Enable OpenGL support" FORCE)
set(WITH_FFMPEG ON CACHE BOOL "Enable FFMPEG support" FORCE)
set(OpenCV_ROOT "${VCPKG_INSTALLED_DIR}/arm64-osx/share/opencv4")
find_package(OpenCV REQUIRED)
set(DEP_LIBS ${DEP_LIBS} ${OpenCV_LIBS})

find_package(spdlog REQUIRED)
set(DEP_LIBS ${DEP_LIBS} spdlog::spdlog)

# ─── 실행 파일 생성 및 설정 ──────────────────────────
# Executable에 사용하는 Source들과 Header 모음
set(PROJECT_SOURCES
    src/my_demo_opencv.cpp

    # src/buffer.cpp src/common.cpp src/context.cpp src/image.cpp src/program.cpp
    # src/shader.cpp src/vertex_layout.cpp src/texture.cpp
)

set(PROJECT_HEADERS
    src/my_demo_opencv.hpp
    # src/buffer.h src/common.h src/context.h src/image.h src/program.h
    # src/shader.h src/vertex_layout.h src/texture.h
)
add_subdirectory(config)
add_subdirectory(src/chapter4)
add_subdirectory(src/chapter5)
add_subdirectory(src/chapter6)
add_subdirectory(src/chapter7)
add_subdirectory(src/chapter8)
add_subdirectory(src/chapter9)
add_subdirectory(src/chapter10)

message(STATUS "PROJECT_SOURCES " ${PROJECT_SOURCES})
message(STATUS "PROJECT_HEADERS " ${PROJECT_HEADERS})

add_executable(${PROJECT_NAME}
    app/main.cpp
    ${PROJECT_SOURCES} ${PROJECT_HEADERS}
    ${CHAPTER4_SOURCES} ${CHAPTER4_HEADERS}
    ${CHAPTER5_SOURCES} ${CHAPTER5_HEADERS}
    ${CHAPTER6_SOURCES} ${CHAPTER6_HEADERS}
    ${CHAPTER7_SOURCES} ${CHAPTER7_HEADERS}
    ${CHAPTER8_SOURCES} ${CHAPTER8_HEADERS}
    ${CHAPTER9_SOURCES} ${CHAPTER9_HEADERS}
    ${CHAPTER10_SOURCES} ${CHAPTER10_HEADERS}
)

# 의존성 헤더 경로 추가
target_include_directories(${PROJECT_NAME} PUBLIC
    ${DEP_SOURCE_DIR}
    ${DEP_INCLUDE_DIR}
    ${VCPKG_INCLUDE_DIR}
    ${CONFIG_INCLUDE_DIR}
    src
)

# 의존성 라이브러리 링크
target_link_libraries(${PROJECT_NAME} PUBLIC
    ${DEP_LIBS}
)
