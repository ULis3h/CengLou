#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QAction>
#include "about.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include "switchcontrol.h"
#include <QProcess>
#include <stdint.h>
#include "yawinf.h"
#include <QImageReader>
#include <QBuffer>
#include <QHostAddress>
#include <QPixmap>
#include <QUdpSocket>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace  std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_btn_openFile_clicked();

    void on_action_about_triggered();

    void on_openPort_btn_clicked();

    void on_btn_Connect_Stm32_clicked();

    void on_pushButton_left_clicked();

    void serial_Read();//串口数据读取显示

    void on_pushButton_sendData_clicked();

    void on_pushButton_clear_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_checkBox_auto_stateChanged(int arg1);

    void on_radioButton_hex_clicked(bool checked);

    void on_actionhelp_triggered();

    void on_radioButton_5_clicked();

    void on_pushButton_360_yaw_clicked();

    void on_pushButton_stop_yaw_clicked();

    void on_pushButton_right_clicked();

    void on_actionyaw_triggered();

    void on_pushButton_2_clicked();

    void recvVideoShow();  // 接收视频显示函数
    void importFrame(); // 显示网络摄像头视频

    void on_btn_Connect_Pi_clicked();

    void on_pushButton_force_add_clicked();

    void on_pushButton_force_red_clicked();

    void on_pushButton_write_img_clicked();

public:
    void Init();

public:
    QMediaPlayer *mediaPlayer;
    QVBoxLayout  *layout_video;
    QVideoWidget *videoWidget;
    QSerialPort *SerialPort;
    bool hexable;  //16进制
    bool utf8able; //utf8
    bool endable;//换行
    bool procTk1; //视屏处理机tk1 选择开关
    bool yawAuto = false; //勾选自动时候为真
    int yaw_right_angle = 0;// 记录yaw右旋按钮点击事件中角度值的变化
    bool recvModel; // 实时接收模式 1 时有效
    cv::VideoCapture cap; // OpenCV摄像机类
    Mat frame;
    QTimer *timer;

private:
    Ui::MainWindow *ui;
    about *ab;
    yawinf *yawinfWindow;
    QUdpSocket recver; // 用于接收视频的udp套接字
    QProcess *pro;


};
#endif // MAINWINDOW_H
