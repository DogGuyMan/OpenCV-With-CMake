# cmake -G "Unix Makefiles" -B build
# CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
cmake --preset opencv-project
cmake --build --preset opencv-project
