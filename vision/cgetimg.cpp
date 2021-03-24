#include "cgetimg.h"
#include "cimgproc.h"

CGetimg::CGetimg()
{

}
CGetimg::~CGetimg()
{

}

int CGetimg::getImgFromIndCam(cv::Mat &mat)
{
    long nCameraCount = 0;
    long nRel                      = -1;
    long nWidth                    =  0;
    long nHeight                   =  0;
    long nFrames                   =  0;

    unsigned char  *pBuffer        = NULL;
    ICamera        *pCamera        = NULL;
    IDeviceManager *pDeviceManager = new IDeviceManager();
    if(NULL == pDeviceManager)
    {
            printf("create device manager failed!\r\n");
            return -1;
    }

    // Init
    pDeviceManager->Initialize();
   // pCamera->AutoBalance();

    // Get online camera count
    nCameraCount = pDeviceManager->GetCameraCount(2000);
    printf("A total of %d cameras are online!\r\n ", nCameraCount);

    if(nCameraCount > 0)
    {
            do
            {
                    // Get first camera on camera list
                    pCamera = pDeviceManager->GetCamera(0);

                    if(pCamera)
                    {
                            printf("First camera name is %s,  user name is %s, serial number is %s\r\n",
                            pCamera->GetDeviceInfo()->GetModelName(),
                            pCamera->GetDeviceInfo()->GetUserID(),
                            pCamera->GetDeviceInfo()->GetSerialNumber());

                            // Open camera
                            nRel = pCamera->Open();
                            if(0 != nRel)
                            {
                                    printf("Open camera failed!\r\n");
                                    break;
                            }

                pCamera->SetValue("GevSCPSPacketSize", 1500);
                pCamera->SetValue("InterPacketDelay", 4000);

                            // Get image width and height
                            nWidth = pCamera->GetValue("Width");
                            nHeight = pCamera->GetValue("Height");
                            printf("camera resolution is %ld x %ld \r\n", nWidth, nHeight);
                            pBuffer = new unsigned char[nWidth*nHeight];

                            // Set Trans mode
                            nRel = pCamera->SetTransMode(TRANS_Continuous);

                            // Start capture
                            nRel = pCamera->StartCapture();

                            if(0 == nRel)
                            {
                                CascadeClassifier cascade, nestedCascade;
                                bool stop = false;
                                cascade.load("/home/ubuntu/opencv-3.4.1/data/haarcascades/haarcascade_frontalface_alt.xml");
                                nestedCascade.load("/home/ubuntu/opencv-3.4.1/data/haarcascades/haarcascade_eye.xml");
                                CImgproc proc;
                                    // Get Image
                                    while(true)
                                    {

                                            if(NULL != pCamera->GetBuffer(1000))
                                            {
                                                    nFrames++;
                                                    pBuffer = (unsigned char *)pCamera->GetBuffer(1000);
                                                    if(pBuffer == NULL)continue;
                                                    // GetBuffer Success
                                                    printf("Get Image success, Image Index is %ld\r\n", nFrames);
                                                    cv::Mat img(nHeight,nWidth,CV_8UC1,pBuffer);
                                                    mat = img;
                                                    proc.detectFace(img, cascade, nestedCascade,2,0);
                                                    cv::imshow("raw",img);
                                                    cv::imwrite("/home/ubuntu/test.png",img);
                                                    cv::waitKey(1);

                                                    pBuffer = NULL;

                                            }
                                    }
                                    pCamera->StopCapture();
                            }

                            // close camera
                            pCamera->Close();
                    }
            }while(false);
    }

    // Releases all fairsion resources.
    pDeviceManager->Terminate();

}

/*get KS2A17 's img*/
int CGetimg::getImgFromBaseCam()
{
    cv::VideoCapture cap;
    cap.open(0);
    if(!cap.isOpened())
    {
        cout<<"The Usb Cam Open Failed!"<<endl;
    }
    else
        cout<<"Open Usb Cam Sucess!"<<endl;

    cap.set(CV_CAP_PROP_BRIGHTNESS,50);
    cv::Mat frame;
    int count = 0;
    while(1)
    {
        count++;
        cout<<"get img ===>>"<<count<<"frame"<<endl;
        cap>>frame;
        cv::imshow("UsbImg",frame);
        if(cv::waitKey(10) >= 0)
            break;
    }

    return 0;
}

