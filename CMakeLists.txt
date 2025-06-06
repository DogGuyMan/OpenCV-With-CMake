# ─── CMake 설정 ─────────────────────
cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME opencv-project)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

# ─── 의존성 라이브러리 설정 ───────────────────────

# VCPKG_INSTALLED_DIR:PATH=~/Develop Projects/CXXProject/OpenCV-With-CMake/build/vcpkg_installed
# CMakePresets에 CMAKE_MODULE_PATH를 설정하지 않으면 cmake/*.cmake 파일을 찾을 수 없음
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(Config)
include(CppStandard)
include(Dependency)

# ─── 실행 파일 생성 및 설정 ──────────────────────────
# Executable에 사용하는 Source들과 Header 모음

set(PROJECT_SOURCES
    src/my_demo_opencv.cpp
)

set(PROJECT_HEADERS
    src/my_demo_opencv.hpp
)

set(PROJECT_CHAPTER_DEFINES)

add_subdirectory(config)
# add_subdirectory(src/chapter4)
# add_subdirectory(src/chapter5)
# add_subdirectory(src/chapter6)
# add_subdirectory(src/chapter7)
# add_subdirectory(src/chapter8)
# add_subdirectory(src/chapter9)
# add_subdirectory(src/chapter10)
# add_subdirectory(src/chapter11)
# add_subdirectory(src/chapter12)
# add_subdirectory(src/chapter13)
# add_subdirectory(src/chapter14)
# add_subdirectory(src/chapter15)
# add_subdirectory(src/chapter16)
# add_subdirectory(src/chapter17)
# add_subdirectory(src/chapter18)
# add_subdirectory(src/chapter19)
# add_subdirectory(src/chapter20)
add_subdirectory(src/chapter21)


# ─── 설정한 Define 전처리 디버깅 ──────────────────────────
# get_directory_property(_defs COMPILE_DEFINITIONS)
# message(STATUS "defs = ${_defs}")

add_executable(${PROJECT_NAME}
    app/main.cpp
    ${PROJECT_SOURCES} ${PROJECT_HEADERS}
)

target_compile_definitions(${PROJECT_NAME} PUBLIC ${PROJECT_CHAPTER_DEFINES})

# 의존성 헤더 경로 추가
target_include_directories(${PROJECT_NAME} PUBLIC
    ${DEP_SOURCE_DIR}
    ${DEP_INCLUDE_DIR}
    ${CONFIG_INCLUDE_DIR}
    src
)

# 의존성 라이브러리 링크
target_link_libraries(${PROJECT_NAME} PUBLIC
    ${DEP_LIBS}
)

# ─── 빌드 후 리소스 복사 ──────────────────────────
set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/resources)
# Generator Expression은 빌드 시스템 생성 이후(빌드 타임)에 지연 평가된다. 따라서 다음줄에 OutPut을 사용할 수 없다..
set(OUTPUT_DIR $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# file(COPY "${RESOURCE_DIR}" DESTINATION ${CMAKE_BINARY_DIR})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND
    ${CMAKE_COMMAND} -E copy_directory "${RESOURCE_DIR}" "${OUTPUT_DIR}/resources"
    # 다음 커맨드를 쉘에 실행하는것과 동치
    # /usr/local/bin/cmake -E copy_directory "${RESOURCE_DIR}" "${OUTPUT_DIR}/resources"
    COMMENT "${PROJECT_NAME} 프로젝트 빌드 후 리소스를 build 디렉터리에 복사"
    )

# ─── XCode 리소스 대응 ──────────────────────────
# 애플이며, XCode를 빌드 제너레이터로 설정시 수행할 커맨드로, Xcode에 리소스 디렉토리를 참조할 수 있도록 함.
if(APPLE AND CMAKE_GENERATOR STREQUAL "Xcode")
    set_source_files_properties("${RESOURCE_DIR}" PROPERTIES
        MACOSX_PACKAGE_LOCATION "resources"
    )
    target_sources(${PROJECT_NAME} PRIVATE "${RESOURCE_DIR}")
endif()
