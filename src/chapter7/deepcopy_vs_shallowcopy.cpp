#include "deepcopy_vs_shallowcopy.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace cv;

/*
original m1 =
   [1, 2, 3;
    4, 5, 6;
    7, 8, 9]

update pixel

original m1 =
   [100, 2, 3;
    4, 5, 6;
    7, 8, 9]

shallow m1 =
   [100, 2, 3;
    4, 5, 6;
    7, 8, 9]

deep m1 =
   [1, 2, 3;
    4, 5, 6;
    7, 8, 9]
*/

// (Mat_<double>(3,3) << 1,2,3,4,5,6,7,8,9);
// m1.clone();
void DebugMat(string title, Mat& mat) {
    cout << title << "=" << endl;
    cout << setw(4) << mat << endl;
    cout << endl;
}
int chapter7::DeepCopyVsShallowCopy() {
    Mat m1 = (Mat_<double>(3,3) << 1,2,3,4,5,6,7,8,9); // Mat_ ???
    Mat m_shallow = m1;
    Mat m_deep = m1.clone();

    // 원본 매트릭스 출력
    DebugMat("original m1", m1);
    // 매트릭스 수정
    m1.at<double>(0, 0) = 100; // 원본 수정
    cout << "Update Matrix = " << "m1.at<double>(0, 0) = 100" << endl;
    cout << endl;
    // 원본 매트릭스 출력
    DebugMat("original m1", m1);
    // 얕은 복사 매트릭스 출력
    DebugMat("shallow m1", m_shallow);
    // 원본 매트릭스 출력
    DebugMat("deep m1", m_deep);

    waitKey(0);
    return 1;
}
