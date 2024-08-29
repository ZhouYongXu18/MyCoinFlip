#include "chooselevelscene.h"
#include <QPainter>
#include <QMenuBar>
#include <mypushbutton.h>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include "playscene.h"
#include <QSoundEffect>
ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(320,588);
      this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡");

    // 创建菜单栏
    QMenuBar *bar=menuBar();
    this->setMenuBar(bar);
    // 创建菜单
    QMenu *startmenu=bar->addMenu("开始");
    // 创建菜单项
    QAction *quitaction=startmenu->addAction("退出");

    connect(quitaction,&QAction::triggered,[=](){
        this->close();
    });

// 设置返回按钮
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
     //qDebug() << "点击了返回按钮";
     //告诉主场景 我返回了，主场景监听ChooseLevelScene的返回按钮

// 开始播放
    backsound->play();

      //延时返回
     QTimer::singleShot(200,this,[=](){
         emit this->chooseSceneBack();
     });

    });


// 设置点击选择关卡时的按钮音效
 QSoundEffect *choosesound=new QSoundEffect;
 choosesound->setSource(QUrl::fromLocalFile((":/res/TapButtonSound.wav")));
 choosesound->setLoopCount(1);
 choosesound->setVolume(0.25f);

for(int i=0;i<20;i++)
 {
     MyPushButton *menubtn=new MyPushButton(":/res/LevelIcon.png");
    menubtn->setParent(this);
     menubtn->move(25+i%4*75,130+i/4*75);

    connect(menubtn,&MyPushButton::clicked,[=](){

         // 开始播放
         choosesound->play();
         // 点击创建游戏场景
         play=new PlayScene(i+1);

         // 设置游戏场景的初始位置
         play->setGeometry(this->geometry());

        // 隐藏选择关卡场景
         this->hide();
         // 展示游戏场景
         play->show();

         // 监听游戏场景的返回按钮的信号
         connect(play,&PlayScene::choosesceneback,this,[=](){
             // 保证切换到选择关卡场景时窗口位置不变
             this->setGeometry(play->geometry());

             this->show(); //重新显示选择关卡场景
             // 返回后删除游戏场景，防止次数过多导致内存泄露
             delete play;
             play=NULL;

         });
     });

    QLabel *label=new QLabel;
     label->setParent(menubtn);
    label->setFixedSize(menubtn->width(),menubtn->height());
     label->setText(QString::number(i+1));
    label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
}




}



void ChooseLevelScene::paintEvent(QPaintEvent *event)
{
    // 加载场景
    QPixmap pix;
    QPainter painter(this);
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    // 加载标题
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}
