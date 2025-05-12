## Pedestrian Detection (보행자 감지)

> ### 📄 1. Pedestrian Detection
* 이미지나 비디오에서 보행자(사람)를 자동으로 찾아내는 기술.
* 주로 자율주행, 감시 카메라, 로봇 비전 등에서 사용되며,
입력된 영상에서 사람의 위치를 사각형 등으로 표시.
* 다양한 환경(조명, 배경, 크기, 자세 등)에서 사람을 정확하게 검출하기 위해,
강인한 특징 추출과 분류기가 필요하다.

> ### 📄 2. Histogram of Oriented Gradients Descriptor

#### HoG는 이미지 내에 객체의 Shape를 나타내는 대표적인 특징(Feature) 추출하는 방법.

* KeyPoint(관심점)과 Descriptor(기술자)를 사용하여 사진을 매칭한다.

#### 1).  SIFT

##### ① 조명의 변화에 강하며, 물체의 방향에 상관없는 기술자를 생성할 수 있다.
##### ② HoG 특징 추출 절차
1. **이미지 분할** : SIFT에서 Scale에 불변한 KeyPoint를 찾음 -> KeyPoint 위치를 찾았다면 warp하여 16x16 사이즈의 윈도우를 만든다.
2. **경계(Edge) 방향 계산** : 16x16의 윈도우의 각 픽셀에 x,y 방향의 미분을 통해 방향(Orientation)과 크기(Magnitude)를 계산한다.
3. **방향 히스토그램 생성** : 8방향 벡터, 8개 bin의 히스토그램을 만든다.
4. **블록 정규화** : 그것을 또 4x4의 영역으로 셀을 만들어 16개의 셀 각각에 대해 정규화를 하여 조명 변화에 강하게 한다.
5. **특징 벡터 생성** : 모든 블록의 히스토그램을 연결(concatenate)하여 최종적으로 하나의 고차원 특징 벡터 제작

<div align=center>
    <img src="image/2025-05-12-22-57-00.png" width=80%>
    <h5>이미지 분할</h5>
    <img src="image/2025-05-12-22-56-49.png" width=80%>
    <h5>경계 방향 계산및, 방향 히스토그램 생성</h5>
    <img src="image/2025-05-12-22-57-22.png" width=80%>
    <h5>특징 벡터 생성 (우측이 고차원 특징 벡터임)</h5>
</div>

#### 2). Feature
* 여기서 Feature란, HoG를 사용한 보행자 표현이다.

> ### 📄 2. Training

* HoG 특징을 추출 했다면, 보행자와 비보행자(배경 등) 이미지를 이용해 분류기를 학습시킨다.
* OpenCV에서는 주로 SVM(Support Vector Machine) 분류기를 사용한다.

#### 1).  SVM(서포트 벡터 머신)
* SVM은 두 클래스(보행자/비보행자)를 가장 잘 구분하는
**최대 마진 초평면(Hyperplane ??!!)** 을 찾는 지도학습 분류기로,
HoG 특징 벡터를 입력으로 받아, 보행자일 확률이 높은 영역을 검출한다.

<div align=center>
    <img src="image/2025-05-12-22-58-48.png" width=80%>
    <h5>세로로 하면 마진이 작지만, 여기서 각도를 돌려가면 거리가 최대가 되는 마진을 찾을 수 있다.</h5>
</div>

> ### 📄 3. Optimize

#### 보행자 검출의 정확도와 속도를 높이기 위해 전처리, 후처리, 혹은 분류기 설계가 필요하다.

#### 1). 이미지 패치 크기 조정(Image patch resizing)

* 입력 이미지를 다양한 크기로 변환하여, 여러 크기의 보행자를 검출할 수 있도록 함(멀티스케일).

#### 2). 히스토그램 정규화(Histogram normalization)

* 조명 변화에 강인하도록, 블록 단위로 히스토그램을 정규화함.

#### 3). 이미지 피라미드(Image pyramid)

* 이미지를 여러 해상도로 축소/확대하여, 다양한 크기의 객체를 검출.
윈도우 스트라이드(Window stride) 및 패딩(Padding)
슬라이딩 윈도우의 이동 간격과 패딩을 조절하여, 검출 성능과 속도 균형을 맞춤.

#### 4). 후처리(Post-processing)

* 중복 검출된 사각형을 그룹화(Grouping)하여, 최종적으로 하나의 객체만 남기도록 함.

> ### 📄 4. OpenCV 함수

#### 1). `HOGDescriptor::HOGDescriptor`

* `win_size` : Detection window size. Align to block size and block stride.
* `block_size` : Block size in pixels. Align to cell size. Only (16,16) is supported for now.
* `block_stride` : Block stride. It must be a multiple of cell size.
* `cell_size` : Cell size. Only (8, 8) is supported for now.
* `nbins` : Number of bins. Only 9 bins per cell are supported for now.
* `win_sigma` : Gaussian smoothing window parameter.
* `threshold_L2hys` : L2-Hys normalization method shrinkage.
* `gamma_correction` : Flag to specify whether the gamma correction preprocessing is required or not.
* `nlevels` : Maximum number of detection window increases.

#### 2). `HOGDescriptor::detectMultiScale`
* `img`  Source image.
* `found_locations`  Detected objects boundaries.
* `hit_threshold`  Threshold for the distance between features and SVM classifying plane.
* `win_stride`  Window stride. It indicates the “step size” in both the x and y location of the window
* `padding`  It indicates the number of pixels in both the x and y direction in which the sliding window ROI is “padded” prior to HoG feature extraction. (8,8), (16,16), (24,24), (32,32)
* `scale0`  Coefficient of the detection window increase.
* `group_threshold`  Coefficient to regulate the similarity threshold. When detected, some objects can be covered by many rectangles. 0 means not to perform grouping.

> ### 📄 5. 참고

1. [카이 제곱 : HoG Descriptor](http://vision0814.tistory.com/168)
