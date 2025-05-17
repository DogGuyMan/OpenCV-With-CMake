# cmake -G "Unix Makefiles" -B build
# CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"

GENERATOR_TYPE="$1"

if [ "$GENERATOR_TYPE" = "unix" ]; then
    cmake --preset unix-makefiles-opencv-project-debug
elif [ "$GENERATOR_TYPE" = "xcode" ]; then
    cmake --preset xcode-opencv-project-debug
    open ./build/opencv-project.xcodeproj
else
    echo "쉘 인자에 반드시 unix 또는 xcode 중 하나를 입력해야 합니다."
    exit 1
fi
