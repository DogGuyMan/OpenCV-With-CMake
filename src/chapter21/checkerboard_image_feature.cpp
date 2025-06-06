#include "checkerboard_image_feature.hpp"
#define DEBUG 1
using namespace std;
using namespace cv;

static void onMouse(int event, int x, int y, int flags, void* userData) {
    chapter21::MouseParams* mp = reinterpret_cast<chapter21::MouseParams*>(userData);
    if(mp->isMask == true) return; // 이미 마스크가 설정된 경우, 아무 작업도 하지 않음
    if(event == EVENT_LBUTTONDOWN && mp->input.size() < 4) {
        // 컨투어를 통해 마스크 생성
        cout << "Mouse Clicked at: " << x << ", " << y << endl;
        mp->input.push_back(Point(x, y));
        if(mp->input.size() == 4) {
            Mat mask = Mat::zeros(mp->size, CV_8UC1); // 마스크 생성 (8비트 단일 채널)

            // fillPoly를 사용하여 다각형 영역 채우기
            fillPoly(mask, vector<vector<Point>>({mp->input}), Scalar(255));
            mask.copyTo(mp->mask); // 마스크를 저장
#if (DEBUG == 1)
            imshow(mp->windowName+" Mask", mp->mask); // 마스크 이미지 출력
            mp->isMask = true; // 마스크가 설정되었음을 표시
#endif
        }
    }
    if(event == EVENT_RBUTTONDOWN) {
        // 마우스 우클릭시 입력된 좌표 초기화
        cout << "Mouse Right Clicked, clearing input." << endl;
        mp->input.clear();
        mp->mask = Mat::zeros(mp->size, CV_8UC1); // 마스크 초기화
    }
}

int chapter21::CheckerBoardImageFeature() {
    Mat queryImage, destImage, descriptor1, descriptor2;
    Ptr<ORB> orbF = ORB::create(1000);
    vector<KeyPoint> keypoints1, keypoints2;
    vector<vector<DMatch>> matches;
    vector<DMatch> goodMatches;

    BFMatcher matcher(NORM_HAMMING); // NORM_HAMMING2는 WTA_K=3,4일 때 사용

    Mat imgMatches, H; // 매칭되는 결과 // H는 뭔지 모르겠다.
    vector<Point2f> obj, scene; // 매칭된 키포인트의 좌표를 저장할 벡터
    vector<Point2f> objP(4), sceneP(4); // 매칭된 객체와 장면의 4개의 점들
    float nndrRatio = 0.7f; // Nearest Neighbor Distance Ratio

    // 이미지 A (Query) B (Image) 불러오기
    queryImage = imread("./resources/checker_a.jpg", IMREAD_GRAYSCALE);
    destImage = imread("./resources/checker_b.jpg", IMREAD_GRAYSCALE);

    // ORB 진행
    // KeyPoint 추출
    resize(queryImage, queryImage, Size(640, 480));
    resize(destImage, destImage, Size(640, 480));

    threshold(queryImage, queryImage, 200, 255, THRESH_OTSU);
    threshold(destImage, destImage, 200, 255, THRESH_OTSU);

    chapter21::MouseParams dataQuery, dataDest; // 마우스 이벤트를 위한 파라미터 구조체
    dataQuery.size = Size(640, 480);
    dataQuery.windowName = "Feature Query";
    dataDest.size = Size(640, 480);
    dataDest.windowName = "Feature Dest";

    imshow(dataQuery.windowName, queryImage); // 이미지 출력
    imshow(dataDest.windowName, destImage); // 이미지 출력

    setMouseCallback(dataQuery.windowName, onMouse, (void*)&dataQuery); // 마우스 콜백 설정
    setMouseCallback(dataDest.windowName, onMouse, (void*)&dataDest); // 마우스 콜백 설정

    while(dataQuery.isMask == false || dataDest.isMask == false) {
        waitKey(33);
    }

    cout << "Mask set for both images." << endl;

    // 마스크를 사용하여 ORB 특징 추출
    orbF->detectAndCompute(queryImage, dataQuery.mask, keypoints1, descriptor1); // Query 이미지 전체에서 특징 추출
    orbF->detectAndCompute(destImage, dataDest.mask, keypoints2, descriptor2); // Target 이미지에서 마스크 영역만 특징 추출

    // KNN 매칭
    int k = 2; // KNN 매칭에서 k값 설정
    matcher.knnMatch(descriptor1, descriptor2, matches, k); // KNN 매칭 진행

    // Matches 가져오기
    // 그중 good matches만 추출
    // nndr 스레숄딩 진행후, goodMatched 넣기.
    for(auto& match : matches) {
        if(match.size() == 2 && match[0].distance <= nndrRatio * match[1].distance) {
            goodMatches.push_back(match[0]); // 좋은 매칭만 추출
        }
    }

    // 투영 행렬 탐색
    for(auto& goodMatch : goodMatches) {
        obj.push_back(keypoints1[goodMatch.queryIdx].pt); // Query 이미지의 키포인트 좌표
        scene.push_back(keypoints2[goodMatch.trainIdx].pt); // Image 이미지의 키포인트 좌표
    }

    H = findHomography(obj, scene, RANSAC); // RANSAC을 이용한 투영 행렬(호모그래피) 계산

    // 매칭 결과를 시각화하기 위한 이미지 생성
    drawMatches(queryImage, keypoints1, destImage, keypoints2, goodMatches, imgMatches);

    // 시계 방향으로 좌표계 형성
    objP = {
        Point2f(0, 0), // 2 사분면
        Point2f(queryImage.cols, 0), // 1 사분면
        Point2f(queryImage.cols, queryImage.rows), // 4 사분면
        Point2f(0, queryImage.rows) // 3 사분면
    };

    perspectiveTransform(objP, sceneP, H); // 호모그래피 행렬을 이용하여 좌표 변환

    for(int i = 0; i < 4; i++) sceneP[i] += Point2f(queryImage.cols, 0); // sceneP 좌표를 query 이미지의 너비만큼 이동
    for(int i = 0; i < 4; i++) line(imgMatches, sceneP[i], sceneP[(i + 1) % 4], Scalar(0, 255, 0), 2); // 변환된 좌표를 이용하여 이미지에 사각형 그리기

    imshow("Image Matches", imgMatches); // 매칭된 이미지 출력
    waitKey();
    return 1;
}
