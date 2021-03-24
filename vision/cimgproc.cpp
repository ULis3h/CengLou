#include "cimgproc.h"



CImgproc::CImgproc()
{

}

void CImgproc::detectFace(Mat &img, CascadeClassifier &cascade, CascadeClassifier &nestedCascade, double scale, bool tryflip)
{
    String face_cascade_name = "/home/ubuntu/opencv-3.4.1/data/haarcascades/haarcascade_frontalface_default.xml";

    String eyes_cascade_name = "/home/ubuntu/opencv-3.4.1/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";

    CascadeClassifier face_cascade; //定义人脸分类器
    CascadeClassifier eyes_cascade; //定义人眼分类器
    String window_name = "Capture - Face detection";

    face_cascade.load(face_cascade_name);
    eyes_cascade.load(eyes_cascade_name);

    std::vector<Rect> faces;
    Mat frame_gray = img;
    //cvtColor(img, frame_gray, COLOR_BGR2GRAY);

    equalizeHist(frame_gray, frame_gray);
    //-- Detect faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 3, CV_HAAR_DO_ROUGH_SEARCH, Size(70, 70),Size(100,100));

    for (size_t i = 0; i < faces.size(); i++)
    { //Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        //ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
        rectangle(img, faces[i],Scalar(255,0,0),2,8,0);
        Mat faceROI = frame_gray(faces[i]); std::vector<Rect> eyes;

        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 1, CV_HAAR_DO_ROUGH_SEARCH, Size(3, 3));

        for (size_t j = 0; j < eyes.size(); j++)
        {
            Rect rect(faces[i].x + eyes[j].x, faces[i].y + eyes[j].y, eyes[j].width, eyes[j].height);
            //Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
            //int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
            //circle(frame, eye_center, radius, Scalar(255, 0, 0), 4, 8, 0);
            rectangle(img, rect, Scalar(0, 255, 0), 2, 8, 0);
        }
    }
    //-- Show what you got
    namedWindow(window_name, 2);
    imshow(window_name, img);
}
