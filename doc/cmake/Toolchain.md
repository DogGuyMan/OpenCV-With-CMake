
---

## ToolChain

---

툴체인 : **컴파일러, 링커, 관련 도구, 그리고 타겟 플랫폼에 맞는 경로/설정 등을 한 번에 지정하는 설정 파일**

---

> ### 📄 1. 툴체인(toolchain)이란?

- **컴파일러, 링커, 빌드 도구, 표준 라이브러리, 헤더 파일, 경로 등**을 묶어서 "툴체인"이라고 부름.
- 예시:
  - GCC, Clang, MSVC 등 컴파일러
  - ARM, x86, M1 등 타겟 아키텍처
  - cross-compiling(크로스 컴파일) 환경에서 특히 중요

---

> ### 📄 2. CMake에서의 toolchain 파일

- **toolchain 파일**은 CMake에서 빌드 환경을 제어하기 위한 **설정 파일**임.
- 보통 `.cmake` 확장자를 가지며, 내부에 변수 설정(CMAKE_C_COMPILER, CMAKE_CXX_COMPILER, CMAKE_SYSROOT 등)이 들어감.
- **목적:**
  - 특정 컴파일러/플랫폼/라이브러리 경로를 명확히 지정
  - 크로스 컴파일(예: mac에서 라즈베리파이용 바이너리 빌드)
  - vcpkg, conan 등 패키지 매니저와 연동

---

> ### 📄 3. 사용 예시

#### 1). toolchain 파일 지정

```sh
cmake -B build -DCMAKE_TOOLCHAIN_FILE=/path/to/toolchain.cmake
```

#### 2). vcpkg toolchain 예시

- vcpkg를 쓸 때는 아래처럼 toolchain 파일을 지정함:
  ```sh
  cmake -B build -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
  ```
- 이 파일이 vcpkg에서 설치한 라이브러리, 헤더 경로 등을 자동으로 CMake에 알려줌.

#### 3). CMakePreset.json 에서 사용하기
```json
...
    "configurePresets": [
        {
            "name": "unix-makefiles-opencv-project-debug",
            "displayName": "도구 체인 파일을 사용하여 사전 설정 구성",
            "description": "Unix Makefiles 생성기, 빌드 및 설치 디렉터리 설정",
            "generator": "Unix Makefiles",
            "binaryDir": "${sourceDir}/build/",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug",
                "CMAKE_TOOLCHAIN_FILE": {
                    "value": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake",
                    "type": "FILEPATH"
                },
                "CMAKE_INSTALL_PREFIX": "$env{VCPKG_ROOT}/installed/arm64-osx",
                "VCPKG_TARGET_TRIPLET": "$env{VCPKG_DEFAULT_TRIPLET}"
            }
        }
...
```
---

> ### 📄 4. toolchain 파일 내부 예시

```cmake
# toolchain-arm.cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
set(CMAKE_SYSROOT /opt/arm-sysroot)
```
- 위 예시는 ARM 리눅스용 크로스 컴파일을 위한 toolchain 파일

---

> ### 📄 5. 요약

- **CMake toolchain**은 빌드에 사용할 컴파일러, 링커, 경로, 환경 등을 한 번에 지정하는 설정 파일
- 크로스 컴파일, 패키지 매니저(vcpkg 등) 연동, 특정 환경 강제 등에서 필수적
- `-DCMAKE_TOOLCHAIN_FILE=...` 옵션으로 지정
