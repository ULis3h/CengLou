此目录存放CengLou的客户端程序源码  
依赖环境 ：因为使用的是qt库，理论上只要安装好opencv 和 python 即可跨平台  
          qt4 ~ qmake  
          g++
          OpenCV 3.4.1（其余版本可能会通用，若使用新版本可能会有些API被移除）  
          
test客户端主要功能为接收 上位机传输的图像和调试电机及串口数据的功能

## 雄迈摄像头[OPTION]  
由于客户端可以调试雄迈模组的变焦镜头，所以将介绍放在这里
这个变焦镜头的方案参照一次偶然视频刷到的拆个网络监控摄像头的模组+变焦镜头实现拉流获取视频的功能，所以想着之后为机器人加个图传   
正好还有变焦功能，所以就做了这个，由于这个变焦镜头并不是必不可少的,所以加了个option的标号

变焦镜头介绍：  
默认地址码：1             波特率：9600            协议：Pelco-d
RS485通用指令             电压3.3V                            
<p><img src="https://github.com/Hiiam9/CengLou/blob/main/other/clientpic/xmCam.gif"/></p>
