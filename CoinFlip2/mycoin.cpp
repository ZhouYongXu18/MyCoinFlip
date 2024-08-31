#include "mycoin.h"

// MyCoin::MyCoin(QWidget *parent)
//     : QPushButton{parent}
// {}
MyCoin::MyCoin(QString strpath)
{
    QPixmap pix;
    bool ret = pix.load(strpath);
     pix=pix.scaled(pix.width()+4,pix.height()+6);
    if(!ret)
    {
        QString str=QString("图片%1加载失败").arg(strpath);
        qDebug()<<str;
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

    // 初始化定时器
    timer1=new QTimer;
    timer2=new QTimer;
    // 监听正面翻反面信号
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(QString::number(min++));
        pix.load(str);

        this->setFixedSize( pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
         this->setIconSize(QSize(pix.width(),pix.height()));
        this->setIcon(pix);

         if(min>max)
             {
            timer1->stop();
             min=1;
            isAnimation=false;
         }
    });
    // 监听反面翻正面信号
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%8.png").arg(QString::number(max--));
        pix.load(str);

        this->setFixedSize( pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIconSize(QSize(pix.width(),pix.height()));
        this->setIcon(pix);

        if(max<min)
        {
            timer2->stop();
            max=8;
            isAnimation=false;
        }
    });
}

void MyCoin::ChangFlag()
{
    if(flag==1)
    {
        timer1->start(20);
        flag=0;
        isAnimation=true;

    }
    else
    {
        timer2->start(20);
        flag=1;
        isAnimation=true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *event)
{
    if(isAnimation==true||isWin==true)
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(event);
    }
}
























