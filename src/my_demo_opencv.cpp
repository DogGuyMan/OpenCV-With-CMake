#include <my_demo_opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <fmt/format.h>
#include <config.hpp>

#include <iostream>

using namespace cv;
using namespace std;

int OpenCVDemo() {
    cout << "Hello " << project_name << endl;

    //! [imread]
    std::string image_path = samples::findFile("./data/starry_night.jpg");
    Mat img = imread(image_path, IMREAD_COLOR);
    //! [imread]

    //! [empty]
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    //! [empty]

    //! [imshow]
    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    //! [imshow]

    //! [imsave]
    if(k == 's')
    {
        imwrite("./data/starry_night.png", img);
    }
    //! [imsave]

    return 0;
}
