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
* vcpkg CLI Add port
    ```bash
    vcpkg add port fmt
    vcpkg add port nlohmann-json
    vcpkg add port spdlog
    vcpkg add port opencv4
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
##### ⑤ CMake `find_package()` 
```txt
...

find_package(fmt REQUIRED)
set(DEP_LIBS ${DEP_LIBS} fmt::fmt)

find_package(nlohmann_json REQUIRED)
set(DEP_LIBS ${DEP_LIBS} nlohmann_json::nlohmann_json)

find_package(OpenCV REQUIRED)
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

#### 3) [OpenCL CMake Cache 설정](https://blog.naver.com/91blacksheep/221492188605)
