#include "perspective_transformation.hpp"

using namespace cv;
using namespace std;


static void onMouse(int event, int x, int y, int flags, void* userData) {
    chapter20::MouseParams* mp = reinterpret_cast<chapter20::MouseParams*>(userData);
    Mat img = mp->img;

    if(event == EVENT_LBUTTONDOWN) {
        Mat result;

        // 2 1 4 3 사분면으로 시계방향으로 기입.
        mp->input.push_back(Point2f(x, y));

        if(mp->input.size() == 4) {
            Mat homo_mat = getPerspectiveTransform(mp->input, mp->output);
            // Homograph 행렬을 이용한 warp
            warpPerspective(img, result, homo_mat, Size(200,200));
            imshow("Output", result);
        }
        else {
            result = img.clone();
            for(size_t i = 0; i < mp->input.size(); i++) {
                circle(result, mp->input[i], 3, Scalar(0,0,255), 5);
            }
            imshow("input", result);
        }
    }
    if(event == EVENT_RBUTTONDOWN) {
        // 우클릭시 리셋
        mp->input.clear();
        imshow("input", img);
    }
}

int chapter20::PerspectiveTransformation() {
    Mat input = imread("");
    imshow("Input", input);

    chapter20::MouseParams mp;
    mp.output.push_back(Point2f(0, 0));
    mp.output.push_back(Point2f(200, 0));
    mp.output.push_back(Point2f(200, 200));
    mp.output.push_back(Point2f(0, 200));
    mp.img = input;

    setMouseCallback("input", onMouse, (void*)&mp);
    waitKey();
    return 1;
}
