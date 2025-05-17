#include "face_detection.hpp"

using namespace std;
using namespace cv;

int chapter17::FaceDetection() {
    // 비얼굴 영역 제저기 -> 그렇게 함으로 살아남은 얼굴만 판단
    // 각 강한 분류기 내 약한 분류기의 수는 3 > 2 > 1 순으로 줄어든다.
    // 초반 단계: 계산이 매우 빠르고, 얼굴이 아닌 영역을 대량으로 제거(거짓 음성은 허용, 거짓 양성은 최소화)
    // 후반 단계: 더 복잡한 분류기를 사용해 남은 영역을 정밀하게 판별
    CascadeClassifier face_classifier;
    Mat frame, grayFrame;
    vector<Rect> faces;

    VideoCapture cap(0);
    if(!cap.isOpened()) {
        cout << "카메라를 찾을 수 없습니다." << endl;
        return -1;
    }

    // 이 XML 파일에 들어있는 내용은 정멸 얼굴을 검출하기 위해 필요한 학습 결과 파일이라고 생각하면 된다.
    face_classifier.load("./resources/haarcascade_frontalface_alt.xml");

    while(true) {
        cap >> frame;
        cvtColor(frame, grayFrame, COLOR_BGR2GRAY);

        face_classifier.detectMultiScale(
            grayFrame,      // 입력 이미지
            faces,          // 검출된 얼굴 영역 저장
            1.1,            // 얼굴을 찾을떄, Feature 크기 조절 비율을 조절하는 값으로,
                                    // "값이 작으면, 더 많은 얼굴을 찾을 수 있음/ 하지만 오탐지 또한 많아짐",
                                    // "값이 커지면, 속도와 오탐지가 줄어들고 빨라지지만, 작은 얼굴을 놓질 수 있음"
            3,              // 얼굴을 찾을때, 겹치는 사각형(검출 결과)가 몇개 이상이여야 하는지 결정
                                    // "값이 작으면 : 느슨하게 얼굴로 인지 해서 얼굴 검출결과가 많아지고, 이떄문에 오탐지가 많아짐"
                                    // "값이 커지면 : 더 많이 겹쳐야 얼굴로 인지해서 좀 더 빡빡하다, 하지만 진짜 얼굴을 놓질수도 있음"
            0,              //
            Size(30, 30)    // 얼굴을 찾을떄 최소 픽셀 크기,이보다 작은 얼굴을 무시
        );

        for(int i= 0; i < faces.size(); i++) {
            Point topRight(faces[i].x, faces[i].y);
            Point leftBottom = topRight + Point(faces[i].width, faces[i].height);
            rectangle(frame, leftBottom, topRight, Scalar(0, 255, 0), 3, 4, 0);
        }

        imshow("Face Detection", frame);
        if(waitKey(33) >= 27) break;
    }

    return 0;
}
