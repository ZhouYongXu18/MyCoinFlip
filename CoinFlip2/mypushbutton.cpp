#include "mypushbutton.h"
#include <QPropertyAnimation>
#include <QDebug>
// MyPushButton::MyPushButton(QWidget *parent)
//     : QPushButton{parent}
// {}
MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

    QPixmap pix;
    bool ret = pix.load(normalImg);
    // QString str=QString(":width=%1,height=%2").arg(pix.width()).arg(pix.height());
    // qDebug()<<normalImg<<str;
    if(!ret)
    {
        qDebug() << "图片加载失败";
        return;
    }

    //设置图片固定大小---按钮大小的判定范围
    this->setFixedSize( pix.width(),pix.height());

    //设置不规则图片样式实现透明贴图
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

    //设置图标
    this->setIcon(pix);
}

void MyPushButton::zoom1()
{
    // 创建动态对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    // 设置动画时间间隔
    animation->setDuration(200);
    // 设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    // 设置结束位置
    animation->setEndValue((QRect(this->x(),this->y()-10,this->width(),this->height())));
    // 设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutInBounce);
    // 开始
    animation->start();

}

void MyPushButton::zoom2()
{
    // 创建动态对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    // 设置动画时间间隔
    animation->setDuration(200);
    // 设置起始位置
    animation->setStartValue(QRect(this->x(),this->y()-10,this->width(),this->height()));
    // 设置结束位置
    animation->setEndValue((QRect(this->x(),this->y(),this->width(),this->height())));
    // 设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutInBounce);
    // 开始
    animation->start();

}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="")
    {
        QPixmap pix;
        bool res=pix.load(this->pressImgPath);
        if(!res)
        {
            qDebug()<<"图片加载失败";
            return ;
        }
        //设置图片固定大小---按钮大小的判定范围
        this->setFixedSize( pix.width(),pix.height());

        //设置不规则图片样式实现透明贴图
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));

        //设置图标
        this->setIcon(pix);
    }

    if(isLock<1)
    {
        return;
    }

    // 让父类执行其他操作
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleseEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="")
    {
        QPixmap pix;
        bool res=pix.load(this->normalImgPath);
        if(!res)
        {
            qDebug()<<"图片加载失败";
            return ;
        }
        //设置图片固定大小---按钮大小的判定范围
        this->setFixedSize( pix.width(),pix.height());

        //设置不规则图片样式实现透明贴图
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));

        //设置图标
        this->setIcon(pix);
    }
    return QPushButton::mouseReleaseEvent(e);
}



