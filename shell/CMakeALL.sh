BASE_DIR=$(dirname $0)

GENERATOR_TYPE="$1"

sh $BASE_DIR/CMakePrepare.sh
if [ "$GENERATOR_TYPE" = "unix" ]; then
    sh $BASE_DIR/CMakeConfigureAndGenerate.sh   unix
    sh $BASE_DIR/CMakeBuild.sh                  unix
    sh $BASE_DIR/CMakeExecute.sh                unix
elif [ "$GENERATOR_TYPE" = "xcode" ]; then
    sh $BASE_DIR/CMakeConfigureAndGenerate.sh   xcode
    sh $BASE_DIR/CMakeBuild.sh                  xcode
    sh $BASE_DIR/CMakeExecute.sh                xcode
else
    echo "쉘 인자에 반드시 unix 또는 xcode 중 하나를 입력해야 합니다."
    exit 1
fi
