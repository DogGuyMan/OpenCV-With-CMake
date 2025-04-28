<img src="image/2025-04-27-02-37-58.png" width=49%>
<img src="image/2025-04-27-02-38-06.png" width=49%>
<img src="image/2025-04-27-02-39-06.png" width=49%>
<img src="image/2025-04-27-02-39-45.png" width=49%>
<img src="image/2025-04-27-02-40-12.png" width=49%>
<img src="image/2025-04-27-02-40-28.png" width=49%>

## Morphological Operation

#### 배경 제거가 끝났다, 따라서 객체를 이제 추정할 수 있는데. 그 결과를 바로 쓰기에는 부족하다.

> ### 📄 Erosion & Dilation

#### 1). Erosion

**Erosion of A By B**

* Erosion은 이진화 이미지를 축소시키거나 얇게 만들어 준다.

#### 2). Dilation

**Dilation of A By B**

* Dilation은 이진화 이미지를 키우거나, 굵게 만들어 준다.

> ### 📄 Opening & Closing

#### 1). Opening

**Erosion of A By B** 를 의미하고, 벽을 허물어 주는 효과라는 점에서 "오프닝"이라고 하는 것 같다.
* 컨투어를 부드럽게 만들어 주고, 지협(두개의 몸체나 엽사이를 연결하는 좁은 부위)를 허물어 주고,
날카로운 피크나, 동떨어진 섬과 같은 점을 제거한다.

#### 2). Closing

**Dilation of A By B**
* 마찬가지로 컨투어를 부드럽게 만들고, 지협을 매꿔준다, 즉, 작은 구멍을 하얀색으로 매꿔준다.
