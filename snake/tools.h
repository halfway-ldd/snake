#ifndef TOOLS_H
#define TOOLS_H


#include<QFile>
#include<QString>
#include<QTextStream>
#include"data.h"
struct tempData
{
    QString account;
    QString password;
    QString score;
};

void changeScore(QString score);

int getNumber();

#endif // TOOLS_H
