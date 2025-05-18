#include "baisic_data_structure_in_openCV.hpp"
using namespace cv;
using namespace std;

namespace chapter4 {
    int BaisicDataStructureInOpenCV() {
        int w = 150, h = 100;
        // 만약 pixelType 이 3 channel이라면 Scaler(double, double, double) 형태이다.
        // 🚸 Scalar(255,0,0); 는 RGB 순서일 것 같지만.. 사실 BGR 순서로 거꾸로다! 🚸
        Mat image(h, w, CV_8UC1, Scalar(255));

        cout << "Szie: " << image.size().height << "," << image.size().width << endl;
        // imgshow : 해당 매트릭스에 해당하는 이미지를 보여준다.
        imshow("image", image);

        waitKey(0);
        return 0;
    }
}
