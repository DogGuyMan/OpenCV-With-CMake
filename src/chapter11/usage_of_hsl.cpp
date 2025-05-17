#include "usage_of_hsl.hpp"

// 제네릭 포인터(Generic Pointer)  void* userdata
void chapter11::onMouse(int event, int x, int y, int flags, void* userData) {
    bool * isOnceClicked = reinterpret_cast<bool*>(userData);

    if(event == cv::EVENT_LBUTTONDOWN) {
        *isOnceClicked = true;
    }
}

void chapter11::WaitForMouseInput(const string& windowName, void* isOnceClickedFlags) {
    bool IsOnceClicked = reinterpret_cast<bool*>(isOnceClickedFlags);
    setMouseCallback(windowName, onMouse, &IsOnceClicked);
}

int chapter11::UsageOfHSL() {
    Mat image = imread("./resources/colorful.jpeg");
    double aspect_ratio = (double)image.cols/ image.rows;
    resize(image, image, Size(), 0.25, 0.25);
    Mat HSV, intensity_change, mask_out, change_color;
    vector<Mat> splited_intensity_change(3);
    vector<Mat> splited_mask_out(3);
    vector<Mat> splited_change_color(3);

    int rows = image.rows;
    int cols = image.cols;

    cvtColor(image, HSV, COLOR_BGR2HSV);

    // 1
    split(HSV, splited_intensity_change);
    equalizeHist(splited_intensity_change[2], splited_intensity_change[2]);

    // 2
    uchar *hue, *saturate, *intensity_value;
    split(HSV, splited_mask_out);
    for(int i = 0; i < rows; i++) {
        hue      = splited_mask_out[0].ptr<uchar>(i);
        saturate = splited_mask_out[1].ptr<uchar>(i);
        for(int j = 0; j < cols; j++) {
            if(hue[j] > 9 && hue[j] < 23) continue;
            saturate[j] = 0;
        }
    }

    // 3
    hue = nullptr, saturate = nullptr, intensity_value = nullptr;
    split(HSV, splited_change_color);
    for(int i = 0; i < rows; i++) {
        hue      = splited_change_color[0].ptr<uchar>(i);
        saturate = splited_change_color[0].ptr<uchar>(i);
        // 50만큼 Hue 각도를 틀것.
        for(int j = 0; j < cols; j++) {
            if(hue[j] + 50 > 255) // 만약 255를 (한바퀴 각도)를 돌았다면 다시 0부터 시작
                hue[j] = hue[j] + 50 - 255;
            else
                hue[j] += 50;
        }
    }

    // Draw
    merge(splited_intensity_change, intensity_change);
    merge(splited_mask_out, mask_out);
    merge(splited_change_color, change_color);

    cvtColor(intensity_change   ,intensity_change  ,COLOR_HSV2BGR);
    cvtColor(mask_out           ,mask_out          ,COLOR_HSV2BGR);
    cvtColor(change_color       ,change_color      ,COLOR_HSV2BGR);

    const string ORIGINAL_WINDOW_NAME = "original image";
    const string IN_CHANGE_WINDOW_NAME = "intensity change image";
    const string MASK_OUT_WINDOW_NAME = "mask out image";
    const string COLOR_CHANGE_WINDOW_NAME = "color change image";

    imshow(ORIGINAL_WINDOW_NAME     ,image);
    imshow(IN_CHANGE_WINDOW_NAME    ,intensity_change);
    imshow(MASK_OUT_WINDOW_NAME     ,mask_out);
    imshow(COLOR_CHANGE_WINDOW_NAME ,change_color);

    bool isOnceClicked[4] = {false,};
    WaitForMouseInput(ORIGINAL_WINDOW_NAME,     &isOnceClicked[0]);
    WaitForMouseInput(IN_CHANGE_WINDOW_NAME,    &isOnceClicked[1]);
    WaitForMouseInput(MASK_OUT_WINDOW_NAME,     &isOnceClicked[2]);
    WaitForMouseInput(COLOR_CHANGE_WINDOW_NAME, &isOnceClicked[3]);

    while(true) {
        if(any_of(isOnceClicked + 0, isOnceClicked + 4, [](bool flag) {return flag;}))
            break;
        waitKey(10);
    }

    return 1;
}
