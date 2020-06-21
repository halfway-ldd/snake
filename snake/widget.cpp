#include "widget.h"
#include "ui_widget.h"

#include"reg.h"
#include"mainwindow.h"
#include"menu.h"
#include"data.h"

Widget::Widget(QWidget *parent)//登录界面的实现
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->pushButton_2->setShortcut(Qt::Key_Return);//将字母区回车键与登录按钮绑定在一起
    QShortcut *key = new QShortcut(QKeySequence(Qt::Key_Enter),this);
    connect(key, SIGNAL(activated()),ui->pushButton_2, SLOT(click()));
    setWindowModality(Qt::WindowModal);
}


Widget::~Widget()
{
    delete ui;
}



void Widget::on_pushButton_2_clicked()//登录按钮的槽函数
{
    account=ui->lineEdit->text();
    password=ui->lineEdit_2->text();
    if(QString(password).isEmpty())
    {
        QMessageBox::warning(this,"warning","密码不能为空");
        return;
    }
    QFile read("./Save.txt");
    if(!read.open(QIODevice::ReadOnly)) return;
    QTextStream in(&read);
    int i=0;
    QString str;
    while(!QString(str=in.readLine()).isNull())
    {
        if(i%3==0)
        {
            if(str==account)
            {
                break;
            }
        }
        i=i+1;
    }
    if(!QString(str).isEmpty())
    {
        QString str2;
        str2=in.readLine();
        if(str2==password)
        {
//            MainWindow *m=new MainWindow;
//            m->show();
//            this->close();
//            menu *m=new menu;
//            m->show();
//            this->close();
            data::data_user=str;
            data::data_state=true;
            QMessageBox::information(this,"成功","登陆成功！");
            this->close();
        }
        else
        {
            QMessageBox::critical(this,"密码错误","密码错误!");
            return;
        }
    }
    else
    {
        QMessageBox::information(this,"information","用户名不存在");
        return;
    }

}

void Widget::on_pushButton_clicked()//注册按钮的槽函数，显示出注册界面
{
    reg *re=new reg(this);
    re->setWindowFlag(Qt::Window);
    re->show();
}
