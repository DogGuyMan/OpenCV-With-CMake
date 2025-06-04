#include "image_feature_extractor_descriptor.hpp"

using namespace std;
using namespace cv;

int chapter21::ImageFeatureExtractorDescriptor() {
    Mat query, image, descriptor1, descriptor2;
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
    query = imread("./resources/imageA.jpg");
    image = imread("./resources/imageB.jpg");

    // ORB 진행
    // KeyPoint 추출
    resize(image, image, Size(640, 480));
    orbF->detectAndCompute(query, noArray(), keypoints1, descriptor1); // KeyPoint 추출 및 Descriptor 계산
    orbF->detectAndCompute(image, noArray(), keypoints2, descriptor2); // KeyPoint 추출 및 Descriptor 계산

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

    // 시계 방향으로 좌표계 형성
    objP = {
        Point2f(0, 0), // 2 사분면
        Point2f(query.cols, 0), // 1 사분면
        Point2f(query.cols, query.rows), // 4 사분면
        Point2f(0, query.rows) // 3 사분면
    };

    perspectiveTransform(objP, sceneP, H); // 호모그래피 행렬을 이용하여 좌표 변환

    for(int i = 0; i < 4; i++) sceneP[i] += Point2f(query.cols, 0); // sceneP 좌표를 query 이미지의 너비만큼 이동
    for(int i = 0; i < 4; i++) line(imgMatches, sceneP[i], sceneP[(i + 1) % 4], Scalar(0, 255, 0), 2); // 변환된 좌표를 이용하여 이미지에 사각형 그리기

    imshow("Image Matches", imgMatches); // 매칭된 이미지 출력
    return 1;
}
