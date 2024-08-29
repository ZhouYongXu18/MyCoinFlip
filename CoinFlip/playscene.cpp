#include "playscene.h"
#include <QStringList>
#include <QMenuBar>
#include <QLabel>
#include <QDebug>
#include <mycoin.h>
#include <datefile.h>
#include <QPropertyAnimation>
#include "mypushbutton.h"
#include <QSoundEffect>
#include <QTimer>

// PlayScene::PlayScene(QWidget *parent)
//     : QMainWindow{parent}
// {}
PlayScene::PlayScene(int levelnum)
{
    // 初始化游戏场景
    // 固定游戏大小
    this->setFixedSize(320,588);
    // 设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    // 设置标题
    // QString str=QString("第%1关").arg(QString::number(levelnum));
    // this->setWindowTitle(str);
    this->setWindowTitle("游戏场景");

    // 创建菜单栏
    QMenuBar *bar=menuBar();
    // 创建菜单
    QMenu *startmenu=bar->addMenu("开始");
    // 创建菜单项
    QAction *quitaction=startmenu->addAction("退出");
    QAction *backaction=startmenu->addAction("返回");

    // 创建返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png" , ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width() , this->height() - backBtn->height());
    // 设置返回音效
    QSoundEffect *backsound=new QSoundEffect;
    backsound->setSource(QUrl::fromLocalFile((":/res/BackButtonSound.wav")));
    backsound->setLoopCount(1);
    backsound->setVolume(0.25f);

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        // 开始播放
        backsound->play();
        QTimer::singleShot(200,this,[=](){
            emit this->choosesceneback();
        });

    });



    QLabel *label=new QLabel;
    label->setParent(this);
    QString str=QString("Level:%1").arg(QString::number(levelnum));
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(30);
    label->setFont(font);
    label->setText(str);
    label->setGeometry(20,this->height()-60,150,50);


    connect(quitaction,&QAction::triggered,[=](){
        this->close();
    });

    connect(backaction,&QAction::triggered,[=](){
        emit this->choosesceneback();
    });

    // 创建胜利图片
    QLabel *winlabel=new QLabel;
    winlabel->setParent(this);
    QPixmap pixs;
    pixs.load(":res/LevelCompletedDialogBg.png");
    winlabel->setGeometry(0,0,pixs.width(),pixs.height());
    winlabel->setPixmap(pixs);
    winlabel->move((this->width()-pixs.width())*0.5,-pixs.height());





    // 创建数据对象
    DateFile date;
    // 金币路径名
    QString strs;
    // 创建点击金币时的音效
    QSoundEffect *coinsound =new QSoundEffect;
    coinsound->setSource(QUrl::fromLocalFile((":/res/ConFlipSound.wav")));
    coinsound->setLoopCount(1);
    coinsound->setVolume(0.25f);
    // 创建胜利时的音效
    QSoundEffect *winsound =new QSoundEffect;
    winsound->setSource(QUrl::fromLocalFile((":/res/LevelWinSound.wav")));
    winsound->setLoopCount(1);
    winsound->setVolume(0.25f);

    // 显示金币背景图案
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            QLabel *label=new QLabel;
            label->setParent(this);
            QPixmap pix1,pix2;
            pix1.load(":/res/Coin0001.png");
            pix1=pix1.scaled(pix1.width()+4,pix1.height()+6);
            // // qDebug()<<pix1.width();
            // qDebug()<<pix1.height();
            label->setGeometry(0,0,pix1.width(),pix1.height());
            pix2.load(":/res/BoardNode.png");
            // // qDebug()<<pix2.width();
            // qDebug()<<pix2.height();
            label->setPixmap(pix2);
            label->move(57+i*pix2.width(),200+j*pix2.height());


            this->array[i][j]=date.mData[levelnum][i][j];
            // 创建金币
            if(array[i][j]==1)
            {
                strs=QString(":/res/Coin0001.png");
            }
            else
            {
                strs=QString(":/res/Coin0008.png");
            }
            MyCoin *mycoin=new MyCoin(strs);
            mycoin->setParent(this);
            mycoin->move(57+i*50,200+j*50);

            // 给金币属性赋值
            mycoin->posX=i;
            mycoin->posY=j;
            mycoin->flag=array[i][j];


            // 将金币放到金币的二维数组中，方便后期的维护
            coinbtn[i][j]=mycoin;

            // 点击金币进行翻转
            connect(mycoin,&MyCoin::clicked,[=](){
                // 开始播放
                coinsound->play();
                // 翻转
                mycoin->ChangFlag();

                // 把每个按钮设置为胜利，在点击一个按钮的时候，别的按钮都不能点击
                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        coinbtn[i][j]->isWin=true;
                    }
                }

                // 记录金币状态
                array[i][j]= array[i][j]==0 ? 1 : 0;

                QTimer::singleShot(200,this,[=](){
                    // 右侧金币翻转
                    if(mycoin->posX+1<=3)
                    {
                        coinbtn[mycoin->posX+1][mycoin->posY]->ChangFlag();
                        array[mycoin->posX+1][mycoin->posY]= array[mycoin->posX+1][mycoin->posY]==0 ? 1 : 0;
                    }
                    // 左侧金币翻转
                    if(mycoin->posX-1>=0)
                    {
                        coinbtn[mycoin->posX-1][mycoin->posY]->ChangFlag();
                        array[mycoin->posX-1][mycoin->posY]= array[mycoin->posX-1][mycoin->posY]==0 ? 1 : 0;
                    }
                    // 下方金币翻转
                    if(mycoin->posY+1<=3)
                    {
                        coinbtn[mycoin->posX][mycoin->posY+1]->ChangFlag();
                        array[mycoin->posX][mycoin->posY+1]= array[mycoin->posX][mycoin->posY+1]==0 ? 1 : 0;
                    }
                    // 上方金币翻转
                    if(mycoin->posY-1>=0)
                    {
                        coinbtn[mycoin->posX][mycoin->posY-1]->ChangFlag();
                        array[mycoin->posX][mycoin->posY-1]= array[mycoin->posX][mycoin->posY-1]==0 ? 1 : 0;
                    }
                    // 判断是否胜利
                    this->iswin=true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(array[i][j]==0)
                            {
                                this->iswin=false;
                                break;
                            }
                        }
                    }
                    if(this->iswin==true)
                    {

                        QTimer::singleShot(500,winlabel,[=](){
                            // 开始播放
                             winsound->play();

                             QPropertyAnimation *animation=new QPropertyAnimation(winlabel,"geometry");
                             // 设置间隔时间
                             animation->setDuration(1000);
                             // 设置起始位置
                             animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
                             // 设置结束位置
                             animation->setEndValue(QRect(winlabel->x(),-winlabel->y(),winlabel->width(),winlabel->height()));
                             // 设置弹跳曲线
                             animation->setEasingCurve(QEasingCurve::OutBounce);
                             // 开始
                             animation->start();
                        });
                    }
                    // 恢复别的金币为可以点击状态
                    else
                    {
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                coinbtn[i][j]->isWin=false;
                            }
                        }
                    }

                });
            });


        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPixmap pix;
    QPainter painter(this);
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);
}



