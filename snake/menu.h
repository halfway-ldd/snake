#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include<QTimer>
#include<QString>
#include<QDebug>
#include<QMessageBox>
#include<QPixmap>

namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    void getNumber();//获取用户数量
    void scoreSort(struct user *p,int t);//排序
    QString achievement(QString score);//称号系统
    ~menu();


private slots:
    void displayUser();//显示当前用户

    void on_pushButton_clicked();//开始按钮

    void on_pushButton_2_clicked();//排行榜按钮

    void on_pushButton_3_clicked();//登录账户按钮

    void on_pushButton_4_clicked();//退出账户按钮

    void on_pushButton_5_clicked();//游戏说明按钮

    void on_pushButton_6_clicked();//说明界面返回主界面

    void on_pushButton_7_clicked();//排行榜界面返回主界面

    void on_pushButton_8_clicked();//画面设置按钮

    void on_pushButton_9_clicked();//设置界面返回主界面

    void on_pushButton_10_clicked();//画面设置到地图设置

    void on_pushButton_12_clicked();//地图设置到画面设置

    void on_pushButton_11_clicked();//地图设置到主界面

    //画面设置
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_8_clicked();

    void on_radioButton_9_clicked();

    void on_radioButton_10_clicked();

    void on_radioButton_11_clicked();

    void on_radioButton_12_clicked();





    void on_radioButton_13_clicked();

    void on_radioButton_14_clicked();

    void on_radioButton_15_clicked();

    void on_radioButton_16_clicked();

private:
    Ui::menu *ui;
    QTimer*timer=new QTimer(this);
    int total;
};
struct user
{
    QString account;
    QString score;
};

#endif // MENU_H
