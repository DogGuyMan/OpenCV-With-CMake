# CMakeLists.txt of chapter4

# https://junstar92.tistory.com/211
# add_subdirectory()와 이로 인해 발생하는 변수의 scope에 대해서 알아보겠습니다.
# 그리고 add_subdirectory()와 유사하지만 약간은 다른 include()에 대해서도 살짝 알아보도록 하겠습니다.

# 부모 scope에서 정의된 모든 변수는 자식 scope에서 볼 수 있으며, 다른 변수들과 마찬가지로 해당 값을 읽을 수 있습니다.
# 자식 scope에서 생성된 모든 변수들은 부모 scope에서 볼 수 없습니다.
# 자식 scope에서 발생한 모든 변수들의 변경사항은 해당 자식 scope에서만 유효합니다. 즉, 변경된 변수가 부모 scope에서 생성되어 자식 scope로 전달된 변수라면 자식 scope에서 변경되었더라도 부모 scope에는 영향을 끼치지 않습니다. 부모 scope에서 정의된 변수가 자식 scope에서 변경되었다면, 수정된 변수는 자식 scope를 벗어날 때 삭제되는 새로운 변수처럼 동작합니다.

# 정리하자면, 자식 scope에 진입하게 되면 해당 시점에서 부모 scope의 정의된 모든 변수의 복사본을 전달받게 됩니다.
# 자식 scope의 변수에 대한 모든 변경 사항들은 자식 scope의 복사본에서 수행되고, 부모 scope의 변수는 변경되지 않은 상태로 유지됩니다.

# 부모 scope로 변수 전달 방법
# 자식 scope에서 변경되거나 추가된 변수가 부모 scope에서 필요한 경우가 있습니다.
# 예를 들어, 서브 디렉토리의 소스 파일 목록을 생성하고 상위 디렉토리에 다시 전달하는 경우가 있습니다.
# 이는 set() 명령에서 PARENT_SCOPE 라는 키워드

set(CHAPTER4_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/baisic_data_structure_in_openCV.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/read_an_image_in_openCV.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/read_a_video_from_a_file.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/read_a_video_from_a_webcam.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/play_with_video_capture.cpp
    PARENT_SCOPE
)

# message(STATUS "baisic data source path " ${CMAKE_CURRENT_SOURCE_DIR}/baisic_data_structure_in_openCV.cpp)
# message(STATUS "read an image source path" ${CMAKE_CURRENT_SOURCE_DIR}/read_an_image_in_openCV.cpp)

set(CHAPTER4_HEADERS
    ${PROJECT_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/baisic_data_structure_in_openCV.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/read_an_image_in_openCV.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/read_a_video_from_a_file.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/read_a_video_from_a_webcam.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/play_with_video_capture.hpp
    PARENT_SCOPE
)

# message(STATUS "baisic data header path" ${CMAKE_CURRENT_SOURCE_DIR}/baisic_data_structure_in_openCV.hpp)
# message(STATUS "read an image header path" ${CMAKE_CURRENT_SOURCE_DIR}/read_an_image_in_openCV.hpp)
