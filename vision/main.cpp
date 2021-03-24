#include "cgetimg.h"
#include "csetting.h"

#define SETTING_FILE "./config/config.yml"

int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        cout<<"few argument!"<<endl;
        /*this should sent a single
        TODO : .....
        */
    }

    if(argv[2] == "-f")
    {
        /*TODO : jiance renlian*/
    }
    else if(argv[2] == "-a")
    {
        /*TODO for DATABASE*/
    }


    csetting m_setting(SETTING_FILE);           /*config all*/
    CGetimg gImg;
    cv::Mat a;
    /*
    three threads run
    */
    gImg.getImgFromIndCam(a);
    return 0;
}
