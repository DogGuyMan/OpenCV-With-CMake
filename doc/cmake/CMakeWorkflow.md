
---

## CMake의 단계(Workflow)

---

> ### 📄 1. **Configure 단계**
* **목적:**
  소스 코드와 CMakeLists.txt를 바탕으로, 빌드 시스템(예: Makefile, Ninja, Xcode 프로젝트 등)에 맞는 중간 파일(빌드 스크립트, 프로젝트 파일 등)을 생성.
* **주요 작업:**
  * CMakeLists.txt 파싱
  * 의존성 확인 및 경로 설정
  * 빌드 옵션/환경 변수 적용
  * 실제 빌드 시스템에 맞는 파일 생성 (예: Makefile, .ninja, .xcodeproj 등)

---

> ### 📄 2. **Generate 단계**
* **목적:**
  Configure 단계에서 설정된 내용을 바탕으로, 실제 빌드 시스템이 사용할 수 있는 파일을 생성.
* **주요 작업:**
  * 선택한 제네레이터(예: "Unix Makefiles", "Ninja", "Xcode" 등)에 맞는 빌드 파일 생성
  * 프로젝트 구조, 타겟, 의존성 등 반영
  * 지정한 빌드 디렉토리(`build/`)에 생성합니다.
    * 전통적인 방법 : `cmake -B <build-directory> -G "<generator-name>"`
    * 현대적 방식 : `cmake --preset <CMakePresets.json에 첨부한 preset name>`
  * *실제로 CMake는 Configure와 Generate를 한 번에 처리함*

---

> ### 📄 3. **Build 단계**
* **목적:**
  위에서 생성된 빌드 시스템 파일을 이용해 실제로 소스 코드를 컴파일/링크하여 실행 파일, 라이브러리 등을 생성.
* **주요 작업:**
  * `make`, `ninja`, Xcode의 빌드 버튼 등으로 빌드 실행
    * 전통적인 방식 : `cmake --build <build-directory>`
    * 현대적 방식 : `cmake --preset <CMakePresets.json에 첨부한 preset name>`
