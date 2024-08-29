#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include "chooselevelscene.h"
#include <QTimer>
#include  <QSoundEffect>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    // 设置固定窗口大小
    this->setFixedSize(320,588);
    // 设置窗口标题
    this->setWindowTitle("翻金币");
    // 设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    // 退出按钮
    connect(ui->actionquit,&QAction::triggered,[=]()
            {
        this->close();
    });

    // 实例化选择关卡场景
    chooselevel=new ChooseLevelScene;

    // 设置开始按钮音效
    QSoundEffect *startsound=new QSoundEffect;
    startsound->setSource(QUrl::fromLocalFile((":/res/TapButtonSound.wav")));
    startsound->setLoopCount(1);
    startsound->setVolume(0.25f);


    // 开始按钮的设置
    MyPushButton *startbtn=new MyPushButton(":/res/MenuSceneStartButton");
    startbtn->setParent(this);
    startbtn->move(this->width()*0.5-startbtn->width()*0.5,this->height()*0.7);
    connect(startbtn,&QPushButton::clicked,[=]()
            {
        // 开始播放
        startsound->play();

        startbtn->zoom1();
        startbtn->zoom2();

        // 切换到选关卡场景
        QTimer::singleShot(200,this,[=](){
            // 保证切换到选择关卡场景时窗口位置不变
             chooselevel->setGeometry(this->geometry());
            // 实例化选择关卡场景
            this->hide();
            chooselevel->show();
        });
            });


    // 返回按钮的设置
    //监听选择关卡的返回按钮的信号
    connect(chooselevel,&ChooseLevelScene::chooseSceneBack,this,[=](){
        // 保证切换到主场景时窗口位置不变
        this->setGeometry(chooselevel->geometry());

        chooselevel->hide(); //将选择关卡场景 隐藏掉
        this->show(); //重新显示主场景
    });

}

void MainScene::paintEvent(QPaintEvent * event)
{
    // 主场景绘画
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    // 给图片进行缩放
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);


}
MainScene::~MainScene()
{
    delete ui;
}
