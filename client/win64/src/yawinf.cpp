#include "yawinf.h"
#include "ui_yawinf.h"

yawinf::yawinf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::yawinf)
{
    ui->setupUi(this);
    //禁止修改窗口大小
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮

    setFixedSize(this->width(),this->height());                     // 禁止拖动窗口大小
}

yawinf::~yawinf()
{
    delete ui;
}
