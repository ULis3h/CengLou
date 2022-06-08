#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>


using namespace cv;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    std::cout<<"software start"<<endl;
    ui->setupUi(this);
    //禁止修改窗口大小
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮

    setFixedSize(this->width(),this->height());                     // 禁止拖动窗口大小

    SerialPort = new QSerialPort;

    QString pic_path ="D:\\Documents\\src\\lulu.png";
    QPixmap *pic_pix = new QPixmap(pic_path);
    //3.设置大小兼容
    QPixmap pix = pic_pix->scaled(ui->label_pic->size());
    //4.将图片放到控件
    ui->label_pic->setPixmap(pix);

   /* //视频显示区默认图像
    //显示顶部背景
     //1.路径包含
     QString bg_path("C:\\Users\\Mypc\\Desktop\\bg.jpg");
     //2.创建图片对象
     QPixmap *bg_pix = new QPixmap(bg_path);
     //3.设置大小兼容
     QPixmap pix2 = bg_pix->scaled(ui->label_player->size());
     //4.将图片放到控件
     ui->label_player->setPixmap(pix2);
   */

    mediaPlayer = new QMediaPlayer();
    layout_video = new QVBoxLayout;
    videoWidget = new QVideoWidget();
    layout_video->setMargin(1);


    connect(ui->spinBox, SIGNAL(valueChanged(int)),
                        ui->horizontalSlider, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),
                        ui->spinBox, SLOT(setValue(int)));

    connect(ui->actionopen, SIGNAL(triggered()), this, SLOT(on_btn_openFile_clicked()));//打开文件信号连接

    connect(SerialPort,SIGNAL(readyRead()),this,SLOT(serial_Read()));


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(importFrame()));

    //实时接收模式 udp套接字 信号连接
    recver.bind(QHostAddress::Any,52475);
    connect(&recver,SIGNAL(readyRead()),this,SLOT(recvVideoShow()));


    Init();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete SerialPort;
    delete mediaPlayer;
    delete layout_video;
    delete videoWidget;
    delete  pro;
}

void MainWindow::Init(){


    //读取串口信息
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        // 自动读取串口号添加到端口portBox中
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->portBox->addItem(info.portName());
            serial.close();
        }
    }

    //所有开关关闭
    this->procTk1 = false;

     QStringList baudList;   //波特率
     QStringList parityList; //校验位
     QStringList dataBitsList;   //数据位
     QStringList stopBitsList;   //停止位
     // 波特率    //波特率默认选择下拉第三项：9600

     baudList<<"1200"<<"2400"<<
               "4800"<<"9600"<<
               "14400"<<"19200"<<
               "38400"<<"56000"<<
               "57600"<<"115200";
     ui->boteBox->addItems(baudList);
     ui->boteBox->setCurrentIndex(9);

     // 校验      //校验默认选择无
     parityList<<"No"<<"Odd"<<"Even";
     ui->comboBox_check->addItems(parityList);
     ui->comboBox_check->setCurrentIndex(0);


     // 数据位      //数据位默认选择8位
     dataBitsList<<"5"<<"6"<<"7"<<"8";
     ui->comboBox_data->addItems(dataBitsList);
     ui->comboBox_data->setCurrentIndex(3);


     // 停止位      //停止位默认选择1位
     stopBitsList<<"1"<<"2";
     ui->comboBox_end->addItems(stopBitsList);
     ui->comboBox_end->setCurrentIndex(0);
}

//接收视频显示函数
void MainWindow::recvVideoShow(){
    if(this->recvModel){
        quint64 size = recver.pendingDatagramSize();
        QByteArray buf;
        buf.resize(size);
        QHostAddress addr;
        quint16 port;
        recver.readDatagram(buf.data(),buf.size(),&addr,&port);
        buf = qUncompress(buf);
        QBuffer buffer(&buf);
        QImageReader reader(&buffer,"JPEG");
        QImage image = reader.read();//read()方法用来读取设备图像，也可读取视频，读取成功返回QImage*，否则返回NULL
        ui->label_player->setPixmap(QPixmap::fromImage(image));
        ui->label_player->resize(image.width(),image.height());
    }
}


void MainWindow::on_btn_openFile_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("选择视频"), ".", tr("Image Files(*.flv *.mp4)"));//得到视频路径
    //根据label_player尺寸设置播放区域
    videoWidget->resize(ui->label_player->size());
    layout_video->addWidget(videoWidget);
    ui->label_player->setLayout(layout_video);
    mediaPlayer->setVideoOutput(videoWidget);
    mediaPlayer->setMedia(QUrl::fromLocalFile(path));
    mediaPlayer->play();
}


void MainWindow::on_action_about_triggered()
{
    ab = new about();
    ab->setWindowFlags(ab->windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint);

    ab->show();
}

void MainWindow::on_openPort_btn_clicked()//打开串口点击事件
{
    if(ui->portBox->currentText()==""){

         QMessageBox::information(this,"warning","没有找到串口");
    }

        // 打开串口
        if(ui->openPort_btn->text() == "打开串口")
        {
            // 设置串口号

            SerialPort->setPortName(ui->portBox->currentText());
            // 打开串口
            if(SerialPort->open(QIODevice::ReadWrite))
            {
                // 设置波特率
                SerialPort->setBaudRate(ui->boteBox->currentText().toInt());
                //设置数据位数
                switch(ui->comboBox_data->currentIndex())
                {
                case 5: SerialPort->setDataBits(QSerialPort::Data5); break;
                case 6: SerialPort->setDataBits(QSerialPort::Data6); break;
                case 7: SerialPort->setDataBits(QSerialPort::Data7); break;
                case 8: SerialPort->setDataBits(QSerialPort::Data8); break;
                default: break;
                }
                // 设置校验位
                //SerialPort->setParity(QSerialPort::NoParity);
                //设置奇偶校验
                switch(ui->comboBox_check->currentIndex())
                {
                case 0: SerialPort->setParity(QSerialPort::NoParity); break;
                case 1: SerialPort->setParity(QSerialPort::OddParity); break;
                case 2: SerialPort->setParity(QSerialPort::EvenParity); break;
                default: break;
                }
                // 设置流控制
                SerialPort->setFlowControl(QSerialPort::NoFlowControl);
                //设置停止位
                switch(ui->comboBox_end->currentIndex())
                {
                case 1: SerialPort->setStopBits(QSerialPort::OneStop); break;
                case 2: SerialPort->setStopBits(QSerialPort::TwoStop); break;
                default: break;
                }
            }
            //打开串口
            else
            {
                QMessageBox::about(nullptr, "提示", "串口无法打开\r\n不存在或已被占用");
                return;
            }
            ui->openPort_btn->setText("关闭串口");
            //下拉菜单控件使能
            ui->portBox->setEnabled(false);
            ui->boteBox->setEnabled(false);
            ui->comboBox_data->setEnabled(false);
            ui->comboBox_check->setEnabled(false);
            ui->comboBox_end->setEnabled(false);

            //搜索串口按键使能
            //ui->searchBtn->setEnabled(false);

            //发送按键使能
            ui->pushButton_sendData->setEnabled(true);
        }
        // 关闭串口
        else
        {
            SerialPort->close();
            ui->openPort_btn->setText("打开串口");
            //下拉按键使能
            ui->portBox->setEnabled(true);
            ui->boteBox->setEnabled(true);
            ui->comboBox_data->setEnabled(true);
            ui->comboBox_check->setEnabled(true);
            ui->comboBox_end->setEnabled(true);
            //搜索串口按键使能
           // ui->searchBtn->setEnabled(true);
            //发送按键使能
            ui->pushButton_sendData->setEnabled(false);
        }


}

void MainWindow::on_btn_Connect_Stm32_clicked()//连接stm32按钮点击事件
{
    string ip = "192.168.1.4";
    int port = 8888;

    if(ui->portBox->currentText()!=""){//判断端口是否打开，暂时先这么写

        int count = 0;
        while(count<=100){

            ui->progressBar_stm32->setValue(count);
            count++;
        }
    }
    else
        QMessageBox::information(this,"warning","请先打开串口");
}

void MainWindow::on_pushButton_left_clicked()//左旋按钮单击事件
{
    if(ui->openPort_btn->text() == "打开串口"){
        QMessageBox::information(this,"warning","无法连接电机，请先打开串口");
        return;
    }
    SerialPort->clear();
    if(this->yaw_right_angle <= -360)
        this->yaw_right_angle = 0;
    else
    {
        this->yaw_right_angle -= 30;
        QByteArray Data_1;
        QString Data = "3E A3 01 08 EA 00 00 00 00 00 00 00 00 00 ";
        switch (this->yaw_right_angle) {//更简洁的方法则需使用字符串拼接
        case -30 :{
            Data = "3E A3 01 08 EA 48 F4 FF FF FF FF FF FF 36 ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case -60 :{
            Data = "3E A3 01 08 EA 90 E8 FF FF FF FF FF FF 72 ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case -90 :{
            Data = "3E A3 01 08 EA D8 DC FF FF FF FF FF FF AE ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case -120 :{
            Data = "3E A3 01 08 EA 20 D1 FF FF FF FF FF FF EB ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case -150 :{
            Data = "3E A3 01 08 EA 68 C5 FF FF FF FF FF FF 27 ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case -180 :{
            Data = "3E A3 01 08 EA B0 B9 FF FF FF FF FF FF 63 ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case -210 :{
            Data = "3E A3 01 08 EA F8 AD FF FF FF FF FF FF 9F ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case -240 :{
            Data = "3E A3 01 08 EA 40 A2 FF FF FF FF FF FF DC ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case -270 :{
            Data = "3E A3 01 08 EA 88 96 FF FF FF FF FF FF 18 ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case -300 :{
            Data = "3E A3 01 08 EA D0 8A FF FF FF FF FF FF 54 ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case -330 :{
            Data = "3E A3 01 08 EA 18 7F FF FF FF FF FF FF 91 ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case -360 :{
            Data = "3E A3 01 08 EA 60 73 FF FF FF FF FF FF CD ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        default:{
            Data = "3E A3 01 08 EA 00 00 00 00 00 00 00 00 00 ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        }
        if(yawAuto)
        ui->spinBox->setValue(yaw_right_angle);
        Data_1 = QByteArray::fromHex (Data.toLatin1().data());//按十六进制编码发送
        SerialPort->write(Data_1);
    }
}


void MainWindow::serial_Read()
{

  QString buffer_1;
        //从缓冲区中读取数据
        QByteArray buffer = SerialPort->readAll();
        if((!buffer.isEmpty()))//如果非空说明有数据接收
        {   //转换成16进制大写
            QString str=buffer.toHex().data();
            str=str.toUpper();
            //一个16进制占4位，8位为一字节，所以每两位16进制空一格
            for(int i=0;i<str.length();i+=2)
            {
                   QString str_1 = str.mid (i,2);
                   buffer_1 += str_1;
                   buffer_1 += " ";
            }
        //读取之前显示数据
        QString receive = ui->plainTextEdit_recv->toPlainText();
        //清空显示
        ui->plainTextEdit_recv->clear();
        //重新显示
        if(hexable==0){
                receive += QString(buffer);
                ui->plainTextEdit_recv->appendPlainText(receive);
                }//直接显示
        else    {
                receive += QString(buffer_1);
                ui->plainTextEdit_recv->appendPlainText(receive);
                }//16进制显示
        }
        buffer.clear();

}


void MainWindow::on_pushButton_sendData_clicked()
{
    QByteArray Data_1;
        //获取输入窗口sendData的数据
        QString Data = ui->plainTextEdit_send->toPlainText();
        if(endable)       {Data+='\r';Data+='\n';}//插入换行
        //Data_1 = Data.toUtf8();//转换成utf8格式的字节流发送
         Data_1 = QByteArray::fromHex (Data.toLatin1().data());//按十六进制编码发送
        // 写入发送缓存区
        SerialPort->write(Data_1);


}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->plainTextEdit_recv->setPlainText("");
}



void MainWindow::on_horizontalSlider_valueChanged(int value)//云台角度滑动条
{
    if(ui->openPort_btn->text() == "打开串口"){
        QMessageBox::information(this,"warning","请先打开串口");
    }
    else{
    if(!(ui->checkBox_auto->checkState())){
    QByteArray Data_2;
        //获取输入窗口sendData的数据
        uint32_t locValue = ui->horizontalSlider->value()*100;
        int crc = (locValue&(0x00ff)) + (locValue >> 8);
        QString key;
        QString crcKey;
        key =  QString("%1").arg(locValue,2,16,QLatin1Char('0'));//k为int型或char型都可
        crcKey = QString("%1").arg(crc,2,16,QLatin1Char('0'));
        qDebug()<<key;
        QString Data = "3E A3 01 08 EA"+key.right(2)+key.left(2)+"00 00 00 00 00 00"+crcKey;
        if(endable)       {Data+='\r';Data+='\n';}//插入换行
         Data_2 = QByteArray::fromHex (Data.toLatin1().data());//按十六进制编码发送
        // 写入发送缓存区
        SerialPort->write(Data_2);
    }
}
}

void MainWindow::on_checkBox_auto_stateChanged(int arg1)//滑动条勾选自动事件
{
    this->yawAuto = !this->yawAuto;
    if(ui->checkBox_auto->checkState()){
    ui->horizontalSlider->setEnabled(false);
    }
    else
        ui->horizontalSlider->setEnabled(true);
}

void MainWindow::on_radioButton_hex_clicked(bool checked)
{
    if(checked == true)
    hexable = true;
}

void MainWindow::on_actionhelp_triggered()//点击帮助
{
    QProcess *helpProcess = new QProcess(this);
    QStringList argument("E:\\cl\\CengLou\\help.chm");
    helpProcess->start("hh.exe", argument);//运行另一个程序片段的代码
}

void MainWindow::on_radioButton_5_clicked()//视频处理机 Tk1被选择
{
    this->procTk1 = true;
}


void MainWindow::on_pushButton_360_yaw_clicked()
{
    QByteArray Data_1;
        //获取输入窗口sendData的数据
        QString Data = "3E A2 01 04 E5 A0 8C 00 00 2C";
        Data_1 = QByteArray::fromHex (Data.toLatin1().data());//按十六进制编码发送
        SerialPort->write(Data_1);
}

void MainWindow::on_pushButton_stop_yaw_clicked()
{
    QByteArray Data_1;
        //获取输入窗口sendData的数据
        QString Data = "3E 80 01 04 C3";
        Data_1 = QByteArray::fromHex (Data.toLatin1().data());//按十六进制编码发送
        SerialPort->write(Data_1);
}

void MainWindow::on_pushButton_right_clicked()//yaw右旋点击事件
{
    if(ui->openPort_btn->text() == "打开串口"){
        QMessageBox::information(this,"warning","无法连接电机，请先打开串口");
        return;
    }
    SerialPort->clear();
    if(this->yaw_right_angle >= 360)
        this->yaw_right_angle = 0;
    else
    {
        this->yaw_right_angle += 30;
        QByteArray Data_1;
        QString Data = "3E A3 01 08 EA 00 00 00 00 00 00 00 00 00 ";
        switch (this->yaw_right_angle) {//更简洁的方法则需使用字符串拼接
        case 30 :{
            Data = "3E A3 01 08 EA B8 0B 00 00 00 00 00 00 C3 ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case 60 :{
            Data = "3E A3 01 08 EA 70 17 00 00 00 00 00 00 87 ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case 90 :{
            Data = "3E A3 01 08 EA 28 23 00 00 00 00 00 00 4B ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case 120 :{
            Data = "3E A3 01 08 EA E0 2E 00 00 00 00 00 00 0E ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case 150 :{
            Data = "3E A3 01 08 EA 98 3A 00 00 00 00 00 00 D2 ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case 180 :{
            Data = "3E A3 01 08 EA 50 46 00 00 00 00 00 00 96 ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case 210 :{
            Data = "3E A3 01 08 EA 08 52 00 00 00 00 00 00 5A ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case 240 :{
            Data = "3E A3 01 08 EA C0 5D 00 00 00 00 00 00 1D ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case 270 :{
            Data = "3E A3 01 08 EA 78 69 00 00 00 00 00 00 E1 ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case 300 :{
            Data = "3E A3 01 08 EA 30 75 00 00 00 00 00 00 A5 ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case 330 :{
            Data = "3E A3 01 08 EA E8 80 00 00 00 00 00 00 68 ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        case 360 :{
            Data = "3E A3 01 08 EA A0 8C 00 00 00 00 00 00 2C ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        default:{
            Data = "3E A3 01 08 EA 00 00 00 00 00 00 00 00 00 ";
            qDebug()<<Data;
            qDebug()<<this->yaw_right_angle;
            break;
        }
        }
        if(yawAuto)
        ui->spinBox->setValue(yaw_right_angle);
        Data_1 = QByteArray::fromHex (Data.toLatin1().data());//按十六进制编码发送
        SerialPort->write(Data_1);
    }

}

void MainWindow::on_actionyaw_triggered()
{
    //菜单->配置->电机信息->yaw 点击事件
    this->yawinfWindow = new yawinf();
    yawinfWindow->show();
}

void MainWindow::on_pushButton_2_clicked() // 实时接收模式按钮点击事件
{
    this->recvModel = true;
    cap = VideoCapture("rtsp://192.168.1.9:554/user=admin&password=&channel=1&stream=1.sdp?real_stream");
    if(!cap.isOpened())
    {
        qDebug()<<"open camera faild";
        return;
    }
    importFrame();
}


void MainWindow::importFrame()
{

    ui->label_center_info->setText("");
    cap >> frame;
    imshow("test",frame);
    Mat dst;
    Mat dst1;
    cvtColor(frame, dst, CV_BGR2RGB);//only RGB of Qt
    cv::resize(dst,dst1,Size(ui->label_player->width(),ui->label_player->height()));
    QImage srcQImage = QImage((uchar*)(dst1.data), dst1.cols, dst1.rows, QImage::Format_RGB888);
    ui->label_player->setPixmap(QPixmap::fromImage(srcQImage));
    timer->start(33);
}

void MainWindow::on_btn_Connect_Pi_clicked()//连接树莓派按钮点击
{


        int count = 0;
        while(count<=100){

            ui->progressBar_Pi->setValue(count);
            count++;
        }
       pro = new QProcess;

       pro->start("\"C:\\Program Files (x86)\\NetSarang\\Xshell 6\\Xshell.exe\"");



}

void MainWindow::on_pushButton_force_add_clicked()//变焦+
{

    QByteArray Data_1;
    QString Data = "FF 01 00 40 00 00 41 FF 01 00 00 00 00 01";
    Data_1 = QByteArray::fromHex (Data.toLatin1().data());
    SerialPort->write(Data_1);
}



void MainWindow::on_pushButton_force_red_clicked()//变焦-
{
    QByteArray Data_1;
    QString Data = "FF 01 00 20 00 00 21 FF 01 00 00 00 00 01";
    Data_1 = QByteArray::fromHex (Data.toLatin1().data());
    SerialPort->write(Data_1);
}

void MainWindow::on_pushButton_write_img_clicked()  //采集按钮点击事件
{
    cap >> frame;
    cv::imwrite("E:\\cl\\test.jpg", frame);
    QMessageBox::information(this,"消息","保存成功");
}
