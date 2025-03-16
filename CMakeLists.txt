cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME opencv-project)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# VCPKG_INSTALLED_DIR:PATH=~/Develop Projects/CXXProject/OpenCV-With-CMake/build/vcpkg_installed
set(VCPKG_INCLUDE_DIR ${VCPKG_INSTALLED_DIR}/arm64-osx/include)
set(VCPKG_LIB_DIR ${VCPKG_INSTALLED_DIR}/arm64-osx/lib)
set(CONFIG_INCLUDE_DIR ${CMAKE_BINARY_DIR}/configured_files/include)
set(CMAKE_INSTALL_PREFIX ${DEP_INSTALL_DIR})

find_package(fmt REQUIRED)
set(DEP_LIBS ${DEP_LIBS} fmt::fmt)

find_package(nlohmann_json REQUIRED)
set(DEP_LIBS ${DEP_LIBS} nlohmann_json::nlohmann_json)

find_package(OpenCV REQUIRED)
set(DEP_LIBS ${DEP_LIBS} ${OpenCV_LIBS})
message(STATUS "OpenCV_LIBS ${CMAKE_TOOLCHAIN_FILE}")

find_package(spdlog REQUIRED)
set(DEP_LIBS ${DEP_LIBS} spdlog::spdlog)


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

add_subdirectory(config)
