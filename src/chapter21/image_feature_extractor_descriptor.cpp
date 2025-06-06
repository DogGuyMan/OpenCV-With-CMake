#include "image_feature_extractor_descriptor.hpp"

using namespace cv;
using namespace std;

int chapter21::ImageFeatureExtractorDescriptor() {
    Mat query_image, dest_image;
    Mat descriptor1, descriptor2;

    Ptr<ORB> orbF = ORB::create(1000); // ORB 특징 추출기 생성

    vector<KeyPoint> keypoints1, keypoints2; // 첫 번째와 두 번째 이미지의 키포인트들
    vector<vector<DMatch>> matches; // 매칭된 특징점들
    vector<DMatch> goodMatches; // 좋은 매칭만 추출

    BFMatcher matcher(NORM_HAMMING); // Brute Force 매처 생성

    Mat image_matches;
    Mat H; // H 호모 그래피

    vector<Point2f> obj, scene; // 특징점 좌표
    vector<Point2f> objP(4), sceneP(4); // ?

    float nndrRatio = 0.6f;

    query_image = imread("./resources/art_a.png");
    dest_image = imread("./resources/art_b.png");

    resize(query_image, query_image, Size(640, 480));
    resize(dest_image, dest_image, Size(640, 480));

    orbF->detectAndCompute(query_image, noArray(), keypoints1, descriptor1);
    orbF->detectAndCompute(dest_image, noArray(), keypoints2, descriptor2);

    int k = 2;
    matcher.knnMatch(descriptor1, descriptor2, matches, k); // 두 discriptor 간 아까 만들었던 Brute Force 매처인 "matcher"를 사용해서 매칭 진행
                                                            // 결과는 DMatch의 매칭된 특징점들 first match, second match... N matches의 배열로 이뤄진 것을 얻을 수 있다.
                                                            // 그리고 first match, second match... N matches중에서 Best match를 찾는게 목표다.

    // nndrRatio를 사용하여 스레숄딩 한다.
    for(vector<DMatch> match : matches) {
        if(match.size() < 2) continue;
        // 오! 이거 괜찮은 트릭인것이. 이것을 nndrRatio값을 남기고 식을 전개하면
        // match[0].distance / match[1].distance <= nndrRatio 와 동일하다.
        // 그런데 이렇게 조건문을 작성한 이유는 나눗셈은 float point로, 어쩔수 없이 값이 손실되는 문제가 생기고 말 것이다.
        // 따라서 이런식으로 sqrt(int) < N 이러한 식 또한, int < N * N 형태로 바꿔서 비교하는 것이 좋다.
        DMatch& firstMatch = match[0];
        DMatch& secondMatch = match[1];
        if(firstMatch.distance <= nndrRatio * secondMatch.distance)
        {
            goodMatches.push_back(match[0]);
        }
    }

    // Draw Matching
    drawMatches(query_image, keypoints1, dest_image, keypoints2, goodMatches, image_matches,
                Scalar::all(-1), Scalar(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    // 호모그래피 계산
    if(goodMatches.size() < 4) {cout << "Not enough matches found." << endl; return 0; }

    for(DMatch& goodMatch : goodMatches) {
        obj.push_back(keypoints1[goodMatch.queryIdx].pt);
        scene.push_back(keypoints2[goodMatch.trainIdx].pt);
    }

    H = findHomography(obj, scene, RANSAC);
    objP = {
        Point2f(0, 0),
        Point2f(query_image.cols, 0),
        Point2f(query_image.cols, query_image.rows),
        Point2f(0, query_image.rows)
    };

    perspectiveTransform(objP, sceneP, H);

    for(int i = 0; i < 4; i++)
    sceneP[i] += Point2f(query_image.cols, 0);

    for(int i = 0; i < 4; i++)
        line(image_matches, sceneP[i], sceneP[(i+1) % 4], Scalar(0, 255, 0), 4);

    imshow("image matches", image_matches);
    waitKey();

    return 1;
}
