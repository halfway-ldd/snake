#include"tools.h"

int getNumber()
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
    n=n/3;
    read.close();
    return n;
}
void changeScore(QString score)
{
    int n=getNumber();

    QFile read("./Save.txt");
    if(!read.open(QIODevice::ReadOnly)) return;
    QTextStream in(&read);

    struct tempData temp[n];
    int i=0;
    QString str;
    while(!QString(str=in.readLine()).isNull())
    {
        if(i%3==0)
            temp[i/3].account=str;
        if(i%3==1)
            temp[i/3].password=str;
        if(i%3==2)
            temp[i/3].score=str;
        i++;
    }
    read.close();
    for(int i=0;i<n;i++)
    {
        if(temp[i].account==data::data_user)
        {
            if(temp[i].score.toInt()<score.toInt())
            {
                temp[i].score=score;
            }
        }
    }
    QFile write("./Save.txt");
    if(!write.open(QIODevice::WriteOnly | QFile::Truncate)) return;
    QTextStream out(&write);
    for(int i=0;i<n;i++)
    {
        out<<temp[i].account<<endl<<temp[i].password<<endl<<temp[i].score<<endl;
    }
    write.close();

}
