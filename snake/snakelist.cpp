#include "snakelist.h"


snakelist * snakelist::headnode=NULL;
snakelist * snakelist::tailnode=NULL;

snakelist::snakelist()
{

}

void snakelist::init(mapnode * head,mapnode * tail)
{
    headnode=new snakelist;
    tailnode=new snakelist;
    headnode->Mapnode=head;
    headnode->nextnode=tailnode;
    tailnode->Mapnode=tail;
    tailnode->nextnode=NULL;
}

int snakelist::add(mapnode * map)
{
   snakelist * nownode=new snakelist;
   nownode->Mapnode=map;
   nownode->nextnode=headnode;

   QPixmap snakeheadpic,snakebodypic;
   switch (data::data_snake) {
   case 1:
       snakeheadpic.load(":/gamepic/snakeHead01");
       snakebodypic.load(":/gamepic/snakeBody01");
       snakeheadpic=snakeheadpic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);
       snakebodypic=snakebodypic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);

       break;
   case 2:
       snakeheadpic.load(":/gamepic/snakeHead02");
       snakebodypic.load(":/gamepic/snakeBody02");
       snakeheadpic=snakeheadpic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);
       snakebodypic=snakebodypic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);

       break;
   case 3:
       snakeheadpic.load(":/gamepic/snakeHead03");
       snakebodypic.load(":/gamepic/snakeBody03");
       snakeheadpic=snakeheadpic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);
       snakebodypic=snakebodypic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);

       break;
   case 4:
       snakeheadpic.load(":/gamepic/snakeHead04");
       snakebodypic.load(":/gamepic/snakeBody04");
       snakeheadpic=snakeheadpic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);
       snakebodypic=snakebodypic.scaled(QSize(BLOCK_SIZE,BLOCK_SIZE),Qt::IgnoreAspectRatio);

       break;
       };

   Type pre= nownode->Mapnode->type;
   headnode->Mapnode->type=body;
   headnode->Mapnode->label->setPixmap(snakebodypic);
   headnode=nownode;

   headnode->Mapnode->label->setPixmap(snakeheadpic);
   headnode->Mapnode->type=Head;
   if(pre==wall||pre==body||pre==Tail)
   {
   return 0;
   }
   else if(pre==Food)
   {
       return 2;
   }
   else
   {
       return  1;
   }
}

snakelist::~snakelist()
{

}

void snakelist::detail()
{
    tailnode->Mapnode->label->setPixmap(QPixmap(""));
    tailnode->Mapnode->type=space;
    snakelist * p=headnode;
    for(;p->nextnode!=tailnode;)
    {
         p=p->nextnode;
    }
    delete tailnode;
    tailnode=p;
    tailnode->nextnode=NULL;
    tailnode->Mapnode->type=Tail;
}

void snakelist::deletelist()
{
    snakelist * p=headnode;
    snakelist * p2=headnode->nextnode;
    do
    {
        delete p;
        qDebug()<<"delete";
        p=p2;
        p2=p2->nextnode;
    }while(p->nextnode!=NULL);
    delete p2;


}
