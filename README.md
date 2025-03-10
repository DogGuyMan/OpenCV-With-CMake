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
