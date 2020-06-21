#ifndef BASIC_SETTING_H
#define BASIC_SETTING_H

#include <QLabel>

const int MAX_X = 24;
const int MAX_Y = 20;
const int BLOCK_SIZE = 32;  //地图的大小设置

enum Type
{
    wall,
    space,
    body,
    Head,
    Tail,
    Food
};                        //定义地图格子种类


struct mapnode
{
    QLabel* label;
    Type type;
    int x;
    int y;
};                        //地图节点 label显示图片 type储存格子类型

#endif // BASIC_SETTING_H
