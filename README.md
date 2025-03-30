# OpenCV With CMake

> ### 📄 CLI로 CMake GNU 파일 제작 Shell 스크립트 실행하기


<div align=center>
    <img src="image/2024-10-11-16-48-35.png" width=50%>
</div>

```bash
# sh GNU_DirectoryStructure.sh <ProjectName>

# 본인의 경우 다음과 같이 생성함
sh GNU_DirectoryStructure.sh OpenCV-With-CMake
```

> ### 📄 VSCode 터미널이 Zsh가 아닐때,

#### 1). 쉘 환경 변수에 code 명령 추가하기

<div align=center>
    <img src="image/2025-03-08-18-45-56.png" width=80%>
</div>

#### 2). ‘tasks.json" 사용하기
* 마치 github action에서 yaml을 만들듯.
vscode에서 파일이 열릴때, 등등 이벤트에 수행할 커맨드를 추가할 수 있다.

1. [vscode task onstartup](https://www.roboleary.net/vscode/2020/10/19/vscode-task-onstartup.html)
2. [automated task fix vscodel](https://www.roboleary.net/vscode/2023/12/31/automated-task-fix-vscode.html)

<div align=center>
    <img src="image/2025-03-08-23-08-49.png">
    <h5></h5>
</div>


> ### 📄 CMake 세팅

#### 1). XXX_SOURCE_DIR의 생성 순서

FetchContent_MakeAvailable 이후에 생긴다.

```txt
FetchContent_MakeAvailable(${DEP_LIST})
set(DEP_SOURCE_DIR ${DEP_SOURCE_DIR} "${spdlog_SOURCE_DIR}/include") # spdlog 헤더 (필요에 따라 경로 수정)
set(DEP_SOURCE_DIR ${DEP_SOURCE_DIR} "${OpenCV_SOURCE_DIR}/include") # opencv_world 옵션 활성화: 모든 모듈을 하나의 통합 라이브러리로 빌드
```

#### 2). VCPKG 사용

#### FetchContent는 버리자! 화난다 진짜 VCPKG 쓰자.

##### ① 환경 변수 설정
```shell
# ~/.zshrc
export VCPKG_ROOT="$HOME/vcpkg"
export PATH="$PATH:$VCPKG_ROOT"
```

##### ② VCPKG 설치 밎 업데이트
```bash
cd ~/vcpkg
git pull
sudo chmod 700 ./bootstrap-vcpkg.sh
sh ./bootstrap-vcpkg.sh
```

* Package With Feature
    * `vcpkg install "ffmpeg[core,avcodec,avdevice,avfilter,avformat,ffmpeg,ffplay,ffprobe,nvcodec,opencl,postproc,sdl2,swscale,nonfree]:arm64-osx" --recurse`
    1. **대괄호([]) 표기**
       * **의미:** vcpkg에서는 패키지 설치 시 기본 기능 외에 추가 옵션이나 “피처(feature)”를 선택할 수 있도록 대괄호([])를 사용합니다.
       * **차이점:**
         * **예: `opencv4[ffmpeg]`**
           → OpenCV4를 설치할 때 ffmpeg 관련 기능(예: 동영상 디코딩/인코딩 지원)을 추가로 활성화합니다.
         * **예: `opencv4` (대괄호 없이)**
           → 기본 피처만 설치하게 됩니다.
    2. **`--recurse` 옵션**
       * **의미:** 일부 패키지는 피처를 추가하거나 변경하면 의존하는 다른 패키지들도 함께 재빌드(rebuild)되어야 합니다.
       * **차이점:**
         * `--recurse` 사용 시**
           → 설치 계획에 포함된 패키지의 변경 사항(예: 피처 추가)으로 인해 재빌드가 필요한 모든 관련 의존 패키지들도 함께 다시 빌드하도록 승인합니다.
         * `--recurse` 미사용 시**
           → 변경된 피처로 인해 일부 의존 패키지가 재빌드되어야 하는 상황에서 설치가 실패할 수 있습니다.

* 이 명령을 zsh에서 쓸 수 없는 이유?
  * zsh는 대괄호([])를 파일 이름 패턴(글로빙)으로 해석하기 때문에 발생
  * 즉, opencv4[ffmpeg] 부분이 쉘에 의해 패턴으로 인식되어 올바른 문자열로 전달되지 않으므로
  "bad pattern" 오류가 나타난다..
  ```
  vcpkg install 'opencv4[ffmpeg]:arm64-osx' --recurse
  ```


##### ③ `vcpkg.json` 로 menifest mode 진입

```json
# vcpkg.json
{
  "$schema": "https://raw.githubusercontent.com/microsoft/vcpkg-tool/main/docs/vcpkg.schema.json",
  "name": <PROJECT_NAME>,
  "version": "0.0.1",
  "dependencies": [
  ],
  "builtin-baseline": "782ccc18d8b819cdef6794a6c03eb3d9f7cd04aa"
  // <$VCPKG_ROOT>로 이동하고 터미널에서 git log 했을때 최상단의 커밋의 hex코드 전부 복붙
}

```
##### ④ `vcpkg add port <EXTERNAL_LIBRARIY>`

https://learn.microsoft.com/ko-kr/vcpkg/commands/install

* vcpkg CLI Add port
    ```bash
    vcpkg add port fmt
    vcpkg add port nlohmann-json
    vcpkg add port spdlog
    vcpkg add port opencv4
    ```
    ```bash
    vcpkg integrate install
    ```

* Add port 결과
    ```json
    # vcpkg.json
    {
      "$schema": "https://raw.githubusercontent.com/microsoft/vcpkg-tool/main/docs/vcpkg.schema.json",
      "name": "opencv-project",
      "version": "0.0.1",
      "dependencies": [
        "fmt",
        "nlohmann-json",
        "spdlog",
        "opencv4"
      ],
      "builtin-baseline": "782ccc18d8b819cdef6794a6c03eb3d9f7cd04aa"
    }
    ```
* feature 추가
  * `opencv4` 대신 좀더 늘려 쓰자.
    ```json
    "dependencies": [
        {
            "name":"opencv4",
            "features": ["ffmpeg", "opencl"]
        },
    ]
    ```
* manifest에서 install

##### ⑤ CMake `find_package()`

* `find_package()` **이전에 선언**해야 하는 변수가 있고, **이후에 선언**해야 하는 변수가 있다.
* 만약 mac에 패키지 매니저인 brew와 vcpkg를 사용중이라면
두 패키지 매니저 두가지 중 어느 곳에 깔린 패키지를 가져와야 하느냐.
  > Fair point. Suppose if you have set a toolchain to use vcpkg. Now you want to use apache-arrow from the brew installation. so a solution would be the set the brew path in find_package(Arrow CONFIG REQUIRED PATHS /usr/local/lib/cmake/arrow NO_DEFAULT_PATH). This one loads the dependencies of the arrow package by looking into packages installed by vcpkg, which is not what we want. Then you end up by writing find_package recursively for all the dependencies.
  * 결론은 명시적으로 `find_package`를 사용할 수 있다.

```txt
...

find_package(fmt REQUIRED)
set(DEP_LIBS ${DEP_LIBS} fmt::fmt)

find_package(nlohmann_json REQUIRED)
set(DEP_LIBS ${DEP_LIBS} nlohmann_json::nlohmann_json)

// 대표적으로 find_package 이전에 선언해야 하는 변수
set(OpenCV_ROOT "${VCPKG_INSTALLED_DIR}/arm64-osx/share/opencv4")
find_package(OpenCV REQUIRED)
// 대표적으로 find_package 이후에 선언해야 하는 변수
set(DEP_LIBS ${DEP_LIBS} ${OpenCV_LIBS})
message(STATUS "OpenCV_LIBS ${CMAKE_TOOLCHAIN_FILE}")

find_package(spdlog REQUIRED)
set(DEP_LIBS ${DEP_LIBS} spdlog::spdlog)

...

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${DEP_LIBS}
)
```


##### ⑥ 툴체인 연결 & 빌드

```bash
cmake -B build -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

* 이게 뜻하는 바는 무엇이냐면, 실제 내 하드웨어 어딘가에 깔려있는

---

> ### 📄 VSCode에서 라이브러리를 못찾아 올떄,

<div align=center>
    <img src="./image/스크린샷 2025-03-16 22.01.21.png">
    <h5>분명 CMake Configure&Generate 했는데도 못불러온단 말이지..</h5>
</div>

<div align=center>
    <img src="./image/스크린샷 2025-03-16 22.01.27.png">
    <h5>.vscode/c_cpp_properties.json 을 수정하면 된다.</h5>
</div>


<div align=center>
    <img src="./image/2025-03-16-22-29-27.png">
    <h5>include path를 잘 찾아온다.</h5>
</div>

---


> ### 📄 `cmake -B build --fresh`이후 발생하는 문제

* 갑자기 `spdlog`가 문제다.
    ```bash
    CMake Error at CMakeLists.txt:23 (find_package): By not providing "Findspdlog.cmake" in
    CMAKE_MODULE_PATH this project has asked CMake to find a package configuration file
    provided by "spdlog", but CMake did not find one.

    Could not find a package configuration file provided by "spdlog"
    with any of the following names:

    spdlogConfig.cmake
    spdlog-config.cmake
    Add the installation prefix of "spdlog" to CMAKE_PREFIX_PATH
    or set "spdlog_DIR" to a directory containing one of the above files.
    If "spdlog" provides a separate development package or SDK,
    be sure it has been installed.
    ```
* 사실 `--fresh`를 하는 이유는, `CMakeCache`를 초기화 하기 위함인데.
  이럴때는 극단적으로 모두 삭제해 버리자.
  ```shell
  rm -rf build
  mkdir build
  ```

> ### 📄 `add_subdirectory()`의 변수들의 Scope
---

> ### 📄 실행
<div align=center>
    <img src="image/2025-03-16-23-23-41.png">
    <h5>FetchContent를 버리니 병이 나았습니다. 🥰</h5>
</div>

---

> ### 📄 참고

#### 1). [삼각형의 실전! CMake 초급](https://inf.run/og3Jm)
* 이 강의를 통해 ...
    1. CMake CLI,
    2. C/C++ 라이브러리 의존성 관리
    3. 모던 CMake의 모듈러 디자인에 대해 이해했고, 확장성 있는 빌드 시스템 작성법을 배웠음

#### 2). [컴퓨터 비전 한동대 황성수 교수님](http://www.kocw.net/home/m/cview.do?lid=f879dfef45031db6)

* 이 강의를 통해
  1. 컴퓨터 비전 이론 익히기
  2. C++을 통한 컴퓨터 비전 프로젝트 만들기

#### 3) OpenCL CMake Cache 설정
* https://blog.naver.com/91blacksheep/221492188605
* https://joonwooson.gitbooks.io/opencv/content/
* https://www.youtube.com/watch?v=e7GtcsSJ51s
* https://www.youtube.com/watch?v=yccbaXqRtNU
* https://velog.io/@jinhasong/OpenCV-4.4
