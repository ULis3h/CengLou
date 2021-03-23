#include "cgetimg.h"

int main()
{
    CGetimg gImg;
    cv::Mat a;
    gImg.getImgFromIndCam(a);
    return 0;
}
