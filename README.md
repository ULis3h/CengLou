<h1 align<h1 align="center">Welcome to CengLou 👋  <img src="https://img.shields.io/badge/CengLou-ULis-blue"/></h1>   

> 一个想到哪做到哪的机器人项目 
<p>
    <img src="https://img.shields.io/badge/CengLou-v1.0-blue"/>
</p>  

### ✨ 简介
1.毕业设计的项目-基于OpenCV的人脸识别工具的设计与实现;   
2.但是目前毕业了，人脸识别功能将在新版本中去除，物体识别将会代替

⬇️[下载地址](https://github.com/Hiiam9)

## 🚀 快速使用
⚙️机械结构：
目前拼凑出的整体图如下，后续会舍弃掉一些（如测试使用的intel神经元计算棒）
<p><img src="https://github.com/Hiiam9/CengLou/blob/main/mechanics/pic/wholeCar.jpeg" width="360" height="250"/>各个模块细节查看：https://github.com/Hiiam9/CengLou/blob/main/mechanics</p>   


💡整体软硬件平台    

⚡️硬件：  
上位机---Nvidia Tegra K1 || Nvidia Tegra X1 || Nvidia Tegra X2  
      <p><img src="https://github.com/Hiiam9/CengLou/blob/main/other/jetsonpic/tx2.png"/><img src="https://github.com/Hiiam9/CengLou/blob/main/other/jetsonpic/tk1.jpg" width = "360" height = "250"/></p>
      下位机---STM32 F4系列芯片（引脚可能部分不同）  
      底  盘---STM32 F1系列芯片 （底盘采用的是有方机器人的套件，只有遥控部分做了一些线路和通信协议的改动）  
      
📷 摄像头  


**在使用之前，请务必阅读各个目录的README文件**
将最新工程clone到本地，并进入CengLou目录

    1. #sudo chmod +x install.sh  
   
    2. #./install  

    3. #./cenglou -f /*启动人脸识别*/ 
     
 说明：安装脚本install.sh 使用了各个工程的makefile文件，如需单独使用某个工程，请单独编译。
 
## 🛠 功能与设置
功能：
- 人脸识别与云台跟踪  
人脸检测<p><img src="https://github.com/Hiiam9/CengLou/blob/main/other/detect/faceDetect.png" width = "720" height = "480"/></p>
- 识别信息存入数据库  

设置：  
```bash
#./cenglou -f /*单独启动人脸识别模式，不向下位机发送数据，不存入数据库*/

#./cenglou -a /*启动所有功能 人脸识别 入库 向下位机发送yaw&pitch坐标*/
```
## 🚀 客户端
*客户端目前只测试了ubuntu 14.04 及以上的linux操作系统，但理论上只要运行客户端的主机安装了OpenCV3和Py3 即可跨平台*  
v1.0 Form:
<p><img src="https://github.com/Hiiam9/CengLou/blob/main/other/clientpic/clientpic.png" width = "720" height = "480"/></p>  

- 功能 :  
1.光毓电机调试  
2.雄迈摄像头串口调试  
3.yaw-pitch 三环读取  
4.后台数据库识别信息查看  
5.上位机状态展示  

客户端下载：[源码地址](https://github.com/Hiiam9/CengLou/tree/main/client)  
构建说明参考client目录下的[README](https://github.com/Hiiam9/CengLou/blob/main/client/README.md)文件  
## ⚡️ 调试
## 📱通信协议  
1.上位机至下位机通信协议   
    主要用于云台角度交互
|Byte0|Byte1|Byte2|Byte3|Byte4|Byte5|
|:--|:--|:--|:--|:--|:--|
|0xA0|cmdID|CRC8_Check|pitch_data|pitch_data|pitch_data|
|Byte6|Byte7|Byte8|Byte9|Byte10|Byte11|
|pitch_data|yaw_data|yaw_data|yaw_data|yaw_data|flag|

## 📖数据库
## 🌲文件树  
├── client  
│   ├── build-CengLou-Desktop_Qt_5_13_0_GCC_64bit-Debug  
│   │   ├── about.o  
│   │   ├── CengLou  
│   │   ├── E:\cl\test.jpg  
│   │   ├── main.o  
│   │   ├── mainwindow.o  
│   │   ├── Makefile  
│   │   ├── moc_about.cpp  
│   │   ├── moc_about.o  
│   │   ├── moc_mainwindow.cpp  
│   │   ├── moc_mainwindow.o  
│   │   ├── moc_predefs.h  
│   │   ├── moc_yawinf.cpp  
│   │   ├── moc_yawinf.o  
│   │   ├── ui_about.h  
│   │   ├── ui_mainwindow.h  
│   │   ├── ui_yawinf.h  
│   │   └── yawinf.o  
│   ├── README.md  
│   └── src  
│       ├── about.cpp  
│       ├── about.h  
│       ├── about.ui  
│       ├── CengLou.pro  
│       ├── CengLou.pro.user  
│       ├── help.chm  
│       ├── help.hhp  
│       ├── ic.ico  
│       ├── lulu.png  
│       ├── main.cpp  
│       ├── mainwindow.cpp  
│       ├── mainwindow.h  
│       ├── mainwindow.ui  
│       ├── spider.py  
│       ├── switchcontrol.cpp  
│       ├── switchcontrol.h  
│       ├── switchcontrol.ui  
│       ├── Table of Contents.hhc  
│       ├── videoproc.cpp  
│       ├── videoproc.h  
│       ├── yawinf.cpp  
│       ├── yawinf.h  
│       └── yawinf.ui  
├── clientpic.png  
├── elecCtl  
│   ├── README.md  
│   └── src  
│       └── README.md  
├── mechanics  
│   ├── pic  
│   │   └── wholeCar.jpeg  
│   ├── README.md  
│   ├── 云台中控.SLDPRT  
│   ├── 云台支架0816.SLDPRT  
│   ├── 云台支架.SLDPRT  
│   └── 装配体2.SLDASM  
├── other  
│   ├── clientpic  
│   │   ├── clientpic.png  
│   │   ├── client.png  
│   │   └── xmCam.gif  
│   ├── detect  
│   │   └── faceDetect.png  
│   ├── jetsonpic  
│   │   ├── re  
│   │   ├── tk1.jpg  
│   │   └── tx2.png  
│   └── README.md
├── README.md  
└── vision  
    ├── ccallocal.cpp  
    ├── ccallocal.h  
    ├── ccallocal.o  
    ├── CengLou.pro  
    ├── cfacerec.cpp  
    ├── cfacerec.h  
    ├── cfacerec.o  
    ├── cgetimg.cpp  
    ├── cgetimg.h  
    ├── cgetimg.o  
    ├── cimgproc.cpp  
    ├── cimgproc.h  
    ├── cimgproc.o  
    ├── cserial.cpp  
    ├── cserial.h  
    ├── cserial.o  
    ├── csetting.cpp  
    ├── csetting.h  
    ├── faceinfotomysql.cpp  
    ├── faceinfotomysql.h  
    ├── fairsionCam  
    │   ├── fairsionCamera_arm_i686.bin  
    │   └── ReadMe  
    ├── jetpack  
    │   └── README.md  
    ├── main.cpp  
    ├── main.o  
    ├── Makefile  
    ├── module  
    │   └── haarcascade_frontalface_alt.xml  
    └── README.md  
  

## 😘 参与此项目 
由于目前此项目完全是一个人在搞，个人水平的限制造成太多不完善，希望有相同爱好的朋友参与进来，一起搞机！！！  
期待来信  *email：ulis2020@163.com*

## 📝 其他项目

🔐综合漏洞扫描：[项目地址](https://github.com/Hiiam9/lampShadow)  
🍊流量分析检测：[项目地址](https://github.com/Hiiam9/nightwish)   
💻操作系统项目：[项目地址](https://github.com/ULis3h/LampShadowOS)
