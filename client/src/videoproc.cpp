#include "videoproc.h"
#include <opencv2/opencv.hpp>
using namespace cv;

videoproc::videoproc()
{
    //####测试
    cv::Mat src = cv::imread("C:\\Users\\Mypc\\Desktop\\timg.jpg");
    imshow("test",src);
    waitKey(0);
    //#####
}
