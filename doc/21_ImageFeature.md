
---

## 21 Image Feature

---

> ### 📄 1. Image Feature

#### 1). Image Feature란?

* 이미지 내에서 인식, 분류, 추적 등을 수행하는데 추출되거나 저장된 유용한 정보를 의미한다.
  * Feature란, 일명 이미지의 정보 요약이다.

* 즉, Image Feature은 메모리 상에서 처리되는 데이터(예: 특징점 좌표, 디스크립터 등)일 수도 있고, XML과 같이 별개의 파일로 저장할 수도 있다.
  * 그 데이터는 이미지의 중요한 부분 구조(점, 모서리, 에지, 객체)등을 수치적으로 표현되어 있다.
  * 픽셀들과의 관계나, 특정 알고리즘(SIFT, SURF, ORB)등 Feature Detector을 통해 추출된 결과이다.

* 이를 통해 이미지 전체를 픽셀 단위로 비교하거나 처리하는 것이 아닌,
의미있는 부분(특징점, 에지, 코너)들만 추출한 파일로, 성능, 속도, 공간을 절약하는 기법이 되겠다.

#### 2). 좋은 Feature란.

##### ① 불변성 (invariant)

* 조명 변화(Illumination)에 강인해야 한다.
* 평행이동(Translation)에 영향을 받지 않아야 한다.
* 크기 변화(Scale)에 영향을 받지 않아야 한다.
* 회전(Rotation)에 영향을 받지 않아야 한다.
* 원근 변환(Perspective transform, 즉 시점 변화)에도 견고해야 한다.

##### 즉, 좋은 Feature는 위 수치들의 변화에도 이미지를 대표하는 성질은 불변(invariant)해야 한다.

##### ② 성능

* 연산이 가벼워야 하며,
* 메모리 공간또한 효율적이여야 한다.

---

> ### 📄 2. Feature Extractor & Descriptor

#### 1). Extractor & Descriptor 란?

* Feature Extractor: 이미지를 분석해 의미있는 특징점(Feature)을 찾는 알고리즘 혹은 함수임.
  ex). SIFT, SURF, ORB, Harris Corner
* Feature Descriptor: 추출된 Feature(예: 특징점) 주변의 픽셀 패턴, 구조, 분포 등을 수치적(벡터, 배열)으로 담아내는 자료 형색

---

> ### 📄 3. 대표적인 FED(Feature Extractor & Descriptor) 알고리즘

#### 1). ORB
##### oFast detector + r-BRIEF descriptor

1. **빠른 속도(Fast)**
   * ORB는 FAST(Features from Accelerated Segment Test) 코너 검출기를 기반으로 하여, 특징점 추출 속도가 매우 빠르다!
   * 실시간 영상 처리나 임베디드 환경에서도 효율적으로 사용 가능.

2. **불변성(Invariance)**
   * 조명 변화, 회전(Rotation), 평행이동(Translation), 크기 변화(Scale)에 대해 강인하다.
   * BRIEF(이진 디스크립터)를 회전에 대해 불변하도록 개선(r-BRIEF)하여, 다양한 시점 변화에도 견고하다.

3. **이진 디스크립터(Binary Descriptor)**
   * BRIEF 기반의 이진 벡터를 사용하여, 디스크립터의 크기가 작고, 매칭 속도가 매우 빠르다.
   * 해밍 거리(Hamming Distance)로 빠른 매칭이 가능.

4. **효율적인 메모리 사용**
   * 디스크립터가 이진 벡터이기 때문에, 메모리 사용량이 적고, 대용량 데이터 처리에 유리하다.

---

> ### 📄 4. 이미지 매칭


#### 1). Feature 기반 이미지 매칭 절차

##### Feature 추출 -> Descriptor 생성 -> 유사도 비교 -> 좋은 매칭 선별의 순서로 진행된다.

1. **입력 이미지에서 Feature 추출**
   * Feature Extractor(예: SIFT, ORB 등)를 사용해 각 이미지에서 특징점(Feature)을 찾는다.
2. **각 Feature를 Descriptor로 표현**
   * 추출된 각 Feature에 대해 Descriptor(특징 벡터)를 생성한다.
3. **서로 다른 이미지의 Feature 간 유사도 비교**
   * 두 이미지의 Descriptor를 비교하여, 서로 비슷한 Feature 쌍을 찾는다.
4. **좋은 매칭 추출**
   * 유사도가 높은 Feature 쌍만을 선별하여 최종 매칭 결과로 사용한다.

---

#### 2). 좋은 매칭(Good Matching)이란?

##### 좋은 매칭은 "고유성"과 "신뢰도"가 높아야 하며, NNDR과 같은 기준으로 평가한다.

* 좋은 매칭이란, 한 이미지의 Feature A와 다른 이미지의 Feature B가 서로 유사도가 높고,
  동시에 A와 B 외의 다른 Feature와는 유사도가 낮은 경우를 의미한다.
* 즉, A와 B가 서로 "고유하게" 잘 대응되는 경우가 좋은 매칭이다.

#### 3). 좋은 매칭의 판별 기준: NNDR(Nearest Neighbor Distance Ratio)

* **NNDR(최근접 이웃 거리 비율)**
  * 한 Feature의 가장 가까운 이웃(1st)과 두 번째로 가까운 이웃(2nd) 간의 거리 비율을 계산한다.
  * 이 비율이 낮을수록(즉, 1st와 2nd의 차이가 클수록) 매칭의 신뢰도가 높다고 판단한다.
  * 일반적으로 NNDR이 임계값(예: 0.7)보다 낮으면 좋은 매칭으로 간주한다.

---
