#include "snake.h"

int snake::speed=200;

snake::snake(QWidget *parent) : QWidget(parent),timer(parent)
{
      head_x=5;
      head_y=5;
      tail_x=4;
      tail_y=5;

      loadpix();
      connect(&timer,&QTimer::timeout,this,&snake::snakemove);
      this->setFocusPolicy(Qt::StrongFocus);
}

void snake::initsnake(mapnode* head,mapnode* tail)
{
      //创建蛇的节点 使snake通过snakelist来管理蛇的信息
      mysnake.init(head,tail);
      //修改地图信息
      head->type=Head;
      head->label->setPixmap(snakeheadpic);
      tail->type=Tail;
      tail->label->setPixmap(snakebodypic);
      speed=200;
      timer.start(speed);
}

void snake::getmap(mapnode *(*_map)[20])
{
    map=_map;
}

void snake::keyPressEvent(QKeyEvent * Aevent)
{
    if(move==true)
    {
    switch (Aevent->key()) {
    case Qt::Key_Space:
        if(timer.isActive())
        {
            timer.stop();
            qDebug()<<"  timer.stop();";
            move=true;
            emit stoptime();
        }
        else
        {
            timer.start();
            qDebug()<<"  timer.stop();";
            move=true;
            emit continuetime();
        }
        move=true;
        break;
    case Qt::Key_Up:
    case Qt::Key_W:
        if(movemode!=2 && timer.isActive())
        {
            movemode=1;
            move=false;
        }
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        if(movemode!=1 && timer.isActive())
        {
            movemode=2;
            move=false;
        }
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        if(movemode!=4 && timer.isActive())
        {
            movemode=3;
            move=false;
        }
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        if(movemode!=3 && timer.isActive())
        {
            movemode=4;
            move=false;
        }
        break;
    default:
        break;
    }
    }
}


void snake::snakemove()
{
    move=true;
    qDebug() << movemode;
    switch (movemode)
    {
    case 1:
    {
        int result=mysnake.add(map[head_x][--head_y]);
        if(result==1)
        {
           mysnake.detail();
        }
        else if(result==0)
        {
           gameover();
        }
        else if(result==2)
        {
            emit atefood();
        }
        break;
    }
    case 2:
    {
        int result=mysnake.add(map[head_x][++head_y]);
        if(result==1)
        {
           mysnake.detail();
        }
        else if(result==0)
        {
           gameover();
        }
        else if(result==2)
        {
            emit atefood();
        }
        break;
    }
    case 3:
       {
        int result=mysnake.add(map[--head_x][head_y]);
        if(result==1)
        {
           mysnake.detail();
        }
        else if(result==0)
        {
           gameover();
        }
        else if(result==2)
        {
           emit atefood();
        }
        break;
    }
    case 4:
    {   int result=mysnake.add(map[++head_x][head_y]);
        if(result==1)
        {
           mysnake.detail();
        }
        else if(result==0)
        {
           gameover();
        }
        else if(result==2)
        {
           emit atefood();
        }
        break;
    }
}
};


void snake::gameover()
{
       this->timer.stop();
       mysnake.deletelist();         //析构掉当前链表 清除蛇
       head_x=5;                     //重置一些初始量
       head_y=5;
       tail_x=4;
       tail_y=5;
       movemode=4;
       move=true;
       speed=200;
       emit snakeover();              //发出蛇 结束信号
}


void snake::loadpix()
{
    switch (data::data_snake) {
    case 1:
        snakeheadpic.load(":/gamepic/snakeHead01");
        snakebodypic.load(":/gamepic/snakeBody01");
        snakeheadpic=snakeheadpic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);
        snakebodypic=snakebodypic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);

        break;
    case 2:
        snakeheadpic.load(":/gamepic/snakeHead02");
        snakebodypic.load(":/gamepic/snakeBody02");
        snakeheadpic=snakeheadpic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);
        snakebodypic=snakebodypic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);

        break;
    case 3:
        snakeheadpic.load(":/gamepic/snakeHead03");
        snakebodypic.load(":/gamepic/snakeBody03");
        snakeheadpic=snakeheadpic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);
        snakebodypic=snakebodypic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);

        break;
    case 4:
        snakeheadpic.load(":/gamepic/snakeHead04");
        snakebodypic.load(":/gamepic/snakeBody04");
        snakeheadpic=snakeheadpic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);
        snakebodypic=snakebodypic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);

        break;
        };
    switch (data::data_wall) {
    case 1:
        wallpic.load(":/gamepic/wall01");
        wallpic=wallpic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);

        break;
    case 2:
        wallpic.load(":/gamepic/wall02");
        wallpic=wallpic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);

        break;
    case 3:
        wallpic.load(":/gamepic/wall03");
        wallpic=wallpic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);

        break;
    case 4:
        wallpic.load(":/gamepic/wall04");
        wallpic=wallpic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);

        break;
        };

    switch (data::data_food) {
    case 1:
        foodpic.load(":/gamepic/food01");
        foodpic=foodpic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);

        break;
    case 2:
        foodpic.load(":/gamepic/food02");
        foodpic=foodpic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);

        break;
    case 3:
        foodpic.load(":/gamepic/food03");
        foodpic=foodpic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);

        break;
    case 4:
        foodpic.load(":/gamepic/food04");
        foodpic=foodpic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);

        break;
    }

}
