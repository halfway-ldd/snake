#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "basic_setting.h"
#include "snake.h"
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <data.h>
#include<QFile>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//    bool event(QEvent *event) ;
private:
    Ui::MainWindow *ui;
    snake mysnake;                          //管理蛇
    mapnode * map[MAX_X][MAX_Y];            //储存地图信息
    void initgame();                        //初始化地图格子信息
    void loadmap();                         //加载预设地图
    void drawmap();                         //绘制地图边框
    mapnode * mapmessage(int x,int y);      //在需要时返回相应位置的地图信息
    QTimer mainwindowtimer;                 //mainwindow 计时器
    void timed();                           //时间经过
    void scored();                          //得分
    void drawscoreboard();                  //绘制积分板
    void creatfood();                       //刷新食物
    void creatobstacle();                   //刷新障碍
    void gameover();                        //游戏结束

    int score=0;
    int gametime=0;
    QLabel* _score;
    QLabel* _time;

};

#endif // MAINWINDOW_H
