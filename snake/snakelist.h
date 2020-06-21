#ifndef SNAKELIST_H
#define SNAKELIST_H
#include "basic_setting.h"
#include "data.h"
#include <QDebug>

class snakelist
{
public:
    static snakelist * headnode;
    static snakelist * tailnode;
    snakelist();
    ~snakelist();
    void init(mapnode * head,mapnode * tail);   //初始化
    int add(mapnode * map);                     //增加一个结点
    void detail();                              //删除尾节点
    void deletelist();
private:
    mapnode * Mapnode;
    snakelist * nextnode;

};

#endif // SNAKELIST_H
