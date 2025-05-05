BASE_DIR=$(dirname $0)

sh $BASE_DIR/CMakePrepare.sh
sh $BASE_DIR/CMakeConfigure.sh
sh $BASE_DIR/CMakeBuild.sh
sh $BASE_DIR/CMakeExecute.sh
