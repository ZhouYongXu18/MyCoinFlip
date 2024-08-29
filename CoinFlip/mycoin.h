#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>
#include <QMouseEvent>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    // explicit MyCoin(QWidget *parent = nullptr);
    // 传入路径，是金币还是银币
   MyCoin(QString str);

    int posX;
   int posY;
    bool flag;/*判断正反面*/


    // 改变正反面的方法
    void ChangFlag();
    QTimer *timer1;
    QTimer *timer2;
    int min=1;
    int max=8;
    bool isAnimation=false;
    bool isWin=false;


    void mousePressEvent(QMouseEvent *);

signals:
};

#endif // MYCOIN_H
