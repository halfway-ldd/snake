#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include "basic_setting.h"
#include "snakelist.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>
class snake : public QWidget
{
    Q_OBJECT
public:
    explicit snake(QWidget *parent = nullptr);
    void initsnake(mapnode* head,mapnode* tail);      //初始化蛇  一个链表
    void snakemove();
    int gethead_x(){return head_x;};
    int gethead_y(){return head_y;};
    int gettail_x(){return tail_x;};
    int gettail_y(){return tail_y;};
    void getmap(mapnode * _map[MAX_X][MAX_Y]);
    void eatfood();
    QTimer timer;                                   //管理运动速度的计时器
    QPixmap snakeheadpic;                           //储存相关图片
    QPixmap snakebodypic;
    QPixmap wallpic;
    QPixmap spacepic;
    QPixmap foodpic;
    static int speed;
signals:
    void atefood();
    void snakeover();
    void stoptime();
    void continuetime();
private:
    int head_x;
    int head_y;
    int tail_x;
    int tail_y;
    snakelist mysnake;
    int movemode=4;
    bool move=true;
    mapnode *(*map)[20];
    void gameover();
    void loadpix();                              //加载图片
protected:
     void keyPressEvent(QKeyEvent * Aevent);
};

#endif // SNAKE_H
