#ifndef CIMGPROC_H
#define CIMGPROC_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;




class CImgproc
{
public:
    CImgproc();

public:
    void detectFace(Mat &img, CascadeClassifier &cascade,CascadeClassifier &nestedCascade, double scale, bool tryflip);
};

#endif // CIMGPROC_H
