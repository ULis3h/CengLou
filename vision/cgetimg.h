#ifndef CGETIMG_H
#define CGETIMG_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/fairsioncamera.h"
#include<opencv2/opencv.hpp>

using namespace std;
using namespace FAIRSIONCAMERA_API;
using namespace cv;



class CGetimg
{
public:
    CGetimg();
    ~CGetimg();

public:
    int getImgFromIndCam(cv::Mat &mat);
    int getImgFromBaseCam();
    int getImgFromImg();

};

#endif // CGETIMG_H
