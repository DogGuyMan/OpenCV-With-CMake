cmake -G "Unix Makefiles" -B build
# cmake {project_dir} -DCMAKE_TOOLCHAIN_FILE={util_dir}\vcpkg\scripts\buildsystems\vcpkg.cmake
# CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
# cmake -B build -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
