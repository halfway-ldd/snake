#include "reg.h"
#include "ui_reg.h"

reg::reg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reg)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    ui->pushButton->setShortcut(Qt::Key_Return);//将字母区回车键与登录按钮绑定在一起
    QShortcut *key = new QShortcut(QKeySequence(Qt::Key_Enter),this);
    connect(key, SIGNAL(activated()),ui->pushButton, SLOT(click()));
}

reg::~reg()
{
    delete ui;
}

void reg::on_pushButton_clicked()//注册界面的注册按钮，用于检查数据是否合格
{
    QString accout,name,password,psw2;
    accout=ui->lineEdit->text();
    password=ui->lineEdit_3->text();
    psw2=ui->lineEdit_4->text();
    if(QString(accout).isEmpty())
    {
        QMessageBox::warning(this,"critical","用户名不能为空");
        return;
    }
    if(QString(password).isEmpty())
    {
        QMessageBox::warning(this,"critical","密码不能为空");
        return;
    }
    if(password!=psw2)
    {
        QMessageBox::warning(this,"critical","确认密码有误");
        return;
    }
    QFile read("./Save.txt");
    read.open(QIODevice::ReadOnly);
    QTextStream in(&read);
    int i=0;
    QString str;
    while(!QString(str=in.readLine()).isNull())
    {
        if(i%3==0)
        {
            if(str==accout)
            {
                QMessageBox::warning(this,"critical","账号已存在");
                return;
            }
        }
        i++;
    }
    read.close();

    QFile wr("./Save.txt");
    wr.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream op(&wr);
    op<<accout<<endl<<password<<endl<<"0"<<endl;
    wr.close();
    QMessageBox::information(this,"information","注册成功!");
    this->close();
}
