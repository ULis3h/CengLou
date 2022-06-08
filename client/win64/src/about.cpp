#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    //禁止修改窗口大小
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮

    setFixedSize(this->width(),this->height());                     // 禁止拖动窗口大小
/*
    //显示顶部背景
    //1.路径包含
    QString bg_path("C:\\Users\\Mypc\\Desktop\\bg.jpg");
    //2.创建图片对象
    QPixmap *bg_pix = new QPixmap(bg_path);
    //3.设置大小兼容
    QPixmap pix2 = bg_pix->scaled(ui->label_background->size());
    //4.将图片放到控件
    ui->label_background->setPixmap(pix2);
*/
}

about::~about()
{
    delete ui;
}

void about::on_pushButton_clicked()
{
    delete this;
}

void about::on_commandLinkButton_clicked()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://www.baidu.com")));
}
