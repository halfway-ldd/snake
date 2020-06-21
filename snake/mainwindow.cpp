#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"tools.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),mysnake(this),mainwindowtimer(this)
{
    ui->setupUi(this);                                                                    //窗体的基本设置
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("Game");
    this->setFixedSize(MAX_X*BLOCK_SIZE,(MAX_Y+1)*BLOCK_SIZE);
    mainwindowtimer.start(1000);
    connect(&mysnake,&snake::atefood,this,&MainWindow::scored);                            //连接得分 时间经过的槽
    connect(&mysnake,&snake::snakeover,this,&MainWindow::gameover);
    connect(&mainwindowtimer,&QTimer::timeout,this,&MainWindow::timed);
    connect(&mysnake,&snake::stoptime,&mainwindowtimer,&QTimer::stop);
    connect(&mysnake,SIGNAL(continuetime()),&mainwindowtimer,SLOT(start()));
    initgame();
    drawscoreboard();
    creatfood();
    mysnake.getmap(map);
    mysnake.initsnake(map[mysnake.gethead_x()][mysnake.gethead_y()],map[mysnake.gettail_x()][mysnake.gettail_y()]);
   }



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initgame()
{

    for(int i=0;i<=MAX_X-1;i++)
{
    for(int j=0;j<=MAX_Y-1;j++)
    {

        map[i][j]=new mapnode;
        map[i][j]->x=i;
        map[i][j]->y=j;
        map[i][j]->type=space;
    }
}
    drawmap();
    loadmap();
}

void MainWindow::drawmap()
{
    for(int i=0;i<=MAX_X-1;i++)
    {
        for(int j=0;j<=MAX_Y-1;j++)
        {
            if(i==0||j==0||i==MAX_X-1||j==MAX_Y-1)
            {
            map[i][j]->type=wall;
            map[i][j]->label=new QLabel(this);
            map[i][j]->label->setPixmap(mysnake.wallpic);
            map[i][j]->label->resize(BLOCK_SIZE,BLOCK_SIZE);
            map[i][j]->label->move(i*BLOCK_SIZE,j*BLOCK_SIZE);
            map[i][j]->label->show();
            }
            else
            {
                map[i][j]->type=space;
                map[i][j]->label=new QLabel(this);
                map[i][j]->label->setStyleSheet("background:white");
                map[i][j]->label->resize(BLOCK_SIZE,BLOCK_SIZE);
                map[i][j]->label->move(i*BLOCK_SIZE,j*BLOCK_SIZE);
                map[i][j]->label->show();
            }
        }
    }
}

mapnode * MainWindow::mapmessage(int x, int y)
{
    return map[x][y];
}

void MainWindow::scored()
{
    score++;
    _score->setText("score:"+QString::number(score)+"        speed:"+QString::number(snake::speed));
    creatfood();
    if(score!=0&&score%7==0)
        creatobstacle();
}

void MainWindow::timed()
{
    gametime++;
    _time->setText("time:"+QString::number(gametime)+"s");
}

void MainWindow::drawscoreboard()//画出积分板
{
   _score = new QLabel(this);
   _time = new QLabel(this);
   _score->resize((MAX_X/2)*BLOCK_SIZE,BLOCK_SIZE);
   _score->move(0*BLOCK_SIZE,MAX_Y*BLOCK_SIZE);
   _score->setText("score:"+QString::number(score)+"        speed:"+QString::number(snake::speed));
   _time->resize((MAX_X/2)*BLOCK_SIZE,BLOCK_SIZE);
   _time->move((MAX_X/2)*BLOCK_SIZE,MAX_Y*BLOCK_SIZE);
   _time->setText("time:"+QString::number(gametime));
   QPushButton *closebutton=new QPushButton(this);
   closebutton->setText("关闭");
   closebutton->resize((MAX_X/6)*BLOCK_SIZE,BLOCK_SIZE);
   closebutton->move((MAX_X/2)*BLOCK_SIZE+260,MAX_Y*BLOCK_SIZE);
   connect(closebutton,&QPushButton::clicked,this,&MainWindow::close);
}

void MainWindow::creatfood()
{
    int foodx,foody;
    int is=0;
    srand((unsigned)time(0));
    do{
    foodx=(rand()%(MAX_X-1));
    foody=(rand()%(MAX_Y-1));
    if(map[foodx][foody]->type==space)
    {
       is=1;
       map[foodx][foody]->type=Food;
       map[foodx][foody]->label->setPixmap(mysnake.foodpic);
    }
    }while(is==0);
    if(score!=0&&score%5==0)
        {
           snake::speed=snake::speed-10;                            //随着得分增加，速度加快
           mysnake.timer.start(snake::speed);
        }
    if(score==99)
    {
        QMessageBox::information(this,"CONGRATULATIONS","恭喜你成为了万蛇之王");
        gameover();
    }
}
void MainWindow::creatobstacle()
{
    int obx,oby;
    int is=0;
    srand((unsigned)time(0));
    do{
    obx=(rand()%(MAX_X-1));
    oby=(rand()%(MAX_Y-1));
    if(map[obx][oby]->type==space)
    {
       is=1;
       map[obx][oby]->type=wall;
       map[obx][oby]->label->setPixmap(mysnake.wallpic);
    }
    }while(is==0);
}

void MainWindow::gameover()
{

    if(!QString(data::data_user).isEmpty())
        changeScore(QString::number(score));
    mainwindowtimer.stop();
    if(QMessageBox::Yes==(QMessageBox::question(this,"游戏结束","是否继续游玩？）",QMessageBox::Yes | QMessageBox::No)))
    {
        for(int i=0;i<=MAX_X-1;i++)
        {
            for(int j=0;j<=MAX_Y-1;j++)
            {
                if(i==0||j==0||i==MAX_X-1||j==MAX_Y-1)
                {
                    map[i][j]->type=wall;
                    map[i][j]->label->setPixmap(mysnake.wallpic);
                }
                else
                {
                    map[i][j]->type=space;
                    map[i][j]->label->setPixmap(QPixmap(""));
                }
            }
        }
        loadmap();
        gametime=0;
        score=0;
        creatfood();
        mysnake.getmap(map);
        mysnake.initsnake(map[mysnake.gethead_x()][mysnake.gethead_y()],map[mysnake.gettail_x()][mysnake.gettail_y()]);
    }
    else
    {



        for(int i=0;i<=MAX_X-1;i++)
        {
           for(int j=0;j<=MAX_Y-1;j++)
           { delete (map[i][j]);}

        }


        this->close();
    }
}

void MainWindow::loadmap()
{
    switch (data::data_mapmode) {
    case 0:
    break;
    case 1:
        for(int i=5;i<=15;i++)
        {
        map[i][i]->type=wall;
        map[i][i]->label->setPixmap(mysnake.wallpic);
        }
        break;
    case 2:
        map[9][13]->type=wall;
        map[9][13]->label->setPixmap(mysnake.wallpic);
        map[20][6]->type=wall;
        map[20][6]->label->setPixmap(mysnake.wallpic);
        map[12][12]->type=wall;
        map[12][12]->label->setPixmap(mysnake.wallpic);
        map[19][7]->type=wall;
        map[19][7]->label->setPixmap(mysnake.wallpic);
        map[18][8]->type=wall;
        map[18][8]->label->setPixmap(mysnake.wallpic);
        map[9][9]->type=wall;
        map[9][9]->label->setPixmap(mysnake.wallpic);
        break;
    case 3:
        for(int i=8;i<=10;i++)
        {
            map[i][8]->type=wall;
            map[i][8]->label->setPixmap(mysnake.wallpic);
        }

        for(int i=14;i<=16;i++)
        {
            map[i][8]->type=wall;
            map[i][8]->label->setPixmap(mysnake.wallpic);
        }

        map[9][13]->type=wall;
        map[9][13]->label->setPixmap(mysnake.wallpic);
        map[10][14]->type=wall;
        map[10][14]->label->setPixmap(mysnake.wallpic);
        map[11][15]->type=wall;
        map[11][15]->label->setPixmap(mysnake.wallpic);
        map[12][16]->type=wall;
        map[12][16]->label->setPixmap(mysnake.wallpic);
        map[13][15]->type=wall;
        map[13][15]->label->setPixmap(mysnake.wallpic);
        map[14][14]->type=wall;
        map[14][14]->label->setPixmap(mysnake.wallpic);
        map[15][13]->type=wall;
        map[15][13]->label->setPixmap(mysnake.wallpic);map[9][13]->type=wall;
        break;



    }
}
