#include "perspective_transformation.hpp"
#define DEBUG 1

using namespace cv;
using namespace std;

static void onMouse(int event, int x, int y, int flags, void* userData) {
    chapter20::MouseParams* mp = reinterpret_cast<chapter20::MouseParams*>(userData);
    Mat img = mp->img;

    if(event == EVENT_LBUTTONDOWN && mp->input.size() < 4) {
        Mat result;

#if (DEBUG == 1)
        cout << "Mouse Clicked at: " << x << ", " << y << endl;
#endif

        // 2 1 4 3 사분면으로 시계방향으로 기입.
        mp->input.push_back(Point2f(x, y));

        if(mp->input.size() == 4) {
            Mat homo_mat = getPerspectiveTransform(mp->input, mp->output);
            // Homograph 행렬을 이용한 warp
            warpPerspective(img, result, homo_mat, Size(200,200));
            imshow(chapter20::OUTPUT_WINDOW, result);
        }
        if(mp->input.size() <= 4) {

#if (DEBUG == 1)
            cout << "input count: " << mp->input.size() << endl;
#endif
            result = img.clone();
            for(size_t i = 0; i < mp->input.size(); i++) {
                circle(result, mp->input[i], 3, Scalar(0,0,255), 5);
            }
            imshow(chapter20::INPUT_WINDOW, result);
        }
    }
    if(event == EVENT_RBUTTONDOWN) {
        // 우클릭시 리셋
        mp->input.clear();
        imshow(chapter20::INPUT_WINDOW, img);
    }
}

int chapter20::PerspectiveTransformation() {
    Mat input = imread("./resources/board7.png");
    Mat input_with_margin;
    int top = 50, bottom = 50, left = 50, right = 50;
    copyMakeBorder(input, input_with_margin, top, bottom, left, right, BORDER_CONSTANT);
    imshow(chapter20::INPUT_WINDOW, input_with_margin);

    chapter20::MouseParams mp;
    mp.output.push_back(Point2f(0, 0));
    mp.output.push_back(Point2f(200, 0));
    mp.output.push_back(Point2f(200, 200));
    mp.output.push_back(Point2f(0, 200));
    mp.img = input_with_margin;

    setMouseCallback(chapter20::INPUT_WINDOW, onMouse, (void*)&mp);
    waitKey();
    return 1;
}
