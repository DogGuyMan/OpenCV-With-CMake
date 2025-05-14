#include "pedestrian_detection.hpp"

using namespace std;
using namespace cv;

int chapter18::PedestrianDetection() {
    Mat frame;
    vector<Rect> found;
    int i;
    char ch;

    VideoCapture cap("./data/vtest.avi");

    if(!cap.isOpened()) {
        cout << "영상을 찾을 수 없습니다." << endl;
        return -1;
    }

    HOGDescriptor hog(
        Size(64, 128), // _winSize
                            // 주의할 것은  HOGDescriptor의 윈도우 크기와 SVM detector가 다르면 에러가 발생한다.
                            // 예를 들어 Size(48, 96)로 하면 안된다.
        Size(16, 16), // blockSize
        Size(8, 8),   // blockStride
        Size(8, 8),   // cellSize
        9             // nbins
    );

    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

    while(1) {
        cap >> frame;

        if(frame.empty()) break;

        hog.detectMultiScale(
            frame, // InputImage
            found, // found locations
            1.2, // hit Threshold
            Size(8, 8), // Padding
            Size(32,32), // WinStride
            1.05,
            6);

        for(i = 0; i < (int)found.size(); i++)
            rectangle(frame, found[i], Scalar(0, 255, 0), 2);

        imshow("Pedestrian Detection", frame);
        ch = waitKey(10);
        switch(ch) {
            case 27: {return 0;}   // ESC key
            case 32 :           // Space key
            {
                while (true) {
                    ch = waitKey(10);
                    if (ch == 32) { // Space로 재시작
                        break;
                    }
                    if (ch == 27) { // ESC로 종료
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}
