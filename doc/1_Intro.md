
---

## Introduction

---

> ### 📄 1. 컴퓨터 비전이란


#### 객체 인식, 인간의 시각 처리를 컴퓨터에게 수행할 수 있게끔 자동화한다.

* 인간의 시각 처리 : 눈 + 뇌
* 컴퓨터의 시각 처리 : 센서 + 알고리즘


#### 1). CV를 통해 할 수 있는 것

1. **Preprocessing** : 이미지 전처리 ( 노이즈 제거 / 밝기 어둡게, 밝게 조절 / 디테일 검출 )
2. **Edge Detection / Line Detection**
3. **Image Transformation** : 건물을 비스듬히 촬영한 것을 정면에서 촬영한 것처럼
4. **Image/View Segmentation** : 정적인 이미지에서 객체를 특정 영역, 마스크를 얻는 것
5. **Object Detection / Tracking** : 움직이는 객체의 위치(좌표)와 클래스를 얻는 것.

---

#### 2). "Image/View Segmentation" VS "Object Detection / Tracking"

##### 두 가지 모두 객체의 특정 픽셀 영역이 필요하다는 점은 동일하다.

##### ① Image/View Segmentation

* 각 픽셀이 어떤 객체에 속하는지, 이미지에서 특정 영역을 나누고, 분리하여 ***"마스크"*** 를 얻는 작업.
* 일명 정적인 객체들을 영역으로 분리하는 것.
* 이미지 전체의 구조 분석과, 정밀한 작업이 필요

##### ② "Object Detection / Tracking"

* 여러 프레임에서 어떤 객체를 동일한 객체로 추적하는 것. 객체의 ***"위치(좌표)와 클래스(라벨)"*** 을 얻는 작업.
* 일명 움직이는 객체 하나를 집중해 프레임별로
위치 이동 추적에 적합한 것.
* 범용적이고 빠른 추적이 중요.


---

#### 3). 예시
1. 차선 인식
2. 고양이, 강아지 동물 인식,
3. 다른 날씨와, 시간대에 촬영한 에펠탑 인식하기
4. 배경과 객체 분리
5. Blur/Sharpen, 경계선 검출, 명암 효과 강화, 컬러 조정 및 동적 조명 효과, 왜곡 물결 효과, 모션 블러
6. Depth Mapping

---

> ### 📄 2. 컴퓨터 비전의 워크플로

```
1. 영상 입출력 : 입력 / 출력
2. 전처리  : 이미지 변환 / 노이즈 제거 / 이진화
3. 특징 추출 : 특징 (코너 탐지 / 특징점 검출 및 서술자 생성 / 에지 검출)
4. 객체 검출 및 영상 분할 : 객체 영역 탐지 / 의미 있는 부분으로 영상 분할
5. 분석 : 객체 분류 및 매칭 / 포즈 추정 / 움직임 분석 / 3D 재구성
```


#### 1). 영상 입출력

* 외부 데이터(이미지, 비디오)를 읽어오고 나서, OpenCV 에서 처리할 수 있는 형식(`cv::Mat`)으로 변환 및 처리 결과를 저장.
  * **입력**
    * `cv::imread()`: 이미지를 파일에서 읽음.
    * `cv::VideoCapture()`: 비디오 파일 또는 카메라 스트림을 읽음.
  * **출력**
    * `cv::imwrite()`: 처리 결과 이미지를 파일에 저장.
    * `cv::VideoWriter()`: 처리 결과 비디오를 저장.
    * `cv::imshow()`: 창에 이미지 또는 비디오를 표시.


---

#### 2). 전처리

* 데이터를 분석하기 전에 노이즈 제거, 크기 조정, 형식 변환 등으로 입력 데이터를 처리
    1. **이미지 변환**:
        * 크기 조정 : `cv::resize()`
        * 좌표 변환 : `cv::warpAffine()`, `cv::warpPerspective()`
        * 형식 변환 : `cv::cvtColor()` (예: RGB → Grayscale)
    2. **노이즈 제거**:
        * 블러링: `cv::GaussianBlur()`, `cv::medianBlur()`
        * 경계 보존 필터: `cv::bilateralFilter()`
    3. **이진화**:
        * `cv::threshold()`
        * `cv::adaptiveThreshold()`

---

#### 3). 특징 추출

* 이미지의 주요 정보를 나타내는 특징(엣지, 코너, 점)을 추출하는 단계.
이 단계는 객체 검출 및 분석을 위한 기초 데이터를 제공.
    1. **코너 탐지** :
        * `cv::goodFeaturesToTrack()` (Shi-* omasi 코너 탐지)
        * `cv::cornerHarris()` (Harris 코너 탐지)
    2. **특징점 검출 및 서술자 생성** :
        * SIFT: `cv::SIFT::create()`
        * SURF: `cv::xfeatures2d::SURF::create()`
        * ORB: `cv::ORB::create()`
    3. **에지 검출** :
        * `cv::Canny()`
        * `cv::Laplacian()`


---

#### 4). 객체 검출 및 영상 분할

* 특정 객체나 영역을 찾아내거나 이미지/영상을 의미 있는 부분으로 나눔
  1. **객체 검출**
        * 검출기 사용 :
            * Haar Cascade: `cv::CascadeClassifier`
            * 딥러닝 기반: `cv::dnn.readNet()`
        * 모델 활용 :
          * YOLO, SSD 등 외부 딥러닝 모델
        * 모션 기반 :
          * 배경 차분: `cv::BackgroundSubtractorMOG2`

  2. **영상 분할**:
        * 임계값 기반 분할 : `cv::threshold()`
        * 능동적 분할 : `cv::watershed()`
        * 초점 영역 분할 : `cv::grabCut()`


---

#### 5). 분석

* 추출된 데이터를 기반으로 고급 분석 작업을 수행하여 객체의 의미나 동작을 분석
  1. **객체 인식** :
      * 추출된 특징점을 기준으로 객체를 분류하거나 매칭
      * `cv::BFMatcher` (Brute Force 매칭)
      * `cv::FlannBasedMatcher` (빠른 매칭)
  2. **포즈 추정** :
      * 2D에서 3D 객체 포즈 추정: `cv::solvePnP()`
      * 카메라 캘리브레이션: `cv::calibrateCamera()`
  3. **움직임 분석** :
      * Optical Flow: `cv::calcOpticalFlowPyrLK()`, `cv::calcOpticalFlowFarneback()`
      * 물체 추적: `cv::Tracker` (KCF, MIL 등)
  4. **3D 재구성** :
      * 스테레오 매칭: `cv::stereoBM()`, `cv::stereoSGBM()`
      * 깊이 지도 생성 및 3D 포인트 클라우드
