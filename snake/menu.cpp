#include "menu.h"
#include "ui_menu.h"
#include"data.h"
#include"widget.h"
#include"mainwindow.h"

menu::menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);//显示主页面
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);


    connect(this->timer, SIGNAL(timeout()), this, SLOT(displayUser()));//用来实时显示用户名
    timer->start(100);


}
void menu::displayUser()//用户名登陆状态显示
{
    if(!data::data_state)
    {
        ui->label_3->setText("");
        ui->label_4->setText("");
        ui->label_5->setText("用户未登录");
        ui->pushButton_3->setText("登录账号");
    }
    else
    {
        ui->label_3->setText("用户名：");
        ui->label_4->setText(data::data_user);
        ui->label_5->setText("已登录");
        ui->pushButton_3->setText("切换账号");
    }
}
void menu::getNumber()//文件中的用户名数量
{
    QFile read("./Save.txt");
    read.open(QIODevice::ReadOnly);
    QTextStream in(&read);
    int n=0;
    QString str;
    while(!QString(str=in.readLine()).isNull())
    {
        n++;
    }
    total=n/3;
    read.close();
}
void menu::scoreSort(struct user *p,int t)//按得分大小排序
{
    struct user temp;
    int i,j;
    for(i=0;i<t;i++)
    {
        struct user maxUser;
        maxUser=p[i];
        for(j=i+1;j<t;j++)
        {
            if(p[j].score.length()==maxUser.score.length())
            {
                if(QString::compare(p[j].score,maxUser.score)>0)
                {
                    temp=p[j];
                    p[j]=maxUser;
                    maxUser=temp;
                }
            }
            else if(p[j].score.length()>maxUser.score.length())
            {
                temp=p[j];
                p[j]=maxUser;
                maxUser=temp;
            }
            p[i]=maxUser;
        }
    }
}
QString menu::achievement(QString score)//称号系统
{
    //0-30幼年期    31-50成长期     51-70成熟期    71-98完全体    99万蛇之王

    if(score.toInt()>=0||score.toInt()<=99)
    {
        if(score.toInt()<=30)
            return "幼年期";
        else if(score.toInt()<=50)
            return "成长期";
        else if(score.toInt()<=70)
            return "成熟期";
        else if(score.toInt()<=98)
            return "完全体";
        else
            return "万蛇之王";
    }
    else
        return "数据有误";
}
menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_clicked()//开始按钮
{
    if(!data::data_state)
    {
        if(QMessageBox::Yes==(QMessageBox::question(this,"未登录","尚未登录，是否直接游玩？（得分不会被记录）",QMessageBox::Yes | QMessageBox::No)))
        {
            MainWindow* m=new MainWindow;
            m->show();
        }
    }
    else
    {
        MainWindow* m=new MainWindow;
        m->show();
    }
}

void menu::on_pushButton_2_clicked()//排行榜按钮
{
    getNumber();
    ui->stackedWidget->setCurrentIndex(2);
    QPixmap *pixmap = new QPixmap(":/gamepic/title.png");//蛇王争霸图片显示
    pixmap->scaled(ui->label_7->size(), Qt::KeepAspectRatio);
    ui->label_7->setScaledContents(true);
    ui->label_7->setPixmap(*pixmap);

    pixmap=new QPixmap(":/gamepic/snake_03.png");//蛇图片显示
    pixmap->scaled(ui->label_9->size(), Qt::KeepAspectRatio);
    ui->label_9->setScaledContents(true);
    ui->label_9->setPixmap(*pixmap);

    ui->tableWidget->setEditTriggers(0);//禁止编辑
    ui->tableWidget->setRowCount(total);//设置行数
    user rankUser[total];
    QFile read("./Save.txt");
    if(!read.open(QIODevice::ReadOnly)) return;
    QTextStream in(&read);
    int i=0;
    QString str;
    while(!QString(str=in.readLine()).isNull())
    {
        i++;
        if(i%3==1)rankUser[(i-1)/3].account=str;
        if(i%3==0&&i!=0)rankUser[(i/3)-1].score=str;
    }
    read.close();
    scoreSort(rankUser,total);
    int y;
    for(y=0;y<total;y++)
    {
        ui->tableWidget->setItem(y,0,new QTableWidgetItem(rankUser[y].account));
        ui->tableWidget->item(y,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(y,1,new QTableWidgetItem(rankUser[y].score));
        ui->tableWidget->item(y,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(y,2,new QTableWidgetItem(achievement(rankUser[y].score)));
        ui->tableWidget->item(y,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
}

void menu::on_pushButton_3_clicked()//登录账户按钮
{
    Widget* w=new Widget(this);
    w->setWindowFlag(Qt::Window);
    w->show();
}

void menu::on_pushButton_4_clicked()//退出账户按钮
{
    if(data::data_state)
    {
        data::data_user="";
        data::data_state=false;
        QMessageBox::information(this,"information","退出成功");
    }
    else
    {
        QMessageBox::information(this,"information","尚未登录");
    }
}

void menu::on_pushButton_5_clicked()//游戏说明按钮
{
    ui->stackedWidget->setCurrentIndex(1);
    QPixmap *pixmap = new QPixmap(":/gamepic/desc.jpg");
    pixmap->scaled(ui->label_6->size(), Qt::KeepAspectRatio);
    ui->label_6->setScaledContents(true);
    ui->label_6->setPixmap(*pixmap);
    pixmap=new QPixmap(":/gamepic/snake_02.png");
    pixmap->scaled(ui->label_8->size(),Qt::KeepAspectRatio);
    ui->label_8->setScaledContents(true);
    ui->label_8->setPixmap(*pixmap);
}

void menu::on_pushButton_6_clicked()//返回主界面
{
    ui->stackedWidget->setCurrentIndex(0);
}

void menu::on_pushButton_7_clicked()//返回主界面
{
    ui->stackedWidget->setCurrentIndex(0);
}

void menu::on_pushButton_8_clicked()//自定义按钮
{
    ui->stackedWidget->setCurrentIndex(3);

    //蛇头图片
    QPixmap *pixmap = new QPixmap(":/gamepic/snakeHead01");
    pixmap->scaled(ui->label_11->size(), Qt::KeepAspectRatio);
    ui->label_11->setScaledContents(true);
    ui->label_11->setPixmap(*pixmap);

    pixmap=new QPixmap(":/gamepic/snakeHead02");
    pixmap->scaled(ui->label_12->size(), Qt::KeepAspectRatio);
    ui->label_12->setScaledContents(true);
    ui->label_12->setPixmap(*pixmap);

    pixmap=new QPixmap(":/gamepic/snakeHead03");
    pixmap->scaled(ui->label_13->size(), Qt::KeepAspectRatio);
    ui->label_13->setScaledContents(true);
    ui->label_13->setPixmap(*pixmap);

    pixmap=new QPixmap(":/gamepic/snakeHead04");
    pixmap->scaled(ui->label_14->size(), Qt::KeepAspectRatio);
    ui->label_14->setScaledContents(true);
    ui->label_14->setPixmap(*pixmap);

    //蛇身图片
    pixmap=new QPixmap(":/gamepic/snakeBody01");
    pixmap->scaled(ui->label_18->size(), Qt::KeepAspectRatio);
    ui->label_18->setScaledContents(true);
    ui->label_18->setPixmap(*pixmap);

    pixmap=new QPixmap(":/gamepic/snakeBody02");
    pixmap->scaled(ui->label_19->size(), Qt::KeepAspectRatio);
    ui->label_19->setScaledContents(true);
    ui->label_19->setPixmap(*pixmap);

    pixmap=new QPixmap(":/gamepic/snakeBody03");
    pixmap->scaled(ui->label_20->size(), Qt::KeepAspectRatio);
    ui->label_20->setScaledContents(true);
    ui->label_20->setPixmap(*pixmap);

    pixmap=new QPixmap(":/gamepic/snakeBody04");
    pixmap->scaled(ui->label_21->size(), Qt::KeepAspectRatio);
    ui->label_21->setScaledContents(true);
    ui->label_21->setPixmap(*pixmap);

    //墙的图片
    pixmap=new QPixmap(":/gamepic/wall01");
    pixmap->scaled(ui->label_22->size(), Qt::KeepAspectRatio);
    ui->label_22->setScaledContents(true);
    ui->label_22->setPixmap(*pixmap);

    pixmap=new QPixmap(":/gamepic/wall02");
    pixmap->scaled(ui->label_23->size(), Qt::KeepAspectRatio);
    ui->label_23->setScaledContents(true);
    ui->label_23->setPixmap(*pixmap);

    pixmap=new QPixmap(":/gamepic/wall03");
    pixmap->scaled(ui->label_24->size(), Qt::KeepAspectRatio);
    ui->label_24->setScaledContents(true);
    ui->label_24->setPixmap(*pixmap);

    pixmap=new QPixmap(":/gamepic/wall04");
    pixmap->scaled(ui->label_25->size(), Qt::KeepAspectRatio);
    ui->label_25->setScaledContents(true);
    ui->label_25->setPixmap(*pixmap);

    //食物图片
    pixmap=new QPixmap(":/gamepic/food01");
    pixmap->scaled(ui->label_26->size(), Qt::KeepAspectRatio);
    ui->label_26->setScaledContents(true);
    ui->label_26->setPixmap(*pixmap);

    pixmap=new QPixmap(":/gamepic/food02");
    pixmap->scaled(ui->label_27->size(), Qt::KeepAspectRatio);
    ui->label_27->setScaledContents(true);
    ui->label_27->setPixmap(*pixmap);

    pixmap=new QPixmap(":/gamepic/food03");
    pixmap->scaled(ui->label_28->size(), Qt::KeepAspectRatio);
    ui->label_28->setScaledContents(true);
    ui->label_28->setPixmap(*pixmap);

    pixmap=new QPixmap(":/gamepic/food04");
    pixmap->scaled(ui->label_29->size(), Qt::KeepAspectRatio);
    ui->label_29->setScaledContents(true);
    ui->label_29->setPixmap(*pixmap);
}

void menu::on_pushButton_9_clicked()//画面设置返回主页面
{
    ui->stackedWidget->setCurrentIndex(0);
}
void menu::on_pushButton_10_clicked()//画面设置到地图设置
{
    ui->stackedWidget->setCurrentIndex(4);
    QPixmap *pixmap = new QPixmap(":/gamepic/map00");
    pixmap->scaled(ui->label_31->size(), Qt::KeepAspectRatio);
    ui->label_31->setScaledContents(true);
    ui->label_31->setPixmap(*pixmap);

    pixmap=new QPixmap(":/gamepic/map01");
    pixmap->scaled(ui->label_32->size(), Qt::KeepAspectRatio);
    ui->label_32->setScaledContents(true);
    ui->label_32->setPixmap(*pixmap);

    pixmap=new QPixmap(":/gamepic/map02");
    pixmap->scaled(ui->label_33->size(), Qt::KeepAspectRatio);
    ui->label_33->setScaledContents(true);
    ui->label_33->setPixmap(*pixmap);

    pixmap=new QPixmap(":/gamepic/map03");
    pixmap->scaled(ui->label_34->size(), Qt::KeepAspectRatio);
    ui->label_34->setScaledContents(true);
    ui->label_34->setPixmap(*pixmap);
}
void menu::on_pushButton_12_clicked()//地图设置到画面设置
{
    ui->stackedWidget->setCurrentIndex(3);
}
void menu::on_pushButton_11_clicked()//地图设置到主界面
{
    ui->stackedWidget->setCurrentIndex(0);
}
//以下是自定义界面的radioButton的槽函数
void menu::on_radioButton_clicked()
{
    data::data_snake=1;
}


void menu::on_radioButton_2_clicked()
{
    data::data_snake=2;
}

void menu::on_radioButton_3_clicked()
{
    data::data_snake=3;
}


void menu::on_radioButton_4_clicked()
{
    data::data_snake=4;
}

void menu::on_radioButton_5_clicked()
{
    data::data_wall=1;
}


void menu::on_radioButton_6_clicked()
{
    data::data_wall=2;
}

void menu::on_radioButton_7_clicked()
{
    data::data_wall=3;
}

void menu::on_radioButton_8_clicked()
{
    data::data_wall=4;
}

void menu::on_radioButton_9_clicked()
{
    data::data_food=1;
}

void menu::on_radioButton_10_clicked()
{
    data::data_food=2;
}

void menu::on_radioButton_11_clicked()
{
    data::data_food=3;
}

void menu::on_radioButton_12_clicked()
{
    data::data_food=4;
}

void menu::on_radioButton_13_clicked()
{
    data::data_mapmode=0;
}

void menu::on_radioButton_14_clicked()
{
    data::data_mapmode=1;
}

void menu::on_radioButton_15_clicked()
{
    data::data_mapmode=2;
}

void menu::on_radioButton_16_clicked()
{
    data::data_mapmode=3;
}
