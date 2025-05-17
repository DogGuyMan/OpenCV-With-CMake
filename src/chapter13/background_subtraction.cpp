#include "background_subtraction.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace cv;

int chapter13::MeanFilterSubtraction() {
    Mat frame, sum, avg;
    VideoCapture capture;
    if(capture.open("./resources/vtest.avi") == false) return -1;
    double fps = capture.get(CAP_PROP_FPS);
    int total_frames = capture.get(CAP_PROP_FRAME_COUNT);
    int cnt = 2;
    capture >> avg;

    for(int i = 0; i < 100; i++) {
        if (!capture.read(frame) || frame.empty()) break;
        add((frame / cnt), (avg * (cnt-1)) / cnt, avg);
        cnt++;
        cout << i << "/100" << '\n';
    }
    capture.release();
    imshow("avg background", avg);
    // avg background 이미지를 PNG 파일로 저장
    imwrite("./resources/vtest_avg_background.png", avg);
    waitKey(0);
    return 1;
}

uchar static GetMedianWithVector(vector<uchar>& v) {
    nth_element(v.begin(), v.begin() + (v.size() / 2), v.end());
    return v[v.size() / 2];
}

int chapter13::MedianFilterSubtraction() {
    /* Video Capture 열기 */
    VideoCapture cap("./resources/vtest.avi");

    Mat frame;
    vector<Mat> frames;

    for(int i = 0; i < 100; ++i) {
        cap >> frame;
        frames.push_back(frame.clone());
        cout << i << "/100" << '\n';
    }

    Size img_size = frames[0].size();
    cap.release();
    Mat background(img_size, frame.type());

    vector<uchar> pixels_by_times[3];
    pixels_by_times[0].reserve(100);
    pixels_by_times[1].reserve(100);
    pixels_by_times[2].reserve(100);

    for(int y = 0; y < img_size.height; ++y) {
        for(int x = 0; x < img_size.width; ++x) {
            Vec3b medianPixel;
            pixels_by_times[0].clear();
            pixels_by_times[1].clear();
            pixels_by_times[2].clear();

            for(auto& f : frames) {
                Vec3b pixel = f.at<Vec3b>(y, x);
                pixels_by_times[0].push_back(pixel[0]);
                pixels_by_times[1].push_back(pixel[1]);
                pixels_by_times[2].push_back(pixel[2]);
            }

            medianPixel = {
                GetMedianWithVector(pixels_by_times[0]),
                GetMedianWithVector(pixels_by_times[1]),
                GetMedianWithVector(pixels_by_times[2])
            };

            background.at<Vec3b>(y, x) = medianPixel;
        }
    }

    imshow("median Background", background);
    // median background 이미지를 PNG 파일로 저장
    // imwrite("./resources/vtest_median_background.png", background);

    waitKey(0);
    return 1;
}

int chapter13::AbsDiffSubtraction() {
    Mat background, frame, gray, result, foregroundMask, foregroundImg;
    VideoCapture capture;
    if(capture.open("./resources/vtest.avi") == false) return -1;
    double fps = capture.get(CAP_PROP_FPS);
    int total_frames = capture.get(CAP_PROP_FRAME_COUNT);

    /* 배경 프레임 캡쳐 */
    background = imread("./resources/vtest_real_background.png");

    /* 배경 프레임을 그레이 스케일로 변환 */
    cvtColor(background, background, COLOR_BGR2GRAY);

    while(true) {
        // capture.grab() -> capture.retrieve(frame)

        /* Grabs the next frame from video file or capturing device. */
        /* 내부적으로 비디오 스트림에서 다음 프레임을 읽어와 버퍼에 저장만 하고, */
        if(capture.grab() == 0) break;

        /* retrieve()는 그 버퍼에서 실제로 이미지를 "회수"해서 Mat 객체로 반환합니다. */
        /* 이런 맥락에서 "retrieve"라는 단어는 "이미 준비된(획득된) 데이터를 실제로 받아온다"는 의미로 채택된 것으로 보임. */
        capture.retrieve(frame);

        /* 프레임을 그레이 스케일로 변환 */
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        /* 프레임과 배경 프레임의 차이를 계산 */
        absdiff(gray, background, foregroundMask);
        threshold(foregroundMask, foregroundMask, 50, 255, THRESH_BINARY);

        /* foregroundMask.copyTo(foregroundImg)를 써야하는것이, 그렇지 않으면 foregroundMask가 계속 쌓여서 잔상이 생김*/
        foregroundMask.copyTo(foregroundImg);

        /* Copies the matrix to another one */
        // foregroundMask를 마스크로 사용해
        // gray된 원본 프레임을 마스킹하여
        // foregroundImg란 검열된 프레임을 만든다.
        gray.copyTo(foregroundImg, foregroundMask);

        imshow("foregroundImg", foregroundImg);
        imshow("foregroundMask", foregroundMask);
        imshow("background", background);

        if(waitKey(1000 / fps) == 32) {break;}
    }
    capture.release();
    destroyAllWindows();
    return 1;
}

int chapter13::MoG2ModelSubtraction() {
    Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2();
    Mat image, foregroundMask, background, foregroundImg;

    VideoCapture cap("./resources/vtest.avi");

    while(true) {
        cap >> image;
        resize(image, image, Size(640, 480));

        if(foregroundMask.empty())
            foregroundMask.create(image.size(), image.type());

        bg_model->apply(image, foregroundMask);
        GaussianBlur(foregroundMask, foregroundMask, Size(11,11), 3.5, 3.5);

        threshold(foregroundMask, foregroundMask, 10, 255, THRESH_BINARY);

        foregroundImg = Scalar::all(0);

        image.copyTo(foregroundImg, foregroundMask);
        bg_model->getBackgroundImage(background);

        imshow("foregroundImg", foregroundImg);
        imshow("foregroundMask", foregroundMask);
        imshow("background", background);
        if(!background.empty()) {
            imshow("background", background);
        }
        if(waitKey(33) == 32) {break;}
    }
    cap.release();
    destroyAllWindows();
    return 1;
}
