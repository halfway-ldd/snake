#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QString>
#include<string.h>
#include<QFile>
#include<QMessageBox>
#include<QPushButton>
#include<QDebug>
#include<QKeySequence>
#include<QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void compare();


private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QString account;
    QString password;
};
#endif // WIDGET_H
