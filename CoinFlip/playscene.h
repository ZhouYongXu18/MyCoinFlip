#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPaintEvent>
#include <qpainter.h>
#include "mycoin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int levelnum);
    void paintEvent(QPaintEvent *);
    int array[4][4];
    MyCoin *coinbtn[4][4];
    bool iswin;
signals:
    void choosesceneback();
};

#endif // PLAYSCENE_H
