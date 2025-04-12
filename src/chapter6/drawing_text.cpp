#include "drawing_text.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace std;
using namespace cv;

int chapter6::DrawingText() {
    Mat image = Mat::zeros(400, 600, CV_8UC3);

    int w = image.cols, h = image.rows;
    putText(image, format("width : %d, height : %d", w, h), Point(50, 80),
        FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200,200), 4
    );

    imshow("text on image", image);
    waitKey(0);
    return 0;
}

int chapter6::DrawingDateTime() {
    // 화면에 표시할 빈 이미지 생성
    Mat canvas(400, 600, CV_8UC3, Scalar(30, 30, 30));
    const double fps = 30;
    // 창 생성
    namedWindow("Timer", WINDOW_AUTOSIZE);

    while (true) {
        // 이미지 초기화
        canvas.setTo(Scalar(30, 30, 30));

        // 현재 시간 측정
        // time_t로 변환하여 tm 구조체 생성
        auto now = chrono::system_clock::now();
        time_t now_time_t = chrono::system_clock::to_time_t(now);
        tm now_tm = *localtime(&now_time_t);
        auto duration = now.time_since_epoch();

        // 시간 문자열 생성 (예: "Time: 123456789 ms")
        auto ms = chrono::duration_cast<chrono::milliseconds>(duration).count() % 1000;
        ostringstream time_text_ss;
        time_text_ss << put_time(&now_tm, "%Y-%m-%d %H:%M:%S")
        << '.' << setfill('0') << setw(3) << ms;

        string text = time_text_ss.str();

        // 가변 가로 세로 텍스트 사이즈 구하기
        Size textSize = getTextSize(text, FONT_HERSHEY_SIMPLEX, 1.0, 2, 0);

        // 텍스트 위치 계산 (이미지 중앙)
        Point textOrg((canvas.cols - textSize.width) / 2,
                      (canvas.rows + textSize.height) / 2);

        // 텍스트 출력
        putText(canvas, time_text_ss.str(), textOrg,
                    FONT_HERSHEY_SIMPLEX, 1.0,
                    Scalar(0, 255, 0), 2);

        // 이미지 표시
        imshow("Timer", canvas);

        // 키 입력 대기 (1ms)
        int key = waitKey(1000 / fps);
        if (key == 13 || key == 32) { // Enter(13) 또는 Space(32) 키
            break;
        }
    }

    destroyAllWindows();
    return 0;
}
