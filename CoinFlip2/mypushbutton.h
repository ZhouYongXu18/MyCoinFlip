#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    // explicit mypushbutton(QWidget *parent = nullptr);
   MyPushButton(QString normalImg, QString pressImg = "" );
    QString normalImgPath;
   QString pressImgPath;

    void zoom1();
   void zoom2();
    void mousePressEvent(QMouseEvent *);
   void mouseReleseEvent(QMouseEvent *);

    int isLock;

signals:
};

#endif // MYPUSHBUTTON_H
