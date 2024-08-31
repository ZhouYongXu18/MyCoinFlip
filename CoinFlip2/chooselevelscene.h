#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"
#include <QMouseEvent>
#include "mypushbutton.h"
#include <QLabel>
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void mouseEvent(QMouseEvent *);
        void readdata();
    MyPushButton *btnarray[25];
        QLabel *arraylabel[25];
    PlayScene *play;
    // bool isLock=true;
    int islock[21];
    int realislock[21];
    char *pStr;
signals:
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
