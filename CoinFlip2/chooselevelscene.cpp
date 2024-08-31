#include "chooselevelscene.h"
#include <QPainter>
#include <QMenuBar>
#include <mypushbutton.h>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include "playscene.h"
#include <QSoundEffect>
#include <QFile>
#include <QDir>

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

backBtn->isLock=1;

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

  // 从文件中读取数据
 readdata();



for(int i=0;i<20;i++)
 {
     MyPushButton *menubtn=new MyPushButton(":/res/LevelIcon.png");
    menubtn->setParent(this);
     menubtn->move(25+i%4*75,130+i/4*75);

     // 将每一个关卡按钮存放进一个数组，方便维护----这个很重要，在按钮上做手脚时候都要用上
    btnarray[i]=menubtn;
     // 判断每一关有没有解锁
    menubtn->isLock=this->realislock[i];
    // 没有解锁就加上锁的图标
    if(menubtn->isLock<1)
    {
        QLabel *locklabel=new QLabel;
        arraylabel[i]=locklabel;
        locklabel->setParent(menubtn);
        QPixmap pix;
        pix.load(":res/lock.png");
        pix=pix.scaled(pix.width()*2+5,pix.height()*2+5);
        locklabel->setFixedSize(pix.width(),pix.height());
        locklabel->move(10,10);
        locklabel->setPixmap(pix);
    }

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

         connect(play,&PlayScene::havewined,[=]()
             {
             QString Str=QString("第%1关通过").arg(QString::number(i+1));
             qDebug()<<Str;
             // 获胜后解锁下一关
             islock[i+2]=1;
             // 把数据写进文件
             QString strpath=QDir::currentPath() + "/data.txt";
             QFile file(strpath);

             if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
             {
                 qDebug()<<"打开文件失败，请生重新检查？";
             }
             file.write(" ");
             for(int i=1;i<=20;i++)
             {
                 file.write(QString::number(islock[i]).toUtf8());
             }
             file.close();
             // 再次读取更新数据
             readdata();
             // 再次判断每一关是否解锁
             for(int i=0;i<20;i++)
             {
                 btnarray[i]->isLock=this->realislock[i];
             }
             arraylabel[i+1]->hide();
         }
                 );

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

void ChooseLevelScene::readdata()
{

    QString strpath=QDir::currentPath() + "/data.txt";
    QFile file(strpath);

    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"打开文件失败，请生重新检查？";
    }
    pStr=new char[31];
    qint64 rcount=file.readLine(pStr,31);

    while((rcount!=0) && (rcount!=-1))
    {
        rcount=file.readLine(pStr,31);
    }

    file.close();

    for(int i=1;i<=20;i++)
    {
        islock[i]=static_cast<int>(pStr[i])-static_cast<int>('0');
        // islock数组读取的第一个是乱码，从第二个开始是正常的
        realislock[i-1]=islock[i];
    }
}










