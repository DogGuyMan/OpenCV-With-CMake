# cmake --build build

# 첫 번째 인자를 받아옵니다.
GENERATOR_TYPE="$1"

if [ "$GENERATOR_TYPE" = "unix" ]; then
    cmake --build --preset unix-makefiles-opencv-project-debug
elif [ "$GENERATOR_TYPE" = "xcode" ]; then
    cmake --build --preset xcode-opencv-project-debug
else
    echo "쉘 인자에 반드시 unix 또는 xcode 중 하나를 입력해야 합니다."
    exit 1
fi
