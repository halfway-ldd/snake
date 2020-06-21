#ifndef REG_H
#define REG_H

#include <QWidget>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QShortcut>

namespace Ui {
class reg;
}

class reg : public QWidget
{
    Q_OBJECT

public:
    explicit reg(QWidget *parent = nullptr);
    ~reg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::reg *ui;
};

#endif // REG_H
